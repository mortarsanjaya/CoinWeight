//
//  singleplayergame.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-19.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef singleplayergame_hpp
#define singleplayergame_hpp

#include "gamescreen.hpp"
#include "tablenavigator.hpp"
#include "coinset.hpp"
#include "coinselection.hpp"
#include "history.hpp"
#include "gamelevel.hpp"

namespace CoinWeight {



class SinglePlayerGame : public GameScreenBase {
public:
    SinglePlayerGame(const size_t nCoinsTotal, const GameLevel level,
        const size_t nRowsDisplay, const size_t nCoinsPerRow);
    
    void onArrowUp() final;
    void onArrowDown() final;
    void onArrowLeft() final;
    void onArrowRight() final;
    void onCharInput(const char inputChar) final;
    void onReturnButton(Model &model) final;
    void triggerDisplay(ViewX11 &view) final;
    
private:
    TableNavigator coinNavigator;
    bool isOnButtonHighlight;
    
    CoinSet coinSet;
    CoinSelection selection;
    History history;
    WeighResult lastResult; // Also used to display invalid guess
    
    virtual void buttonHighlightUp() = 0;
    virtual void buttonHighlightDown() = 0;
    virtual void buttonHighlightLeft() = 0;
    virtual void buttonHighlightRight() = 0;
    
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



};

#endif
