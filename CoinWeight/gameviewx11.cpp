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
        throw GameViewX11Failure("Cannot open display");
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
            throw GameViewX11Failure("Cannot parse color");
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
    
    XMapRaised(display, historyWindow);
    XMapRaised(display, mainWindow);
    XFlush(display);
 
    sleep(1);
}



//***************************************************** Private methods
//******************** Basic drawing functions
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
    if (color > colors.size()) throw GameViewX11Failure("Invalid color");
    XSetForeground(display, gc, colors[color]);
    XDrawArc(display, window, gc, x_pos, y_pos, radius, radius, 0, circle_full_arc);
    XSetForeground(display, gc, colors[defaultFGColor]);
    XFlush(display);
}

void GameViewX11::fillCircle(Window window, int x_pos, int y_pos, unsigned int radius, int color) {
    if (color > colors.size()) throw GameViewX11Failure("Invalid color");
    XSetForeground(display, gc, colors[color]);
    XFillArc(display, window, gc, x_pos, y_pos, radius, radius, 0, circle_full_arc);
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

//******************** Tons of helper functions
//**** Number of weighings
const std::string GameViewX11::numOfWeighsText(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) const {
    std::string numOfWeighsStr = "Number of comparisons remaining: ";
    numOfWeighsStr += std::to_string(numOfWeighsLeft);
    numOfWeighsStr += " out of ";
    numOfWeighsStr += std::to_string(numOfWeighsMax);
    return numOfWeighsStr;
}

//**** Window to draw
const Window GameViewX11::windowToDraw(DrawingWindow window) const {
    switch (window) {
        case DrawingWindow::Main:
            return mainWindow;
        case DrawingWindow::History:
            return historyWindow;
    }
}

//**** Weigh result
void GameViewX11::drawWeighResultText(const DrawingWindow window, const WeighResult weighResult) {
    drawString(windowToDraw(window), 30, 30, toString(weighResult));
}

//**** Coin
const int GameViewX11::coinColor(CoinStates::Value coinState) const {
    switch (coinState) {
        case CoinStates::Value::NoSelect:
            return GameViewX11::Gold;
        case CoinStates::Value::LeftGroup:
            return GameViewX11::Red;
        case CoinStates::Value::RightGroup:
            return GameViewX11::Blue;
        case CoinStates::Value::Guess:
            return GameViewX11::Green;
    }
}

void GameViewX11::drawCoin(Window window, CoinStates::Value coinState, size_t coinIndex) {
    const int x_pos = coin0XPos + coinDist * (coinIndex % coinsPerRow);
    const int y_pos = coin0YPos + coinDist * (coinIndex / coinsPerRow);
    fillCircle(window, x_pos, y_pos, coinRadius, coinColor(coinState));
    drawCircle(window, x_pos, y_pos, coinRadius, GameViewX11::Black);
    drawString(window, x_pos, y_pos, std::to_string(coinIndex + 1));
}

void GameViewX11::drawCoin(DrawingWindow window, CoinStates::Value coinState, size_t coinIndex) {
    drawCoin(windowToDraw(window), coinState, coinIndex);
}

//**** Return button
void GameViewX11::drawReturnButton() {
    drawString(mainWindow, 305, 515, "Return", true);
}

//**** Game Play screen
void GameViewX11::drawGamePlayHumanHighlight(const int screenHighlight, const int coinHighlight) {
    const int x_pos = coin0XPos - 6 + coinDist * (coinHighlight % coinsPerRow);
    const int y_pos = coin0YPos - 12 + coinDist * (coinHighlight / coinsPerRow);
    drawString(windowToDraw(DrawingWindow::Main), 300, 500, "Weigh", screenHighlight == 1);
    drawString(windowToDraw(DrawingWindow::Main), 300, 520, "Guess", screenHighlight == 2);
    if (screenHighlight == 0) {
        drawCircle(mainWindow, x_pos, y_pos, 15, Black); // magic number :(
    }
    
}

void GameViewX11::drawGamePlayNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) {
    drawString(mainWindow, 30, 30, numOfWeighsText(numOfWeighsLeft, numOfWeighsMax)); // magic number :(
}

//**** Game Over screen
void GameViewX11::drawGameOverEndMessage(const bool isWin) {
    drawString(mainWindow, 300, 200, isWin ? "You Win!" : "You Lose :(");
}
void GameViewX11::drawGameOverNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) {
    drawString(mainWindow, 300, 300, numOfWeighsText(numOfWeighsLeft, numOfWeighsMax));
}

//**** History screen
void GameViewX11::drawHistoryIndexText(const size_t index, const size_t numOfWeighs) {
    drawString(historyWindow, 300, 50, "Move " + std::to_string(index + 1) + " out of " + std::to_string(numOfWeighs));
}

void GameViewX11::drawEmptyHistoryScreen() {
    drawString(historyWindow, 300, 200, "You have not made any moves.");
}

//**** Clear screen
void GameViewX11::clearMainScreen() {
    XClearWindow(display, mainWindow);
    XFlush(display);
}

void GameViewX11::clearHistoryScreen() {
    XClearWindow(display, historyWindow);
    XFlush(display);
}

void GameViewX11::clearScreen(const DrawingWindow window) {
    switch (window) {
        case GameView::DrawingWindow::Main:
            clearMainScreen();
            break;
        case GameView::DrawingWindow::History:
            clearHistoryScreen();
            break;
    }
}



//***************************************************** Public methods
void GameViewX11::drawMainScreen(int screenHighlight) {
    const int stringHeight = 20;
    clearScreen(DrawingWindow::Main);
    
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
    clearScreen(DrawingWindow::Main);
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
    drawReturnButton();
}

void GameViewX11::drawCreditScreen() {
    clearScreen(DrawingWindow::Main);
    drawString(mainWindow, 300, 300, "---");
    
    sleep(1);
    drawReturnButton();
}

void GameViewX11::drawGameOptionScreen(const int screenHighlight, const size_t numOfCoins,
    const std::string &gameLevel, const bool isHuman)
{
    const int stringHeight = 20;
    clearScreen(DrawingWindow::Main);
    
    drawString(mainWindow, 300, 50, "Coin Weight");
    drawString(mainWindow, 300, 300 + stringHeight, "Number of Coins:");
    drawString(mainWindow, 300, 300 + 2 * stringHeight, "Level:");
    drawString(mainWindow, 300, 300 + 3 * stringHeight, "Mode:");
    
    drawString(mainWindow, 405, 300 + stringHeight, std::to_string(numOfCoins), screenHighlight == 0);
    drawString(mainWindow, 405, 300 + 2 * stringHeight, gameLevel, screenHighlight == 1);
    drawString(mainWindow, 405, 300 + 3 * stringHeight, isHuman ? "Human" : "Computer", screenHighlight == 2);
}

void GameViewX11::receiveInput() {
    XNextEvent(display, &event);
}

const Input GameViewX11::lastInput() {
    if (event.type == KeyPress) {
        Input::Source source;
        if (event.xkey.window == mainWindow) {
            source = Input::Source::Main;
        } else {
            source = Input::Source::History;
        }
        switch (XLookupKeysym(&(event.xkey), 0)) {
            case XK_0:          return Input(source, '0');
            case XK_1:          return Input(source, '1');
            case XK_2:          return Input(source, '2');
            case XK_3:          return Input(source, '3');
            case XK_Return:     return Input(source, '\n');
            case XK_Left:       return Input(source, Input::Arrow::Left);
            case XK_Right:      return Input(source, Input::Arrow::Right);
            case XK_Up:         return Input(source, Input::Arrow::Up);
            case XK_Down:       return Input(source, Input::Arrow::Down);
            default:            return Input(source);
        }
    } else {
        return Input(Input::Source::Main);
    }
}



//***************************************************** Game View X11 Failure
GameViewX11Failure::GameViewX11Failure(std::string coreMessage) :
    Exception(coreMessage) {}
    
const std::string GameViewX11Failure::headerMessage() const {
    return "Game View X11 Failure: ";
}
