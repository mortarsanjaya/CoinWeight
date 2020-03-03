//
//  graphics.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-28.
//  Copyright © 2020 -. All rights reserved.
//

#include "x11graphics.hpp"
#include <iostream>
#include <unistd.h>

X11Graphics::X11Graphics() {
	int width = 600;
	int height = 600;

	display = XOpenDisplay(nullptr);
	if (display == nullptr) {
		std::cerr << "Cannot open display" << std::endl;
		exit(1);
	}
	
	screen = XDefaultScreen(display);
	window = XCreateSimpleWindow(display, XRootWindow(display, screen), 10, 10,
		width, height, 1, XBlackPixel(display, screen), XWhitePixel(display, screen));
		
	XSelectInput(display, window, ExposureMask | KeyPressMask);

	Pixmap pix = XCreatePixmap(
		display, window, width, height,
		DefaultDepth(display, DefaultScreen(display))
	);

	gc = XCreateGC(display, pix, 0, 0);

	XColor xcolour;
	Colormap cmap;

	const size_t numColours = 5;
	char color_vals[numColours][10] = {
		"white", "black", "red",
		"green", "blue"
	};

	cmap = DefaultColormap(display, DefaultScreen(display));
	
	for(unsigned int i = 0; i < numColours; ++i) {
		XParseColor(display, cmap, color_vals[i], &xcolour);
		XAllocColor(display, cmap, &xcolour);
		colours[i] = xcolour.pixel;
	}

	XSetForeground(display, gc, colours[Black]);

	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(display, window, &hints);

	XMapRaised(display, window);
	XFlush(display);
	
	sleep(1);
	
	std::string msg = "History:";
	XDrawString(display, window, gc, 20, 20, msg.c_str(), msg.length());
	XFlush(display);
}

X11Graphics::~X11Graphics() {
	XFreeGC(display, gc);
	XCloseDisplay(display);
}
