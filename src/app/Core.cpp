/**
 * @file src/app/Core.cpp
 *
 */

#include <iostream>

#include "app/Core.hpp"
#include "utils/utils.hpp"

Core::Core() :
    m_is_running    (true),
    m_shellParser   (*this),
    m_shellReader   (this->m_shellParser)
{
    try {
        for (const auto &i : m_dllManager.getAvailable()) 
            if (i.moduleType != "<none>")
                this->m_dllManager.load(i.name, i.moduleType);
    } catch (const dll::Handler::error &error) {
        std::cerr << error.what() << std::endl;
    }

    const auto &loaded = m_dllManager.list();
    const auto lib_graphic = std::find_if(loaded.begin(), loaded.end(),
        [this](const auto &uid) { return this->m_dllManager.info(uid).moduleType == "graphic"; });
    if (lib_graphic != loaded.end())
        this->setWindowFromModule(*lib_graphic);
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
            e.type = graphic::Event::NONE;
            this->m_window->pollEvent(e);

            if (e.type == graphic::Event::CLOSED)
                this->m_window->close();
            if (e.type == graphic::Event::KEY_PRESSED)
                if (e.key.code == graphic::KeyBoard::F12)
                    this->m_window->takeScreenShot(
                        std::string(RESOURCE_DIR) + "screenshots/" + timeStampToString() + ".png");

        }

    }

    return APP_SUCCESS;
}

bool Core::setWindowFromModule(const dll::Manager::UID &id)
{
    if (auto module = this->m_dllManager.get(id).lock(); !module)
        return false;
    else {
        const auto f = module->load<graphic::IWindow *(*)()>("createWindow");
        if (!f) return false;

        this->m_window = std::unique_ptr<graphic::IWindow>(f());
        if (!this->m_window) return false;

        this->m_window->setFavicon(RESOURCE_DIR "icon/favicon.jpg");

        return true;
    }
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
