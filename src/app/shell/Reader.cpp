/**
 * @file src/app/shell/Reader.cpp
 *
 */

#include <csignal>
#include <iostream>
#include <thread>

#include "app/shell/Reader.hpp"
#include "app/shell/Parser.hpp"

const std::function<std::string()> shell::Reader::sc_callback =
[]{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "$> ";

    std::string line;
    std::getline(std::cin, line);
    return line;
};

shell::Reader::Reader(Parser &parser) :
    m_parser    (parser)
{
    if (std::signal(SIGINT, [](int) {
        std::cout << std::endl << "POSIX signal SIGINT receive" << std::endl;
        std::terminate();
    }) == SIG_ERR)
        throw std::invalid_argument("signal: cannot bind SIGINT handler");

    std::cout << "Try 'help' if you are lost" << std::endl;

    this->reset();
}

bool shell::Reader::read()
{
    if (this->m_future.wait_for(std::chrono::microseconds(0)) != std::future_status::ready)
        return false;

    if (this->m_parser.parse(this->m_future.get()))
        this->reset();

    return true;
}

void shell::Reader::reset()
{
    this->m_future = std::async(std::launch::async, this->sc_callback);
}
