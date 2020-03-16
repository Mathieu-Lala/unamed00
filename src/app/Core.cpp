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
    for (const auto &i : m_dllManager.getAvailable())
        this->m_dllManager.load(i.name, i.moduleType);

    for (const auto &i : m_dllManager.list())
        if (const auto info = m_dllManager.info(i); info.moduleType == "graphic") {
            this->setWindowFromModule(info.uid);
            break;
        }
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
