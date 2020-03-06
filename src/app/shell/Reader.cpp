/**
 * @file src/app/shell/Reader.cpp
 *
 */

#include <iostream>
#include <thread>

#include "app/shell/Reader.hpp"
#include "app/shell/Parser.hpp"

shell::Reader::Reader(Parser &parser) :
    m_parser        (parser),
    m_callback      ([this] {

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "$> ";

        std::string line;
        std::getline(std::cin, line);
        return line;
    })
{
    this->reset();
}

bool shell::Reader::read()
{
    if (this->m_promise.wait_for(std::chrono::microseconds(0)) != std::future_status::ready)
        return false;

    if (this->m_parser.parse(this->m_promise.get()))
        this->reset();

    return true;
}

void shell::Reader::reset()
{
    this->m_promise = std::async(std::launch::async, this->m_callback);
}
