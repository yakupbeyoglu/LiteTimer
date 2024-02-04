#ifndef TYPES_H_
#define TYPES_H_

#include <any>
#include <chrono>
#include <functional>

/**
 * @file types.h
 * @brief Include Types
 * @author Yakup Beyoglu
 * @date December 8, 2023
 * @see https://github.com/yakupbeyoglu
 */

/**
 * @brief Define user-defined literal for converting seconds to milliseconds.
 *
 * This user-defined literal converts seconds to milliseconds.
 *
 * @param s The number of seconds.
 * @return std::chrono::milliseconds The corresponding milliseconds.
 */
constexpr std::chrono::milliseconds operator"" _s(unsigned long long s) {
  return std::chrono::milliseconds(s * 1000);
}

/**
 * @brief Define user-defined literal for converting minutes to milliseconds.
 *
 * This user-defined literal converts minutes to milliseconds.
 *
 * @param min The number of minutes.
 * @return std::chrono::milliseconds The corresponding milliseconds.
 */
constexpr std::chrono::milliseconds operator"" _min(unsigned long long min) {
  return std::chrono::milliseconds(min * 60 * 1000);
}

namespace yb {
namespace types {
/**
 * @brief Alias for std::chrono::time_point<std::chrono::high_resolution_clock>.
 */
using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

} // namespace types
} // namespace yb

#endif // TYPES_H_
