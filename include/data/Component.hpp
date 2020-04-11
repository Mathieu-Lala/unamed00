/**
 * @file include/data/Component.hpp
 *
 */

#ifndef COMPONENT_HPP_
# define COMPONENT_HPP_

# include <functional>

# include <graphic/Event.hpp>

struct CRectShape {

    float x, y, w, h;

    CRectShape(float xx, float yy, float ww, float hh) :
        x(xx), y(yy), w(ww), h(hh) { }

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

#endif /* !COMPONENT_HPP_ */
