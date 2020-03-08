/**
 * @file include/app/Core.hpp
 *
 */

#ifndef CORE_HPP_
# define CORE_HPP_

# include <atomic>

# include <dll/Manager.hpp>

class Core {
public:
    Core() = default;
    ~Core() = default;

    void stop() noexcept { m_is_running = false; }
    bool isRunning() const noexcept { return m_is_running; }

    dll::Manager &getDllManager() noexcept { return m_dllManager; }

protected:
private:

    std::atomic<bool> m_is_running = true;

    dll::Manager m_dllManager;

};

#endif /* !CORE_HPP_ */
