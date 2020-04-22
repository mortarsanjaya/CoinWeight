//
//  gameplayhumanscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplayhumanscreen_hpp
#define gameplayhumanscreen_hpp

#include <utility>

class GamePlayHumanScreen {
public:
    enum class ScreenHighlight {
        WeighButton,
        GuessButton,
        Coins
    };
    
    GamePlayHumanScreen(size_t numOfCoins, size_t coinsPerRow);
    GamePlayHumanScreen &operator=(GamePlayHumanScreen &&other);
    
    const ScreenHighlight currScreenHighlight() const;
    const size_t currCoinHighlight() const;
    
    // Manual highlight switch
    void screenHighlightSwitch(const ScreenHighlight screenHighlight);
    void coinHighlightSwitch(const size_t coinHighlight);
    
    // Reset highlight
    void resetHighlight();
    
    // Arrow button highlight switch
    void highlightUp();
    void highlightDown();
    void highlightLeft();
    void highlightRight();
    
private:
    ScreenHighlight screenHighlight;
    const size_t numOfCoins;
    const size_t coinsPerRow;
    size_t coinHighlight;
    
    static constexpr ScreenHighlight defaultScreenHighlight = ScreenHighlight::Coins;
    static constexpr size_t defaultCoinHighlight = 0;
    
    // Arrow button highlight switch at Coins
    void highlightUpAtCoins();
    void highlightDownAtCoins();
    void highlightLeftAtCoins();
    void highlightRightAtCoins();
};

#endif
