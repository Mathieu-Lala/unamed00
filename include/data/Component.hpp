/**
 * @file include/data/Component.hpp
 *
 */

#ifndef COMPONENT_HPP_
# define COMPONENT_HPP_

# include <functional>

# include <graphic/Event.hpp>

# include "ecs/internal/Component.hpp"

namespace data {

struct CRectShape {

    float x, y, w, h;
    CRectShape(float xx, float yy, float ww, float hh) :
        x(xx), y(yy), w(ww), h(hh) { }

    constexpr bool collide(const CRectShape *other) const noexcept
    {
        return other && this != other &&
            this->x < other->x + other->w && this->x + this->w > other->x &&
            this->y < other->y + other->h && this->h + this->y > other->y;
    }

};

struct CVelocity {

    float x, y;
    CVelocity(float xx, float yy) : x(xx), y(yy) { }

};

struct CWithEvent {

    using Callback = std::function<void(const graphic::Event &)>;
    Callback callback;
    CWithEvent(const Callback &f) : callback(f) { }

};

struct CColor {

    float r, g, b, a;

    CColor(float rr, float gg, float bb, float aa) :
        r(rr), g(gg), b(bb), a(aa) { }

};

namespace {
#define INIT_MASK(c) auto mask##c = ecs::component::getMask<c>();

INIT_MASK(CRectShape);
INIT_MASK(CVelocity);
INIT_MASK(CWithEvent);
INIT_MASK(CColor);

#undef INIT_MASK
}

} // namespace data

#endif /* !COMPONENT_HPP_ */
