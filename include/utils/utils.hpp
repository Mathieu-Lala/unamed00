/**
 * @file include/utils/utils.hpp
 *
 */

#ifndef UTILS_HPP_
# define UTILS_HPP_

# include <ctime>
# include <string>
# include <fstream>
# include <vector>
# include <sstream>

inline std::string timeStampToString()
{
    const auto now = std::time(nullptr);
    const auto tp = std::localtime(&now);

    char buffer[32];
    if (!std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", tp))
        return "1970-01-01_00:00:00";

    return buffer;
}

inline std::vector<std::string> explode(const std::string &str, char delim)
{
    std::istringstream split(str);
    std::vector<std::string> tokens;

    std::string each;
    while (std::getline(split, each, delim))
        if (each.size())
            tokens.push_back(each);
    return tokens;
}

inline std::string getContentFile(const std::string_view path)
{
    std::ifstream f(path.data());
    return std::string(
        (std::istreambuf_iterator<char>(f)),
        (std::istreambuf_iterator<char>( ))
    );
}

#endif /* !UTILS_HPP_ */
