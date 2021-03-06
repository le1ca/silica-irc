#ifndef io_results_h_
#define io_results_h_

#include <silica/io/io_base.h>
#include <vector>

namespace silica {
namespace io {

enum class io_result_type { RESULT_READ, RESULT_WRITE };

struct io_result {
    io_result(io_base const& io, std::vector<uint8_t> const& result, io_result_type type = io_result_type::RESULT_READ)
        : io(io), result(result), type(type) {}

    io_base const& io;
    std::vector<uint8_t> result;
    io_result_type type;
};
}  // namespace io
}  // namespace silica

#endif
