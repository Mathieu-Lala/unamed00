/**
 * @file include/app/Core.hpp
 *
 */

#ifndef CORE_HPP_
# define CORE_HPP_

# include <atomic>

# include <dll/Manager.hpp>
# include <ecs/ECS.hpp>

# include <graphic/IWindow.hpp>
# include <scene/IScene.hpp>

# include "app/shell/Parser.hpp"
# include "app/shell/Reader.hpp"

class Core {
public:
    Core();
    ~Core() = default;

    void stop() noexcept;
    bool isRunning() const noexcept;

    dll::Manager &getDllManager() noexcept;

    int start();

    bool setWindowFromModule(const dll::Manager::UID &);
    bool setSceneFromModule(const dll::Manager::UID &);

protected:
private:

    std::atomic<bool> m_is_running;

    shell::Parser m_shellParser;
    shell::Reader m_shellReader;

    dll::Manager m_dllManager;

    std::unique_ptr<ecs::World> m_world;

    using WindowPtr = std::unique_ptr<graphic::IWindow, graphic::IWindow::Dtor>;
    WindowPtr m_window;

    void draw(float elapsedTime);

    using ScenePtr = std::unique_ptr<scene::IScene, scene::IScene::Dtor>;
    ScenePtr m_scene;

};

#endif /* !CORE_HPP_ */
