//
//  gameviewsdl.hpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameviewsdl_hpp
#define gameviewsdl_hpp

#include "sdlgraphics.hpp"
#include "gameview.hpp"

class GameViewSDL : public GameView {
    SDLGraphics coreGraphics;
    
    static const int width = 800;
    static const int height = 600;
    
public:
    GameViewSDL();
    
    virtual void drawMainScreen(int screenHighlight) override;
    virtual void drawInstructionScreen() override;
    virtual void drawCreditScreen() override;
    virtual void drawGameOptionScreen(
        int screenHighlight, size_t numOfCoins,
        std::string gameLevel,
        bool isHuman) override;
    virtual void drawGamePlayScreen(
        std::vector<int> coinStates,
        int highlightedCoin,
        size_t numOfComparisonsLeft,
        size_t numOfComparisonsCap,
        std::vector<std::pair<Weighing, int>> gameHistory) override;
    virtual void drawGameOverScreen(
        bool isWin,
        size_t numOfComparisonsLeft,
        size_t numOfComparisonsCap,
        std::vector<size_t> finalGuess) override;
    virtual void receiveInput() override;
    virtual const Input lastInput() const override;
};

#endif /* gameviewsdl_hpp */
