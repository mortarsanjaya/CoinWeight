//
//  gameplaycomputer.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplaycomputer_hpp
#define gameplaycomputer_hpp

#include "singleplayergame.hpp"

#include "gamescreen.hpp"
#include "tablenavigator.hpp"
#include "coinset.hpp"
#include "computer.hpp"
#include "gamelevel.hpp"

#include "coinselection.hpp"
#include "history.hpp"
#include "weighcounter.hpp"

namespace CoinWeight {



class GamePlayComputer final : public SinglePlayerGame {
public:
    enum class ButtonHighlight {
        NextMove
    };
    
    GamePlayComputer(const size_t nCoinsTotal, const GameLevel level,
        const size_t nRowsDisplay, const size_t nCoinsPerRow);
    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(ViewX11 &view) const override;
    
private:
    ButtonHighlight buttonHighlight;
    TableNavigator coinNavigator;
    bool isOnButtonHighlight;
    
    CoinSet coinSet;
    CoinSelection selection;
    History history;
    
    std::unique_ptr<Computer> computer;
    
    WeighResult lastResult;
    
    WeighCounter counter;
    
    void buttonHighlightUp();
    void buttonHighlightDown();
    void buttonHighlightLeft();
    void buttonHighlightRight();
    
    void coinHighlightUp();
    void coinHighlightDown();
    void coinHighlightLeft();
    void coinHighlightRight();
    
    void transitionToButtonHighlight();
    void transitionToCoinHighlight();
    
    // Game operations
    const WeighResult compareWeight() const;
    const GuessResult guessFakeCoins() const;
    
    void computerSetSelection();
    
    // Display for game play
    void displayLayoutGamePlayComputer(ViewX11 &view) const;
    void displayButtonHighlight(ViewX11 &view) const;
    void displayCoinSelection(ViewX11 &view) const;
    void displayWeighResult(ViewX11 &view) const;
    void displayWeighCounter(ViewX11 &view) const;
    void displayCoinHighlight(ViewX11 &view) const;
};



};

#endif
