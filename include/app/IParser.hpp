/**
 * @file include/app/IParser.hpp
 *
 */

#ifndef IPARSER_HPP_
# define IPARSER_HPP_

# include <string>

class IParser {
public:

    virtual ~IParser() = default;

    virtual void parse(const std::string &) = 0;

protected:
};

#endif /* !IPARSER_HPP_ */
