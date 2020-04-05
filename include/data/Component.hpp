/**
 * @file include/data/Component.hpp
 *
 */

#ifndef COMPONENT_HPP_
# define COMPONENT_HPP_

struct CRectShape {

    float x, y, w, h;

    CRectShape(float xx, float yy, float ww, float hh) :
        x(xx), y(yy), w(ww), h(hh) { }

};

struct CVelocity {

    float x, y;

    CVelocity(float xx, float yy) : x(xx), y(yy) { }

};

#endif /* !COMPONENT_HPP_ */
