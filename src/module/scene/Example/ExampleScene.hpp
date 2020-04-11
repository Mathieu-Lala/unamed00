/**
 * @file src/module/scene/example/ExampleScene.hpp
 *
 */

#ifndef EXAMPLESCENE_HPP_
# define EXAMPLESCENE_HPP_

# include <scene/IScene.hpp>

class ExampleScene : public scene::IScene {
public:
    ExampleScene() = default;
    virtual ~ExampleScene() = default;

    bool onCreate(const std::unique_ptr<ecs::World> &) override;
    void onUpdate(const std::unique_ptr<ecs::World> &, float, const graphic::Event &) override;
    unsigned int getSkyColor() override;

protected:
private:

    ecs::entity::ID m_player;

};

#endif /* !EXAMPLESCENE_HPP_ */
