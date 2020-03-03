//
//  graphics.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-28.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef graphics_hpp
#define graphics_hpp

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "game.hpp"

class X11Graphics {
	Display *display;
	Window window;
	int screen;
	GC gc;
	unsigned long colours[10];
	
public:
	X11Graphics();
	~X11Graphics();
	
	enum {White=0, Black, Red, Green, Blue};
};

#endif
