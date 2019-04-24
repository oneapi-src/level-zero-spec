#include "xe_app.hpp"
#include "api_static_probe.hpp"

namespace xe_api_benchmarks {
namespace measure_latency {
void parameter_buffer(XeApp *benchmark, int warm_up_iteration,
                      int measure_iteration);
void parameter_integer(XeApp *benchmark, int warm_up_iteration,
                       int measure_iteration);
} /* namespace measure_latency */
} /* namespace xe_api_benchmarks */
