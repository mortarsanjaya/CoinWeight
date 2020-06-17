//
//  gameplaycomputer.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameplaycomputer_hpp
#define gameplaycomputer_hpp

#include "singleplayergame.hpp"

#include "gamescreen.hpp"
#include "tablenavigator.hpp"
#include "coinset.hpp"
#include "computer.hpp"
#include "gamelevel.hpp"

#include "coinselection.hpp"
#include "history.hpp"
#include "weighcounter.hpp"

namespace CoinWeight {
namespace X11 {



class GamePlayComputer final : public SinglePlayerGame {
public:
    GamePlayComputer(const size_t nCoinsTotal, const GameLevel level);
    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(Renderer &view) const override;
    
private:
    enum class ButtonHighlight {
        NextMove
    };
    
    ButtonHighlight buttonHighlight;
    TableNavigator coinNavigator;
    bool isOnButtonHighlight;
    
    CoinSet coinSet;
    CoinSelection selection;
    History history;
    
    std::unique_ptr<Computer> computer;
    
    WeighResult lastResult;
    
    WeighCounter counter;
    
    
    
    // Coin configurations
    static constexpr int coinDiameter = 30;
    static constexpr int coinDist = 50;
    static constexpr int coin0XPos = 200;
    static constexpr int coin0YPos = 200;
    static constexpr int coinOffset = (coinDist - coinDiameter) / 2;
    static constexpr size_t coinsPerRow = 10;
    static constexpr size_t rowsDisplay = 8;
    
    
    
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
    
    void computerSetSelection();
    
    // Display for game play
    void displayLayoutGamePlayComputer(Renderer &view) const;
    void displayButtonHighlight(Renderer &view) const;
    void displayCoinSelection(Renderer &view) const;
    void displayWeighResult(Renderer &view) const;
    void displayWeighCounter(Renderer &view) const;
    void displayCoinHighlight(Renderer &view) const;
    
    void drawCoin(Renderer &view, const CoinGroup group, const size_t coinIndex,
                  const size_t row, const size_t column) const;
    static const int coinColor(const CoinGroup group);
    
    void drawWeighResultText(Renderer &view) const;
    void drawWeighingScale(Renderer &view) const;
};



}
}

#endif
