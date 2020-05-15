//
//  gameview.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-14.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameview_hpp
#define gameview_hpp

#include "gameui.hpp"

class GameView {
public:
    GameView(std::unique_ptr<GameUI> ui);
    
    // Note: This [needs to] AND [will] be simplified
    void drawTitleScreen(const TitleScreen &screen);
    void drawInstructionScreen(const InstructionScreen &screen);
    void drawCreditScreen(const CreditScreen &screen);
    void drawGameOptionScreen(const GameOptionScreen &screen);
        
    void drawGamePlayHumanScreen(const CoinSelection &selection, const GamePlayHumanScreen &screen,
        const WeighCounter &counter, const WeighResult lastWeighResult);
    void drawGamePlayComputerScreen(const CoinSelection &selection, const GamePlayComputerScreen &screen,
        const WeighCounter &counter, const WeighResult lastWeighResult);
    void drawGameOverScreen(const GuessResult guessResult, const WeighCounter &counter);
    
    // Input handling functions
    void receiveInput();
    const Input lastInput();

private:
    std::unique_ptr<GameUI> ui;
    
    
};

#endif
