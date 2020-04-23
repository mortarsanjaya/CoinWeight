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
    const TitleScreen::Highlight titleHighlight() const;
    const InstructionScreen::Highlight instructionHighlight() const;
    const CreditScreen::Highlight creditHighlight() const;
    const GameOptionScreen::Highlight gameOptionHighlight() const;
    const GameSettings &gameOptionSettings() const;
    const GamePlayHumanScreen::ScreenHighlight gamePlayHumanScreenHighlight() const;
    const size_t gamePlayHumanCoinHighlight() const;
    const GamePlayComputerScreen::Highlight gamePlayComputerHighlight() const;
    const GameOverScreen::Highlight gameOverHighlight() const;
    
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
