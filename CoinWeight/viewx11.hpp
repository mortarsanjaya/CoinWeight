//
//  viewx11.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef viewx11_hpp
#define viewx11_hpp

#include <memory>
#include <string>
#include <array>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

#include "input.hpp"
#include "x11color.hpp"
#include "exception.hpp"

namespace CoinWeight {
namespace X11 {



class Renderer final {
public:
    Renderer();
    ~Renderer();
    
    // Input handling functions
    const Input nextInput();
    
    // Set foreground
    void setForeground(const unsigned int colorIndex);
    
    void drawLine(const int x1, const int y1, const int x2, const int y2);
    
    void drawString(const int x_pos, const int y_pos, const std::string &str);
    
    // Assumption: NEVER DRAW WITH NON-CIRCLE ELLIPSES
    void drawArc(const int x_pos, const int y_pos, const int diameter, const int angle_init, const int angle_size);
    void fillArc(const int x_pos, const int y_pos, const int diameter, const int angle_init, const int angle_size);
    
    
    void drawFullCircle(const int x_pos, const int y_pos, const unsigned int diameter);
    void fillFullCircle(const int x_pos, const int y_pos, const unsigned int diameter);
    
    // x_pos and y_pos for rectangle is in its upper-left corner position
    // Draws with the current foreground color
    void drawRectangle(const int x_pos, const int y_pos, const int width, const int height);
    void fillPolygon(std::vector<XPoint> xpoints, int shape, int mode);
    
    // Clear window
    void clearWindow();
    
    // Flush display
    void flushDisplay();

private:
    
    Display *display;
    Window window;
    int screen;
    GC gc;
    XEvent event;
    
    std::array<unsigned long, Color::Max + 1> colors;
};



}
}


#endif
