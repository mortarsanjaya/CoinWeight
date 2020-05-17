//
//  gameplaycomputerscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplaycomputerscreen_hpp
#define gameplaycomputerscreen_hpp

#include "gamescreen.hpp"
#include "tablenavigator.hpp"

class GamePlayComputerScreen final : public GameScreen {
public:
    enum class ButtonHighlight {
        NextMove
    };
    
    GamePlayComputerScreen(const size_t nCoinsTotal,
                           const size_t nRowsDisplay,
                           const size_t nCoinsPerRow);
                           
    const ButtonHighlight currButtonHighlight() const;
    const size_t coinDisplayTopRowIndex() const;
    const size_t coinHighlightIndex() const;
    const size_t coinHighlightRow() const;
    const size_t coinHighlightColumn() const;
    const bool onButtonHighlight() const;
    
    void highlightUp(GameView &view) override;
    void highlightDown(GameView &view) override;
    void highlightLeft(GameView &view) override;
    void highlightRight(GameView &view) override;
    void onCharInput(GameView &view, const char inputChar) override;
    void onReturnButton(GameView &view) override;
    void triggerDisplay(GameView &view, GameUI &interface) override;
    
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
