#ifndef io_socket_h_
#define io_socket_h_

#include <cstdint>
#include <unordered_map>
#include <vector>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <silica/common/error.h>
#include <silica/io/io_base.h>

namespace silica {
namespace io {
namespace sockets {

class io_socket : public io_base {
public:
    io_socket();
    void connect(std::string const& hostname, std::string const& port);

    virtual ~io_socket();
    virtual bool valid() override;

    using io_base::read;
    using io_base::write;

    virtual std::vector<uint8_t> read(size_t len) const override;
    virtual void write(std::vector<uint8_t> const& data) const override;

protected:
    virtual size_t avail() const override;

    /* To be implemented by derived classes */
    virtual size_t resolve(std::string const& hostname, std::string const& port, sockaddr& sock_addr) = 0;

private:
    bool m_connected;
};
}  // namespace sockets
}  // namespace io
}  // namespace silica

#endif
