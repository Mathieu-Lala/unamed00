/**
 * @file include/utils/utils.hpp
 *
 */

#ifndef UTILS_HPP_
# define UTILS_HPP_

# include <ctime>
# include <string>

inline std::string timeStampToString()
{
    const auto now = std::time(nullptr);
    const auto tp = std::localtime(&now);

    char buffer[32];
    if (!std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", tp))
        return "1970-01-01_00:00:00";

    return buffer;
}

#endif /* !UTILS_HPP_ */
