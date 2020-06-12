//
//  gameplayhuman.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplayhuman_hpp
#define gameplayhuman_hpp

#include "singleplayergame.hpp"

#include "gamescreen.hpp"
#include "tablenavigator.hpp"
#include "coinset.hpp"
#include "gamelevel.hpp"

#include "coinselection.hpp"
#include "history.hpp"
#include "weighcounter.hpp"

namespace CoinWeight {



class GamePlayHuman final : public SinglePlayerGame {
public:
    
    GamePlayHuman(const size_t nCoinsTotal, const GameLevel level);

    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(ViewX11 &view) const override;
    
private:
    enum class ButtonHighlight {
        Weigh,
        Guess
    };
    
    ButtonHighlight buttonHighlight;
    TableNavigator coinNavigator;
    bool isOnButtonHighlight;
    
    CoinSet coinSet;
    CoinSelection selection;
    History history;
    
    WeighResult lastResult; // Also used to display invalid guess
    
    WeighCounter counter;
    
    
    
    // Coin configurations
    static constexpr int coinDiameter = 30;
    static constexpr int coinDist = 50;
    static constexpr int coin0XPos = 200;
    static constexpr int coin0YPos = 200;
    static constexpr int coinOffset = (coinDist - coinDiameter) / 2;
    static constexpr size_t coinsPerRow = 10;
    static constexpr size_t rowsDisplay = 8;
    
    
    
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
    
    // Display for game play
    void displayLayoutGamePlayHuman(ViewX11 &view) const;
    void displayButtonHighlight(ViewX11 &view) const;
    void displayCoinSelection(ViewX11 &view) const;
    void displayWeighResult(ViewX11 &view) const;
    void displayWeighCounter(ViewX11 &view) const;
    void displayCoinHighlight(ViewX11 &view) const;
    
    void drawCoin(ViewX11 &view, const CoinGroup group, const size_t coinIndex,
                  const size_t row, const size_t column) const;
    static const int coinColor(const CoinGroup group);
    
    void drawWeighResultText(ViewX11 &view) const;
    void drawWeighingScale(ViewX11 &view) const;
};



};

#endif
