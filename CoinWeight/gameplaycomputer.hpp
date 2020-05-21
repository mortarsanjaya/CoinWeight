//
//  gameplaycomputer.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplaycomputer_hpp
#define gameplaycomputer_hpp

#include "modelstate.hpp"
#include "tablenavigator.hpp"
#include "coinset.hpp"
#include "computer.hpp"
#include "gamelevel.hpp"

#include "coinselection.hpp"
#include "history.hpp"
#include "weighcounter.hpp"

namespace CoinWeight {



class GamePlayComputer final : public ModelState {
public:
    enum class ButtonHighlight {
        NextMove
    };
    
    GamePlayComputer(const size_t nCoinsTotal, const GameLevel level,
        const size_t nRowsDisplay, const size_t nCoinsPerRow);
    
    void highlightUp() override;
    void highlightDown() override;
    void highlightLeft() override;
    void highlightRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(View &view) override;
    
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
};



};

#endif
