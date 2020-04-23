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
    static constexpr int font_width = 6;
    static constexpr int font_height = 10;
    static constexpr int circle_full_arc = 360 * 64;
    // Coin configurations
    static constexpr int coinRadius = 30;
    static constexpr int coinDist = 50;
    static constexpr int coin0XPos = 200;
    static constexpr int coin0YPos = 200;
    static constexpr int coinsPerRow = 10;
    static constexpr int defaultFGColor = Black;
    
    // Basic drawing functions
    void drawString(DrawingWindow window, int x_pos, int y_pos, const std::string &msg, int color, bool boxed);
    void drawCircle(DrawingWindow window, int x_pos, int y_pos, unsigned int radius, int color);
    void fillCircle(DrawingWindow window, int x_pos, int y_pos, unsigned int radius, int color);
    void drawRectangle(DrawingWindow window, int x_pos, int y_pos, int width, int height);
    
    // Number of weighings text
    const std::string numOfWeighsText(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) const;
    
    // Window to draw
    const Window windowToDraw(const DrawingWindow window) const;
    
    // Draw weigh result text
    void drawWeighResultText(const DrawingWindow window, const WeighResult weighResult) override;
    
    // Draw coin
    const int coinColor(CoinGroup coinState) const;
    void drawCoin(DrawingWindow window, CoinGroup coinState, size_t coinIndex) override;
    
    // Draw return button
    void drawReturnButton() override;
    
    // Game Play Human screen
    void drawGamePlayHumanHighlight(const GamePlayHumanScreen::ScreenHighlight screenHighlight, const size_t coinHighlight) override;
    void drawGamePlayNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) override;
    
    // Game Over screen
    void drawGameOverEndMessage(const GuessResult guessResult) override;
    void drawGameOverNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) override;
    
    // History screen
    void drawHistoryIndexText(const size_t index, const size_t numOfWeighs) override;
    void drawEmptyHistoryScreen() override;
    
    // Clear screen
    void clearMainScreen();
    void clearHistoryScreen();
    void clearScreen(const DrawingWindow dwindow) override;

public:
    GameViewX11();
    // Main drawing functions
    void drawTitleScreen(const TitleScreen::Highlight screenHighlight) override;
    void drawInstructionScreen() override;
    void drawCreditScreen() override;
    void drawGameOptionScreen(const GameOptionScreen::Highlight screenHighlight,
        const GameSettings &currSettings) override;
    
    void receiveInput() override;
    const Input lastInput() override;
};

#endif
