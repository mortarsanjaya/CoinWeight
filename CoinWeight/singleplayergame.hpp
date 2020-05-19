//
//  singleplayergame.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-19.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef singleplayergame_hpp
#define singleplayergame_hpp

#include "modelstate.hpp"
#include "tablenavigator.hpp"
#include "coinset.hpp"
#include "coinselection.hpp"
#include "history.hpp"
#include "gamelevel.hpp"

class SinglePlayerGame : public ModelState {
public:
    SinglePlayerGame(const size_t nCoinsTotal, const GameLevel level,
        const size_t nRowsDisplay, const size_t nCoinsPerRow);

    const size_t coinDisplayTopRowIndex() const;
    const size_t coinHighlightIndex() const;
    const size_t coinHighlightRow() const;
    const size_t coinHighlightColumn() const;
    const bool onButtonHighlight() const;
    
    void highlightUp() final;
    void highlightDown() final;
    void highlightLeft() final;
    void highlightRight() final;
    void onCharInput(const char inputChar) final;
    void onReturnButton(Controller &controller) final;
    void triggerDisplay(View &view) final;
    
private:
    TableNavigator coinNavigator;
    bool isOnButtonHighlight;
    
    CoinSet coinSet;
    CoinSelection selection;
    History history;
    WeighResult lastResult; // Also used to display invalid guess
    
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
};

#endif
