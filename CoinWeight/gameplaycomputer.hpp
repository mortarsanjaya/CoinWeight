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

class GamePlayComputer final : public ModelState {
public:
    enum class ButtonHighlight {
        NextMove
    };
    
    GamePlayComputer(const size_t nCoinsTotal,
                           const size_t nRowsDisplay,
                           const size_t nCoinsPerRow);
                           
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
