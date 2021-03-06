//
//  gameplayhuman.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplayhuman_hpp
#define gameplayhuman_hpp

#include "gamescreen.hpp"
#include "tablenavigator.hpp"
#include "coinset.hpp"
#include "gamelevel.hpp"

#include "coinselection.hpp"
#include "history.hpp"
#include "weighcounter.hpp"

namespace CoinWeight {



class GamePlayHuman final : public GameScreenBase {
public:
    enum class ButtonHighlight {
        Weigh,
        Guess
    };
    
    GamePlayHuman(const size_t nCoinsTotal, const GameLevel level,
        const size_t nRowsDisplay, const size_t nCoinsPerRow);

    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(View &view) override;
    
private:
    ButtonHighlight buttonHighlight;
    TableNavigator coinNavigator;
    bool isOnButtonHighlight;
    
    CoinSet coinSet;
    CoinSelection selection;
    History history;
    
    WeighResult lastResult; // Also used to display invalid guess
    
    WeighCounter counter;
    
    const size_t coinHighlightIndex() const;
    
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



};

#endif
