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
#include "weighcounter.hpp"

class GameViewX11 : public GameView {
    Display *display;
    Window window;
    int screen;
    GC gc;
    XEvent event;
    std::vector<unsigned long> colors;
    
    enum { Black, White, Red, Blue, Green, Gold };
    
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
    void drawString(int x_pos, int y_pos, const std::string &msg, int color, bool boxed);
    void drawCircle(int x_pos, int y_pos, unsigned int radius, int color);
    void fillCircle(int x_pos, int y_pos, unsigned int radius, int color);
    void drawRectangle(int x_pos, int y_pos, int width, int height);
    
    // Number of weighings text
    const std::string numOfWeighsText(const WeighCounter &counter) const;
    
    // Draw weigh result text
    // HACKED INTO DRAWING THE SCALE AS WELL
    void drawWeighResultText(const WeighResult weighResult) override;
    
    // Draw coin
    const int coinColor(const CoinGroup coinState) const;
    void drawCoin(const CoinGroup coinState, const size_t coinIndex) override;
    
    // Draw return button
    void drawReturnButton() override;
    
    // Game Play Human screen
    void drawGamePlayHumanHighlight(const GamePlayHumanScreen::ScreenHighlight screenHighlight, const size_t coinHighlight) override;
    void drawGamePlayNumOfWeighs(const WeighCounter &counter) override;
    
    // Game Over screen
    void drawGameOverEndMessage(const GuessResult guessResult) override;
    void drawGameOverNumOfWeighs(const WeighCounter &counter) override;
    
    // History screen
    /*
    void drawHistoryIndexText(const size_t index, const size_t numOfWeighs) override;
    void drawEmptyHistoryScreen() override;
    */
    
    // Clear screen
    void clearScreen() override;

public:
    GameViewX11();
    // Main drawing functions
    void drawTitleScreen(const TitleScreen &titleScreen) override;
    void drawInstructionScreen(const InstructionScreen &instructionScreen) override;
    void drawCreditScreen(const CreditScreen &creditScreen) override;
    void drawGameOptionScreen(const GameOptionScreen &gameOptionScreen) override;
    
    void receiveInput() override;
    const Input lastInput() override;
};

#endif
