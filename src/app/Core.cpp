/**
 * @file src/app/Core.cpp
 *
 */

#include <iostream>

#include <data/Component.hpp>
#include <utils/utils.hpp>

#include "app/Core.hpp"

Core::Core() :
    m_is_running    (true),
    m_shellParser   (*this),
    m_shellReader   (this->m_shellParser),
    m_world         (std::make_unique<ecs::World>()),
    m_window        (nullptr, nullptr),
    m_scene         (nullptr, nullptr)
{
    try {
        for (const auto &i : m_dllManager.getAvailable())
            if (i.moduleType != "<none>")
                this->m_dllManager.load(i.name, i.moduleType);
    } catch (const dll::Handler::error &error) {
        std::cerr << error.what() << std::endl;
    }

    const auto &loaded = m_dllManager.list();
    const auto get = [this, &loaded](const std::string_view type) {
        return std::find_if(loaded.begin(), loaded.end(), [this, &type](const auto &uid) {
            return this->m_dllManager.info(uid).moduleType == type;
        });
    };

    if (auto module = get("graphic"); module != loaded.end())
        this->setWindowFromModule(*module);
    if (auto module = get("scene"); module != loaded.end())
        this->setSceneFromModule(*module);
}

int Core::start()
{
    using namespace std::chrono;

    float elapsedTime = 0.0f;
    graphic::Event e;

    while (this->isRunning()) {
        const auto start = system_clock::now();

        this->m_shellReader.read();

        e = {};

        if (this->m_window) {

            this->m_window->clear(this->m_scene ? this->m_scene->getSkyColor() : 0x000000FFu);
            this->m_window->draw(this->m_world);
            this->m_window->render();

            if (this->m_window->pollEvent(e))
                this->handleEvent(e);
        }

        if (this->m_scene)
            this->m_scene->onUpdate(this->m_world, elapsedTime, e);

        elapsedTime = duration_cast<milliseconds>(system_clock::now() - start).count();
    }

    return APP_SUCCESS;
}

void Core::handleEvent(const graphic::Event &e)
{
    if (e.type == graphic::Event::CLOSED)
        this->m_window->close();

    if (e.type == graphic::Event::KEY_PRESSED)
        if (e.key.code == graphic::KeyBoard::F12) {
            const auto file = std::string(RESOURCE_DIR) + "screenshots/" + timeStampToString() + ".png";
            std::cout << "Take a screenshot in " << file << " " <<
                (this->m_window->takeScreenShot(file) ? "success" : "failed") << std::endl;
        }
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
            this->m_window.reset(nullptr);
            return false;
        }

        const auto name_f = module->load<const char * (*)()>("getName");
        const auto title = std::string(name_f ? name_f() : "Unknown") + " - RenderWindow - " PROJECT_NAME "\\v" PROJECT_VERSION;
        this->m_window->setTitle(title);

        this->m_window->setFavicon(RESOURCE_DIR "icon/favicon.png");
        this->m_window->setSize(1080, 760);

        return true;
    }
}

bool Core::setSceneFromModule(const dll::Manager::UID &id)
{
    if (auto module = this->m_dllManager.get(id).lock(); !module)
        return false;
    else {
        const auto ctor = module->load<scene::IScene::Ctor>("createScene");
        const auto dtor = module->load<scene::IScene::Dtor>("destroyScene");
        if (!ctor || !dtor) return false;

        this->m_scene = ScenePtr(ctor(), dtor);
        if (!this->m_scene) return false;

        this->m_world->clearAll();
        if (!this->m_scene->onCreate(this->m_world)) {
            std::cerr << "Failed to initialize the scene" << std::endl;
            this->m_scene.reset(nullptr);
            return false;
        }

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
