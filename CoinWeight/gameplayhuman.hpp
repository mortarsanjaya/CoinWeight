//
//  gameplayhuman.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplayhuman_hpp
#define gameplayhuman_hpp

#include "modelstate.hpp"
#include "tablenavigator.hpp"
#include "coinset.hpp"
#include "humanstd.hpp"
#include "gamelevel.hpp"

class GamePlayHuman final : public ModelState {
public:
    enum class ButtonHighlight {
        Weigh,
        Guess
    };
    
    GamePlayHuman(const size_t nCoinsTotal, const GameLevel level,
        const size_t nRowsDisplay, const size_t nCoinsPerRow);
                        
    const ButtonHighlight currButtonHighlight() const;
    const size_t coinDisplayTopRowIndex() const;
    const size_t coinHighlightIndex() const;
    const size_t coinHighlightRow() const;
    const size_t coinHighlightColumn() const;
    const bool onButtonHighlight() const;
    
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
    HumanStd human;
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
