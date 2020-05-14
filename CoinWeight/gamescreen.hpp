//
//  gamescreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamescreen_hpp
#define gamescreen_hpp

#include <memory>
#include "ScreenPages/allinclude.hpp"

class GameScreen {
public:
    enum class Page {
        Title,               // Play, Instruction, Credit
        Instruction,
        Credit,
        GameOption,         // Number of coins, Difficulty, Human/Computer mode
        GamePlayHuman,      // Coins, Weigh, Guess
        GamePlayComputer,   // Next Step Only
        GameOver            // Lose, Win
    };
    
    GameScreen();
    
    const Page currentScreen() const;
    const TitleScreen &titleScreen() const;
    const InstructionScreen &instructionScreen() const;
    const CreditScreen &creditScreen() const;
    const GameOptionScreen &gameOptionScreen() const;
    const GamePlayHumanScreen &gamePlayHumanScreen() const;
    const GamePlayComputerScreen &gamePlayComputerScreen() const;
    const GameOverScreen &gameOverScreen() const;
    
    // Arrow button highlight switch
    void highlightUp();
    void highlightDown();
    void highlightLeft();
    void highlightRight();
    
    // Reset highlight
    void resetHighlight();
    
    // Screen switch
    void goToTitleScreen();
    void goToInstructionScreen();
    void goToCreditScreen();
    void goToGameOptionScreen();
    void goToGamePlayHumanScreen(const size_t numOfCoins, const size_t coinsPerRow);
    void goToGamePlayComputerScreen();
    void goToGameOverScreen();

private:
    Page page;
    union {
        TitleScreen title;
        InstructionScreen instruction;
        CreditScreen credit;
        GameOptionScreen gameOption;
        GamePlayHumanScreen gamePlayHuman;
        GamePlayComputerScreen gamePlayComputer;
        GameOverScreen gameOver;
    };
};

#endif
