/**
 * @file src/app/shell/Reader.cpp
 *
 */

#include <csignal>
#include <iostream>
#include <thread>

#include "app/shell/Reader.hpp"

shell::Reader::Reader(IParser &parser) :
    m_parser        (parser),
    m_is_running    (false),
    c_callback  ([this]{

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "$> ";

        std::string line;
        if (!std::getline(std::cin, line))
            this->m_is_running = false;
        return line;

    })
{
    if (std::signal(SIGINT, [](int) {
        std::cout << std::endl << "POSIX signal SIGINT receive" << std::endl;
        std::terminate();
    }) == SIG_ERR)
        throw std::invalid_argument("signal: cannot bind SIGINT handler");

    std::cout << "Try 'help' if you are lost" << std::endl;

    this->reset();
}

shell::Reader::~Reader()
{
    this->kill();
}

bool shell::Reader::read()
{
    if (this->m_future.wait_for(std::chrono::microseconds(0)) != std::future_status::ready)
        return false;

    this->m_parser.parse(this->m_is_running ? this->m_future.get() : "exit");
    this->reset();

    return true;
}

void shell::Reader::reset()
{
    this->m_future = std::async(std::launch::async, this->c_callback);
    this->m_is_running = true;
}

void shell::Reader::kill()
{
    if (!this->m_is_running)
        return;

    std::thread([](const auto &) { std::terminate(); }, std::ref(this->m_future)).detach();
}
