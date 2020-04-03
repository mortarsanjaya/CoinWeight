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
#include "gameview.hpp"
#include "x11graphics.hpp"

class GameViewX11 : public GameView {
    Display *display;
    Window mainWindow;
    Window historyWindow;
    int screen;
    GC gc;
    XEvent event;
    std::vector<unsigned long> colors;
    
    // The following numbers are sadly hard-coded
    // Need to find a way to get their value in a better way
    static const int font_width = 6;
    static const int font_height = 10;
    
    enum {
        Black = 0,
        Red,
        Blue,
        Green,
        Gold
    };
    
    static const int defaultFGColor = Black;
    
    void drawString(Window window, int x_pos, int y_pos, const std::string &msg, bool boxed = false);
    void drawCircle(Window window, int x_pos, int y_pos, unsigned int radius, int color);
    void fillCircle(Window window, int x_pos, int y_pos, unsigned int radius, int color);
    void drawRectangle(Window window, int x_pos, int y_pos, int width, int height);
    
    const int coinColor(CoinStates::Value coinState) const;
    
    void drawCoin(Window window, CoinStates::Value coinState, size_t coinIndex);
    void drawCoins(Window window, CoinStates coinStates);
    
    void clear(Window window);
    
    static const int coinRadius = 30;

public:
    GameViewX11();
    void drawMainScreen(int screenHighlight) override;
    void drawInstructionScreen() override;
    void drawCreditScreen() override;
    void drawGameOptionScreen(int screenHighlight, size_t numOfCoins,
            std::string gameLevel, bool isHuman) override;
    void drawGamePlayScreen(CoinStates coinStates, int highlightedCoin,
        size_t numOfWeighsLeft, size_t numOfWeighsCap, WeighResult lastWeighResult) override;
    void drawGameOverScreen(bool isWin, size_t numOfComparisonsLeft,
        size_t numOfComparisonsCap) override;

    void drawGameHistoryScreen(const History &gameHistory) override;
    
    void receiveInput() override;
    const Input lastInput() override;
};

#endif
