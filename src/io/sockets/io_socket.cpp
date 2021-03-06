#include <silica/common/error.h>
#include <silica/io/sockets/io_socket.h>

#include <errno.h>
#include <sys/ioctl.h>

namespace silica {
namespace io {
namespace sockets {

io_socket::io_socket() : m_connected(false) {}

io_socket::~io_socket() {
    if (m_connected && shutdown(m_fd, SHUT_RDWR) == -1) {
        print_error_errno("shutdown(): ", errno);
    }
}

void io_socket::connect(std::string const& hostname, std::string const& port) {
    sockaddr addr;
    const size_t addrlen = resolve(hostname, port, addr);
    if (::connect(m_fd, &addr, addrlen) < 0) {
        make_error_errno("connect(): ", errno);
    }
    m_connected = true;
}

bool io_socket::valid() { return m_connected; }

size_t io_socket::avail() const {
    size_t avail = 0;
    if (ioctl(m_fd, FIONREAD, &avail) == -1) {
        make_error_errno("ioctl(): ", errno);
    }
    return avail;
}

std::vector<uint8_t> io_socket::read(size_t len) const {
    std::vector<uint8_t> res(len);
    size_t pos = 0;
    while (pos < len) {
        size_t recvd;
        if ((recvd = recv(m_fd, &res.data()[pos], len - pos, MSG_NOSIGNAL)) < 0) {
            make_error_errno("recv(): ", errno);
        }
        pos += recvd;
    }
    return res;
}

void io_socket::write(std::vector<uint8_t> const& data) const {
    size_t pos = 0;
    while (pos < data.size()) {
        ssize_t sent;
        if ((sent = send(m_fd, &data.data()[pos], data.size() - pos, MSG_NOSIGNAL)) < 0) {
            make_error_errno("send(): ", errno);
        }
        pos += sent;
    }
}
}  // namespace sockets
}  // namespace io
}  // namespace silica
