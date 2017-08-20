#ifndef io_manager_h_
#define io_manager_h_

#include "io_base.h"
#include "io_events.h"
#include "io_results.h"
#include "common/time.h"

#include <list>
#include <chrono>
#include <functional>
#include <unordered_map>

#include <sys/select.h>

namespace silica {
namespace io {

class io_manager {
public:

    io_manager() = default;
    void add_io(io_base const& io);

    template <typename R, typename P>
    std::list<io_result> read(std::chrono::duration<R, P> const& timeout) {
        return read(duration_to_timeval(timeout));
    }

    std::list<io_result> read(int timeout=0);
    std::list<io_result> read(timeval const& timeout);

private:

    int make_fdset(fd_set& fdset) const;
    std::list<io_event> get_readable(timeval const& timeout);

    std::list<std::reference_wrapper<const io_base>> m_ios;

};

}
}

#endif
