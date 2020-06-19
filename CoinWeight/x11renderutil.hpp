//
//  x11renderutil.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-17.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef x11renderutil_hpp
#define x11renderutil_hpp

#include "viewx11.hpp"

namespace CoinWeight {
namespace X11 {
namespace RenderUtil {

    constexpr int border = 5;
    constexpr int font_width = 6;
    constexpr int font_height = 10;
    constexpr int total_string_width(const int string_len) {
        return font_width * string_len + 2 * border;
    }
    
    constexpr int total_string_height = font_height + 2 * border;
    constexpr int one_degree_to_unit = 64;
    constexpr int circle_full_arc = 360 * one_degree_to_unit;

    inline void drawFullCircle(Renderer &renderer, const int x_pos, const int y_pos, const unsigned int diameter) {
        renderer.drawArc(x_pos, y_pos, diameter, 0, circle_full_arc);
    }
    
    inline void fillFullCircle(Renderer &renderer, const int x_pos, const int y_pos, const unsigned int diameter) {
        renderer.fillArc(x_pos, y_pos, diameter, 0, circle_full_arc);
    }
}
}
}

#endif
