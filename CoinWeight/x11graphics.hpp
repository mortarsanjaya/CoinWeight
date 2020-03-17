//
//  x11graphics.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-28.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef graphics_hpp
#define graphics_hpp

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
    
    void drawRectangle(int x_pos, int y_pos, int height, int width);
	
public:
	X11Graphics(std::string windowName = "");
	~X11Graphics();
	enum {
        White=0,
        Black,
        Red,
        Green,
        Blue,
        Gold,
        Max = Gold
    };
	static const int defaultFGColor = Blue;
	
    void clear();
	void drawString(int x_pos, int y_pos, const std::string &msg);
    void drawCircle(int x_pos, int y_pos, unsigned int radius, int color);
	void fillCircle(int x_pos, int y_pos, unsigned int radius, int color);
    void drawKeyboardInputWindow(int x_pos, int y_pos, int width, int height);
    
    // char readKeyboardInput();
};

class X11GraphicsFailure : public Exception {
    const std::string headerMessage() const override;
public:
    X11GraphicsFailure(std::string coreMessage);
};

#endif
