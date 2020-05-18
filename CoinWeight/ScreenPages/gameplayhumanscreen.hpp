//
//  gameplayhumanscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplayhumanscreen_hpp
#define gameplayhumanscreen_hpp

#include "gamescreen.hpp"
#include "tablenavigator.hpp"
#include "coingroup.hpp"

class GamePlayHumanScreen final : public ModelState {
public:
    enum class ButtonHighlight {
        Weigh,
        Guess
    };
    
    GamePlayHumanScreen(const size_t nCoinsTotal,
                        const size_t nRowsDisplay,
                        const size_t nCoinsPerRow);
                        
    const ButtonHighlight currButtonHighlight() const;
    const size_t coinDisplayTopRowIndex() const;
    const size_t coinHighlightIndex() const;
    const size_t coinHighlightRow() const;
    const size_t coinHighlightColumn() const;
    const bool onButtonHighlight() const;
    
    void highlightUp(Controller &view) override;
    void highlightDown(Controller &view) override;
    void highlightLeft(Controller &view) override;
    void highlightRight(Controller &view) override;
    void onCharInput(Controller &view, const char inputChar) override;
    void onReturnButton(Controller &view) override;
    void triggerDisplay(Controller &view, View &interface) override;
    
private:
    ButtonHighlight buttonHighlight;
    TableNavigator coinNavigator;
    
    bool isOnButtonHighlight;
    
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
};

#endif
