/**
 * @file include/data/Component.hpp
 *
 */

#ifndef COMPONENT_HPP_
# define COMPONENT_HPP_

struct CShape {

    float x, y, w, h;

    CShape(float xx, float yy, float ww, float hh) :
        x(xx), y(yy), w(ww), h(hh) { }

};

#endif /* !COMPONENT_HPP_ */
