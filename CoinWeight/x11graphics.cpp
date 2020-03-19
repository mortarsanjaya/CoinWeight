//
//  x11graphics.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-28.
//  Copyright © 2020 -. All rights reserved.
//
/*
#include "x11graphics.hpp"
#include <iostream>
#include <unistd.h>

// *************************************************************** Constructors and Destructor
X11Graphics::X11Graphics() {
	int width = 1000;
	int height = 1000;

	display = XOpenDisplay(nullptr);
	if (display == nullptr) {
		std::cerr << "Cannot open display" << std::endl;
		exit(1);
	}
	
	screen = XDefaultScreen(display);
	window = XCreateSimpleWindow(display, XRootWindow(display, screen), 0, 0,
		width, height, 1, XBlackPixel(display, screen), XWhitePixel(display, screen));
		
	XSelectInput(display, window, KeyPressMask | KeyReleaseMask |
        ButtonPressMask | ButtonReleaseMask);

	gc = XCreateGC(display, window, 0, 0);

	XColor xcolor;
	Colormap cmap;

	const size_t numColours = Max + 1;
    std::vector<std::string> color_vals = {
		"white", "black", "red", "green", "blue", "gold"
	};

	cmap = DefaultColormap(display, DefaultScreen(display));
	
	for(unsigned int i = 0; i < numColours; ++i) {
		XParseColor(display, cmap, color_vals[i].c_str(), &xcolor);
		XAllocColor(display, cmap, &xcolor);
        colors.emplace_back(xcolor.pixel);
	}

	XSetForeground(display, gc, colors[defaultFGColor]);

	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(display, window, &hints);

	XMapRaised(display, window);
	XFlush(display);
	
	sleep(1);
}

X11Graphics::~X11Graphics() {
	XFreeGC(display, gc);
	XCloseDisplay(display);
}



// *************************************************************** Drawing functions
void X11Graphics::drawString(int x_pos, int y_pos, const std::string &msg) {
	XDrawString(display, window, gc, x_pos, y_pos, msg.c_str(), msg.length());
	XFlush(display);
}

void X11Graphics::fillCircle(int x_pos, int y_pos, unsigned int radius, int color) {
    if (color > Max) throw X11GraphicsFailure{};
	XSetForeground(display, gc, colors[color]);
	XFillArc(display, window, gc, x_pos, y_pos, radius, radius, 0, 360 * 64);
	XSetForeground(display, gc, colors[defaultFGColor]);
	XFlush(display);
}
*/
