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

class GamePlayHumanScreen final : public GameScreen {
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
    
    void highlightUp(GameController &view) override;
    void highlightDown(GameController &view) override;
    void highlightLeft(GameController &view) override;
    void highlightRight(GameController &view) override;
    void onCharInput(GameController &view, const char inputChar) override;
    void onReturnButton(GameController &view) override;
    void triggerDisplay(GameController &view, GameUI &interface) override;
    
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
