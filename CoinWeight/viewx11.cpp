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



//************************** Display for Game Over
void ViewX11::displayLayoutGameOver(const bool isWin) {
    clearWindow();
    setForeground(defaultFGColor);
    
    if (isWin) {
        drawString(300, 200, "You Win!");
    } else {
        drawString(300, 200, "You Lose!");
    }
    
    const std::string &returnStr = "Return";
    
    drawString(300 + border, 500 + total_string_height - border, returnStr);
    drawRectangle(300, 500, total_string_width(returnStr.size()), total_string_height);
    
    flushDisplay();
}



//************************** Information for coin display
const size_t ViewX11::numOfCoinsPerRow() const {
    return coinsPerRow;
}

const size_t ViewX11::numOfRowsPerDisplay() const {
    return rowsDisplay;
}



//************************** Set foreground
void ViewX11::setForeground(const unsigned int colorIndex) {
    if (colorIndex >= colors.size()) throw Exception<ViewX11>("Invalid color");
    XSetForeground(display, gc, colors[colorIndex]);
}



//******************** Basic drawing functions
void ViewX11::drawString(const int x_pos, const int y_pos, const std::string &str) {
    XDrawString(display, window, gc, x_pos, y_pos, str.c_str(), str.length());
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



//******************** Draw coin
void ViewX11::drawCoin(const CoinGroup group, const size_t coinIndex,
                          const size_t row, const size_t column)
{
    const int x_pos = coin0XPos + coinOffset + coinDist * column;
    const int y_pos = coin0YPos + coinOffset + coinDist * row;
    setForeground(coinColor(group));
    fillFullCircle(x_pos, y_pos, coinDiameter);
    setForeground(Black);
    drawFullCircle(x_pos, y_pos, coinDiameter);
    setForeground(defaultFGColor);
    drawString(x_pos, y_pos, std::to_string(coinIndex + 1));
}

const int ViewX11::coinColor(const CoinGroup group) {
    switch (group) {
        case CoinGroup::NoSelect:
            return ViewX11::Gold;
        case CoinGroup::LeftWeigh:
            return ViewX11::Red;
        case CoinGroup::RightWeigh:
            return ViewX11::Blue;
        case CoinGroup::Guess:
            return ViewX11::Green;
    }
}



//******************** Helper functions for drawing weigh result
void ViewX11::drawWeighResultText(const WeighResult weighResult) {
    const int x_pos = 30;
    const int y_pos = 90;
    setForeground(Black);
    switch (weighResult) {
        case WeighResult::Start:
            drawString(x_pos, y_pos, "");
            break;
        case WeighResult::Balance:
            drawString(x_pos, y_pos, "The two groups are balanced.");
            break;
        case WeighResult::LeftHeavy:
            drawString(x_pos, y_pos, "The left group is heavier.");
            break;
        case WeighResult::RightHeavy:
            drawString(x_pos, y_pos, "The right group is heavier.");
            break;
        case WeighResult::Invalid:
            setForeground(Red);
            drawString(x_pos, y_pos, "Invalid move!");
            break;
    }
    
    setForeground(defaultFGColor);
}

void ViewX11::drawWeighingScale(const WeighResult weighResult) {
    {
        
        std::vector<XPoint> xpoints {
            {695, 60},
            {695, 120},
            {690, 120},
            {660, 140},
            {650, 160},
            {650, 180},
            {750, 180},
            {750, 160},
            {740, 140},
            {710, 120},
            {705, 120},
            {705, 60}
        };
        
        XSetForeground(display, gc, colors[Blue]);
        fillPolygon(xpoints, Nonconvex, CoordModeOrigin);
    }
    
    {
        const int radius = 20;
        XSetForeground(display, gc, colors[Green]);
        XFillArc(display, window, gc, 700 - radius, 61 - 2 * radius, radius * 2, radius * 2, 0, circle_full_arc);
    }
    
    {
        const auto anchors = [&weighResult]() -> std::pair<XPoint, XPoint> {
            const int x_base = 700;
            const int y_base = 60;
            const int x_shift = 50;
            const int y_tilt = 20;
            switch (weighResult) {
                case WeighResult::Start:
                case WeighResult::Invalid:
                case WeighResult::Balance:
                    return {{x_base - x_shift, y_base}, {x_base + x_shift, y_base}};
                case WeighResult::LeftHeavy:
                    return {{x_base - x_shift, y_base + y_tilt}, {x_base + x_shift, y_base - y_tilt}};
                case WeighResult::RightHeavy:
                    return {{x_base - x_shift, y_base - y_tilt}, {x_base + x_shift, y_base + y_tilt}};
            }
        }();
        
        const short center_anchor_y_shift = 20;
        const XPoint left_anchor = anchors.first;
        const XPoint right_anchor = anchors.second;
        const XPoint left_center = {left_anchor.x, static_cast<short>(left_anchor.y + center_anchor_y_shift)};
        const XPoint right_center = {right_anchor.x, static_cast<short>(right_anchor.y + center_anchor_y_shift)};
        
        const int one_degree_scale = 64;
        const int south_degree = 270;
        const int range = 100;
        const int radius = 25;
        const int angle1 = one_degree_scale * (south_degree - range / 2);
        const int angle2 = one_degree_scale * range;
        
        const auto weighpoints = [&left_center, &right_center]() -> std::vector<XPoint> {
            const double converter = M_PI / (double(one_degree_scale) * 180);
            const double center_x_shift = - radius * cos(double(angle1) * converter);
            const double center_y_shift = - radius * sin(double(angle1) * converter);
            return std::vector<XPoint> {
                {static_cast<short>(left_center.x - center_x_shift), static_cast<short>(left_center.y + center_y_shift)},
                {static_cast<short>(left_center.x + center_x_shift), static_cast<short>(left_center.y + center_y_shift)},
                {static_cast<short>(right_center.x - center_x_shift), static_cast<short>(right_center.y + center_y_shift)},
                {static_cast<short>(right_center.x + center_x_shift), static_cast<short>(right_center.y + center_y_shift)}
            };
        }();
        
        XSetForeground(display, gc, colors[Black]);
        XDrawLine(display, window, gc, left_anchor.x, left_anchor.y, right_anchor.x, right_anchor.y);
        XDrawLine(display, window, gc, left_anchor.x, left_anchor.y, weighpoints[0].x, weighpoints[0].y);
        XDrawLine(display, window, gc, left_anchor.x, left_anchor.y, weighpoints[1].x, weighpoints[1].y);
        XDrawLine(display, window, gc, right_anchor.x, right_anchor.y, weighpoints[2].x, weighpoints[2].y);
        XDrawLine(display, window, gc, right_anchor.x, right_anchor.y, weighpoints[3].x, weighpoints[3].y);
        
        XSetForeground(display, gc, colors[Red]);
        XFillArc(display, window, gc, left_center.x - radius, left_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        XSetForeground(display, gc, colors[Blue]);
        XFillArc(display, window, gc, right_center.x - radius, right_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        
        XSetForeground(display, gc, colors[White]);
        std::vector<XPoint> leftTrianglePoints{left_center, weighpoints[0], weighpoints[1]};
        XFillPolygon(display, window, gc, leftTrianglePoints.begin().base(), leftTrianglePoints.size(), Convex, CoordModeOrigin);
        std::vector<XPoint> rightTrianglePoints{right_center, weighpoints[2], weighpoints[3]};
        XFillPolygon(display, window, gc, rightTrianglePoints.begin().base(), rightTrianglePoints.size(), Convex, CoordModeOrigin);
        
        XSetForeground(display, gc, colors[Black]);
        XDrawArc(display, window, gc, left_center.x - radius, left_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        XDrawArc(display, window, gc, right_center.x - radius, right_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
    }
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
