//
//  viewx11.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "viewx11.hpp"
#include "exception.hpp"
#include <utility>
#include <cmath>
#include <vector>

using namespace CoinWeight;

//************************** Constructor and Destructor
ViewX11::ViewX11() {
    const int width = 800;
    const int height = 800;

    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        throw Exception<ViewX11>("Cannot open display");
    }
    
    screen = XDefaultScreen(display);
    window = XCreateSimpleWindow(display, XRootWindow(display, screen), 0, 0,
        width, height, 1, XBlackPixel(display, screen), XWhitePixel(display, screen));
        
    XSelectInput(display, window, KeyPressMask);
    
    XStoreName(display, window, "Coin Weight");
    
    gc = XCreateGC(display, window, 0, 0);

    XColor xcolor;
    Colormap cmap;

    std::vector<std::string> colorVals = {
        "black", "white", "red", "blue", "green", "gold"
    };
    
    cmap = DefaultColormap(display, screen);
    
    for (unsigned int i = 0; i <= Max; ++i) {
        if (XParseColor(display, cmap, colorVals[i].c_str(), &xcolor) == 0) {
            throw Exception<ViewX11>("Cannot parse color");
        }
        XAllocColor(display, cmap, &xcolor);
        colors[i] = xcolor.pixel;
    }

    XSetForeground(display, gc, colors[defaultFGColor]);

    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = height;
    hints.min_height = height;
    hints.max_height = height;
    hints.width = hints.base_width = width;
    hints.min_width = width;
    hints.max_width = width;
    XSetNormalHints(display, window, &hints);
    
    XMapRaised(display, window);
    XFlush(display);
 
    sleep(1);
}

ViewX11::~ViewX11() {
    XFreeGC(display, gc);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}



//************************** Set foreground
void ViewX11::setForeground(const unsigned int colorIndex) {
    if (colorIndex >= colors.size()) throw Exception<ViewX11>("Invalid color");
    XSetForeground(display, gc, colors[colorIndex]);
}



//******************** Basic drawing functions
void ViewX11::drawLine(const int x1, const int y1, const int x2, const int y2) {
    XDrawLine(display, window, gc, x1, y1, x2, y2);
}

void ViewX11::drawString(const int x_pos, const int y_pos, const std::string &str) {
    XDrawString(display, window, gc, x_pos, y_pos, str.c_str(), str.length());
}

void ViewX11::drawArc(const int x_pos, const int y_pos, const int diameter, const int angle_init, const int angle_size) {
    XDrawArc(display, window, gc, x_pos, y_pos, diameter, diameter, angle_init, angle_size);
}

void ViewX11::fillArc(const int x_pos, const int y_pos, const int diameter, const int angle_init, const int angle_size) {
    XFillArc(display, window, gc, x_pos, y_pos, diameter, diameter, angle_init, angle_size);
}

void ViewX11::drawFullCircle(const int x_pos, const int y_pos, const unsigned int diameter) {
    XDrawArc(display, window, gc, x_pos, y_pos, diameter, diameter, 0, circle_full_arc);
}

void ViewX11::fillFullCircle(const int x_pos, const int y_pos, const unsigned int diameter) {
    XFillArc(display, window, gc, x_pos, y_pos, diameter, diameter, 0, circle_full_arc);
}

void ViewX11::drawRectangle(const int x_pos, const int y_pos, const int width, const int height) {
    XDrawLine(display, window, gc, x_pos, y_pos, x_pos + width, y_pos);
    XDrawLine(display, window, gc, x_pos, y_pos, x_pos, y_pos + height);
    XDrawLine(display, window, gc, x_pos + width, y_pos, x_pos + width, y_pos + height);
    XDrawLine(display, window, gc, x_pos, y_pos + height, x_pos + width, y_pos + height);
}

void ViewX11::fillPolygon(std::vector<XPoint> xpoints, int shape, int mode) {
    XFillPolygon(display, window, gc, xpoints.begin().base(), xpoints.size(), shape, mode);
}



//******************** Clear window
void ViewX11::clearWindow() {
    XClearWindow(display, window);
}



//******************** Flush display
void ViewX11::flushDisplay() {
    XFlush(display);
}





//************************** Input producing
const Input ViewX11::nextInput() {
    
    if (XCheckWindowEvent(display, window, KeyPressMask, &event) == 0) {
        return Input();
    }
    
    if (event.type == KeyPress) {
        switch (XLookupKeysym(&(event.xkey), 0)) {
            case XK_0:          return Input('0');
            case XK_1:          return Input('1');
            case XK_2:          return Input('2');
            case XK_3:          return Input('3');
            case XK_Return:     return Input('\n');
            case XK_Left:       return Input(Input::Arrow::Left);
            case XK_Right:      return Input(Input::Arrow::Right);
            case XK_Up:         return Input(Input::Arrow::Up);
            case XK_Down:       return Input(Input::Arrow::Down);
            default:            return Input();
        }
    } else {
        return Input();
    }
}





//************************** Game View X11 Exception header message
template<> const std::string Exception<ViewX11>::headerMessage() const {
    return "Game View X11 Failure: ";
}
