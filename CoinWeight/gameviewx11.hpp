//
//  gameviewx11.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameviewx11_hpp
#define gameviewx11_hpp

#include <memory>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include "gameview.hpp"
#include "exception.hpp"

class GameViewX11 : public GameView {
    Display *display;
    Window mainWindow;
    Window historyWindow;
    int screen;
    GC gc;
    XEvent event;
    std::vector<unsigned long> colors;
    
    enum { Black, Red, Blue, Green, Gold };
    
    // The following numbers are sadly hard-coded
    // Need to find a way to get their value in a better way
    static const int font_width = 6;
    static const int font_height = 10;
    static const int circle_full_arc = 360 * 64;
    // Coin configurations
    static const int coinRadius = 30;
    static const int coinDist = 50;
    static const int coin0XPos = 200;
    static const int coin0YPos = 200;
    static const int coinsPerRow = 10;
    static const int defaultFGColor = Black;
    
    // Basic drawing functions
    void drawString(Window window, int x_pos, int y_pos, const std::string &msg, bool boxed = false);
    void drawCircle(Window window, int x_pos, int y_pos, unsigned int radius, int color);
    void fillCircle(Window window, int x_pos, int y_pos, unsigned int radius, int color);
    void drawRectangle(Window window, int x_pos, int y_pos, int width, int height);
    
    // Number of weighings text
    const std::string numOfWeighsText(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) const;
    
    // Window to draw
    const Window windowToDraw(const DrawingWindow window) const;
    
    // Draw weigh result text
    void drawWeighResultText(const DrawingWindow window, const WeighResult weighResult) override;
    
    // Draw coin
    const int coinColor(CoinStates::Group coinState) const;
    void drawCoin(Window window, CoinStates::Group coinState, size_t coinIndex);
    void drawCoin(DrawingWindow window, CoinStates::Group coinState, size_t coinIndex) override;
    
    // Draw return button
    void drawReturnButton() override;
    
    // Game Play screen
    void drawGamePlayHumanHighlight(const int screenHighlight, const int coinHighlight) override;
    void drawGamePlayNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) override;
    
    // Game Over screen
    void drawGameOverEndMessage(const bool isWin) override;
    void drawGameOverNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) override;
    
    // History screen
    void drawHistoryIndexText(const size_t index, const size_t numOfWeighs) override;
    void drawEmptyHistoryScreen() override;
    
    // Clear screen
    void clearMainScreen();
    void clearHistoryScreen();
    void clearScreen(const DrawingWindow window) override;

public:
    GameViewX11();
    // Main drawing functions
    void drawMainScreen(const int screenHighlight) override;
    void drawInstructionScreen() override;
    void drawCreditScreen() override;
    void drawGameOptionScreen(const int screenHighlight, const size_t numOfCoins,
            const std::string &gameLevel, const bool isHuman) override;
    
    void receiveInput() override;
    const Input lastInput() override;
};

#endif
