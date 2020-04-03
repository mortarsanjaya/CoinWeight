//
//  gameviewx11.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameviewx11.hpp"
#include <iostream>

//***************************************************** Constructor
GameViewX11::GameViewX11() {
    const int width = 800;
    const int height = 800;

    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        throw X11GraphicsFailure("Cannot open display");
    }
    
    screen = XDefaultScreen(display);
    mainWindow = XCreateSimpleWindow(display, XRootWindow(display, screen), 0, 0,
        width, height, 1, XBlackPixel(display, screen), XWhitePixel(display, screen));
    historyWindow = XCreateSimpleWindow(display, XRootWindow(display, screen), 0, 0,
        width, height, 1, XBlackPixel(display, screen), XWhitePixel(display, screen));
        
    XSelectInput(display, mainWindow, KeyPressMask);
    XSelectInput(display, historyWindow, KeyPressMask);
    
    XStoreName(display, mainWindow, "Coin Weight");
    XStoreName(display, historyWindow, "Coin Weight History");
    
    gc = XCreateGC(display, mainWindow, 0, 0);

    XColor xcolor;
    Colormap cmap;

    std::vector<std::string> colorVals = {
        "black", "red", "blue", "green", "gold"
    };
    
    cmap = DefaultColormap(display, DefaultScreen(display));
    
    for (unsigned int i = 0; i < colorVals.size(); ++i) {
        if (XParseColor(display, cmap, colorVals[i].c_str(), &xcolor) == 0) {
            throw X11GraphicsFailure("Cannot parse color");
        }
        XAllocColor(display, cmap, &xcolor);
        colors.emplace_back(xcolor.pixel);
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
    XSetNormalHints(display, mainWindow, &hints);
    XSetNormalHints(display, historyWindow, &hints);
    
    XMapRaised(display, mainWindow);
    XMapRaised(display, historyWindow);
    XFlush(display);
 
    sleep(1);
}



//***************************************************** Private methods
void GameViewX11::drawString(Window window, int x_pos, int y_pos, const std::string &msg, bool boxed) {
    XDrawString(display, window, gc, x_pos, y_pos, msg.c_str(), msg.length());
    if (boxed) {
        const int border_dist = font_width;
        drawRectangle(window, x_pos - font_width, y_pos - font_height - font_width,
            font_width * msg.length() + 2 * border_dist,
            font_height + 2 * font_width);
    }
    XFlush(display);
}

void GameViewX11::drawCircle(Window window, int x_pos, int y_pos, unsigned int radius, int color) {
    if (color > colors.size()) throw X11GraphicsFailure("Invalid color");
    XSetForeground(display, gc, colors[color]);
    XDrawArc(display, window, gc, x_pos, y_pos, radius, radius, 0, 360 * 64);
    XSetForeground(display, gc, colors[defaultFGColor]);
    XFlush(display);
}

void GameViewX11::fillCircle(Window window, int x_pos, int y_pos, unsigned int radius, int color) {
    if (color > colors.size()) throw X11GraphicsFailure("Invalid color");
    XSetForeground(display, gc, colors[color]);
    XFillArc(display, window, gc, x_pos, y_pos, radius, radius, 0, 360 * 64);
    XSetForeground(display, gc, colors[defaultFGColor]);
    XFlush(display);
}

void GameViewX11::drawRectangle(Window window, int x_pos, int y_pos, int width, int height) {
    XDrawLine(display, window, gc, x_pos, y_pos, x_pos + width, y_pos);
    XDrawLine(display, window, gc, x_pos, y_pos, x_pos, y_pos + height);
    XDrawLine(display, window, gc, x_pos + width, y_pos, x_pos + width, y_pos + height);
    XDrawLine(display, window, gc, x_pos, y_pos + height, x_pos + width, y_pos + height);
    XFlush(display);
}

const int GameViewX11::coinColor(CoinStates::Value coinState) const {
    switch (coinState) {
        case CoinStates::Value::NoSelect:
            return X11Graphics::Gold;
        case CoinStates::Value::LeftGroup:
            return X11Graphics::Red;
        case CoinStates::Value::RightGroup:
            return X11Graphics::Blue;
        case CoinStates::Value::Guess:
            return X11Graphics::Green;
    }
}

void GameViewX11::drawCoin(Window window, CoinStates::Value coinState, size_t coinIndex) {
    const int x_pos = 200 + 50 * (coinIndex % 10);
    const int y_pos = 200 + 50 * (coinIndex / 10);
    fillCircle(window, x_pos, y_pos, coinRadius, coinColor(coinState));
    drawCircle(window, x_pos, y_pos, coinRadius, X11Graphics::Black);
    drawString(window, x_pos, y_pos, std::to_string(coinIndex + 1));
}

void GameViewX11::drawCoins(Window window, CoinStates coinStates) {
    for (int i = 0; i < coinStates.size(); ++i) {
        drawCoin(window, coinStates.at(i), i);
    }
}

void GameViewX11::clear(Window window) {
    XClearWindow(display, window);
    XFlush(display);
}



//***************************************************** Public methods
void GameViewX11::drawMainScreen(int screenHighlight) {
    const int stringHeight = 20;
    clear(mainWindow);
    
    drawString(mainWindow, 300, 50, "Coin Weight");
    drawString(mainWindow, 300, 300 + stringHeight, "Play", screenHighlight == 0);
    drawString(mainWindow, 300, 300 + 2 * stringHeight, "Instructions", screenHighlight == 1);
    drawString(mainWindow, 300, 300 + 3 * stringHeight, "Credits", screenHighlight == 2);
}

void GameViewX11::drawInstructionScreen() {
    const int x_pos_page_name = 300;
    int y_pos = 100;
    const int x_pos_page_instr = 320;
    const int y_pos_incr = 20;
    clear(mainWindow);
    std::vector<std::vector<std::string>> displayStrings;
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Main Page:",
        "Press Up/Down to select buttons.",
        "Press Enter/Return to switch page."
    });
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Option Page:",
        "Press Left/Right to change selected option.",
        "Press Enter/Return to start game."
    });
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Game Play Page (Human play):",
        "Press arrow keys to select coins.",
        "Press '1' to move selected coin to the red (left) set.",
        "Press '2' to move selected coin to the blue (right) set.",
        "Press '2' to move selected coin to the green (guess) set.",
        "Press 'w' to weigh.",
        "Press 'g' to guess.",
        "Press 'h' to switch to history."
    });
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Game Play Page (Computer play):",
        "Press Enter/Return to trigger the computer's move.",
        "Press 'h' to switch to history."
    });
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Game History Page:",
        "Press Enter/Return to go back to the game play page.",
        "Press Left/Right to switch between previous moves."
    });
    
        
    for (auto pageStrList : displayStrings) {
        for (int i = 0; i < pageStrList.size(); ++i) {
            drawString(mainWindow, i == 0 ? x_pos_page_name : x_pos_page_instr, y_pos, pageStrList[i]);
            y_pos += y_pos_incr;
        }
    }
    
    sleep(1);
    
    drawString(mainWindow, 305, 515, "Return");
    drawRectangle(mainWindow, 300, 500, 50, 20);
}

void GameViewX11::drawCreditScreen() {
    clear(mainWindow);
    drawString(mainWindow, 300, 300, "---");
    
    sleep(1);
    
    drawString(mainWindow, 305, 515, "Return");
    drawRectangle(mainWindow, 300, 500, 50, 20);
}

void GameViewX11::drawGameOptionScreen(int screenHighlight, size_t numOfCoins,
    std::string gameLevel, bool isHuman)
{
    const int stringHeight = 20;
    clear(mainWindow);
    
    drawString(mainWindow, 300, 50, "Coin Weight");
    drawString(mainWindow, 300, 300 + stringHeight, "Number of Coins:");
    drawString(mainWindow, 300, 300 + 2 * stringHeight, "Level:");
    drawString(mainWindow, 300, 300 + 3 * stringHeight, "Mode:");
    
    drawString(mainWindow, 405, 300 + stringHeight, std::to_string(numOfCoins), screenHighlight == 0);
    drawString(mainWindow, 405, 300 + 2 * stringHeight, gameLevel, screenHighlight == 1);
    drawString(mainWindow, 405, 300 + 3 * stringHeight, isHuman ? "Human" : "Computer", screenHighlight == 2);
}

void GameViewX11::drawGamePlayScreen(
    CoinStates coinStates,
    int highlightedCoin,
    size_t numOfComparisonsLeft,
    size_t numOfComparisonsCap,
    WeighResult lastWeighResult)
{
    clear(mainWindow);
    
    for (size_t i = 0; i < coinStates.size(); ++i) {
        drawCoin(mainWindow, coinStates.at(i), i);
    }
    
    const std::string numOfCompLeftStr = std::to_string(numOfComparisonsLeft);
    const std::string numOfCompCapStr = std::to_string(numOfComparisonsCap);
    drawString(mainWindow, 30, 30, "Number of comparisons remaining: " + numOfCompLeftStr +
                                    " out of " + numOfCompCapStr);
    if (numOfComparisonsLeft == 0) {
        drawString(mainWindow, 30, 50, "No more comparisons!");
    }
    drawString(mainWindow, 30, 100, "Result of last move:");
    const int x_pos = 194 + 50 * (highlightedCoin % 10);
    const int y_pos = 188 + 50 * (highlightedCoin / 10);
    drawCircle(mainWindow, x_pos, y_pos, 15, Black);
    
    if (numOfComparisonsLeft != numOfComparisonsCap) {
        drawString(mainWindow, 30, 120, toString(lastWeighResult));
    }
}

void GameViewX11::drawGameOverScreen(
    bool isWin,
    size_t numOfComparisonsLeft,
    size_t numOfComparisonsCap)
{
    clear(mainWindow);
    clear(historyWindow);
    
    drawString(mainWindow, 300, 200, isWin ? "You Win!" : "You Lose :(");
    drawString(mainWindow, 300, 300,
        "Number of comparisons left: " + std::to_string(numOfComparisonsLeft) +
        " out of " + std::to_string(numOfComparisonsCap));
    /*
    coreGraphics.drawString(300, 400, "Final guess: ");
    std::string guessStr;
    for (size_t n : finalGuess) {
        guessStr += (std::to_string(n + 1) + " ");
    }
    coreGraphics.drawString(300, 420, guessStr);
    */
}

void GameViewX11::drawGameHistoryScreen(const History &gameHistory) {
    clear(historyWindow);
    
    drawString(historyWindow, 300, 30, "History");
    if (gameHistory.empty()) {
        drawString(historyWindow, 300, 200, "You have not made any moves.");
    } else {
        drawString(historyWindow, 300, 50, "Move " + std::to_string(gameHistory.currentIndex()));
        drawCoins(historyWindow, gameHistory.getRecord().coinStates());
        drawString(historyWindow, 30, 120, toString(gameHistory.getRecord().result()));
    }
}

void GameViewX11::receiveInput() {
    XNextEvent(display, &event);
}

const Input GameViewX11::lastInput() {
    if (event.type == KeyPress) {
        switch (XLookupKeysym(&(event.xkey), 0)) {
            case XK_0:          return Input('0');
            case XK_1:          return Input('1');
            case XK_2:          return Input('2');
            case XK_3:          return Input('3');
            case XK_w:          return Input('w');
            case XK_g:          return Input('g');
            case XK_h:          return Input('h');
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
