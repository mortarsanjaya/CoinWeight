//
//  renderutil.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-17.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef renderutil_hpp
#define renderutil_hpp

namespace CoinWeight {
namespace X11 {
namespace RenderUtil {

    enum Color {
        Black,
        White,
        Red,
        Blue,
        Green,
        Gold,
        Max = Gold
    };

    constexpr int border = 5;
    constexpr int font_width = 6;
    constexpr int font_height = 10;
    constexpr int total_string_width(const int string_len) {
        return font_width * string_len + 2 * border;
    }
    
    constexpr int total_string_height = font_height + 2 * border;
    constexpr int one_degree_to_unit = 64;
    constexpr int circle_full_arc = 360 * one_degree_to_unit;
    constexpr int defaultFGColor = Black;

}
}
}

#endif
