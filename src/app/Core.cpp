/**
 * @file src/app/Core.cpp
 *
 */

#include "app/Core.hpp"
#include "utils/utils.hpp"

Core::Core() :
    m_is_running    (true),
    m_shellParser   (*this),
    m_shellReader   (this->m_shellParser)
{
    const auto module_alias = "lib#00";
    const auto module_name = "abstract_sfml";
    const auto real_path = std::string(dll::Manager::DEFAULT_PATH) +
        "/module/graphic/" + dll::Manager::set_extension(module_name);

    this->m_dllManager.loadDirect(real_path, module_alias);
    const auto f = this->m_dllManager.get(module_alias).lock()->load<graphic::IWindow *(*)()>("createWindow");
    this->m_window = std::unique_ptr<graphic::IWindow>(f());

    this->m_window->setFavicon(MEDIA_DIR "logo/favicon.jpg");
}

int Core::start()
{
    while (this->isRunning()) {

        this->m_shellReader.read();

        if (this->m_window) {

            this->m_window->clear(0x000000FFu);
            // draw here
            this->m_window->render();

            graphic::Event e;
            this->m_window->pollEvent(e);
            if (e.type == graphic::Event::CLOSED)
                this->m_window->close();
            if (e.type == graphic::Event::KEY_PRESSED)
                if (e.key.code == graphic::KeyBoard::F12)
                    this->m_window->takeScreenShot(
                        std::string(MEDIA_DIR) + "screenshots/" + timeStampToString() + ".png");

        }

    }

    return APP_SUCCESS;
}

void Core::stop() noexcept
{
    m_is_running = false;
}

dll::Manager &Core::getDllManager() noexcept
{
    return m_dllManager;
}

bool Core::isRunning() const noexcept
{
    return m_is_running && (this->m_window ? this->m_window->isRunning() : true);
}
