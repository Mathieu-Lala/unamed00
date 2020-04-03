/**
 * @file src/app/Core.cpp
 *
 */

#include <iostream>

#include "app/Core.hpp"
#include "utils/utils.hpp"

#include "data/Component.hpp"

Core::Core() :
    m_is_running    (true),
    m_shellParser   (*this),
    m_shellReader   (this->m_shellParser),
    m_window        (nullptr, nullptr)
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
    auto world = std::make_unique<ecs::World>();

    auto handler = world->createEntity().add<CShape>(-0.5, -0.5, 1, 1);

    world->flush();

    while (this->isRunning()) {

        this->m_shellReader.read();

        if (this->m_window) {

            this->m_window->clear(0x000000FFu);
            this->m_window->draw(world);
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
        const auto ctor = module->load<graphic::IWindow::Ctor>("createWindow");
        const auto dtor = module->load<graphic::IWindow::Dtor>("destroyWindow");
        if (!ctor || !dtor) return false;

        this->m_window = WindowPtr(ctor(), dtor);
        if (!this->m_window) return false;

        if (!this->m_window->init()) {
            std::cerr << "Failed to initialize the window" << std::endl;
            return false;
        }

        const auto name_f = module->load<std::string(*)()>("getName");
        const auto title = (name_f ? name_f() : "Unknown") + " - RenderWindow - " PROJECT_NAME "\\v" PROJECT_VERSION;
        this->m_window->setTitle(title);

        this->m_window->setFavicon(RESOURCE_DIR "icon/favicon.png");
        this->m_window->setSize(1080, 760);

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
