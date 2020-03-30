//
//  x11graphics.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-28.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef x11graphics_hpp
#define x11graphics_hpp

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string>
#include <vector>
#include "exception.hpp"

class X11Graphics {
    Display *display;
    Window window;
    int screen;
    GC gc;
    XEvent event;
    std::vector<unsigned long> colors;
    
    // The following numbers are sadly hard-coded
    // Need to find a way to get their value in a better way
    static const int font_width = 6;
    static const int font_height = 10;
    
public:
    X11Graphics(std::string windowName = "");
    ~X11Graphics();
    enum {
        Black = 0,
        Red,
        Blue,
        Green,
        Gold
    };
    
    static const int defaultFGColor = Black;
    
    // Drawing functions
    void drawString(int x_pos, int y_pos, const std::string &msg, bool boxed = false);
    void drawCircle(int x_pos, int y_pos, unsigned int radius, int color);
    void fillCircle(int x_pos, int y_pos, unsigned int radius, int color);
    void drawRectangle(int x_pos, int y_pos, int width, int height);
    
    // Clears display
    void clear();
    
    // Functions for events
    void receiveInput();
    const XEvent lastInput() const;
};



//***************************************************** X11 Graphics Failure
class X11GraphicsFailure : public Exception {
    const std::string headerMessage() const override;
public:
    X11GraphicsFailure(std::string coreMessage);
};

#endif
