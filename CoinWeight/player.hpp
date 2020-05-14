//
//  player.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-27.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <memory>
#include "coinstates.hpp"
#include "history.hpp"
#include "gamelevel.hpp"
#include "weighresult.hpp"

class Computer;

class Player {
public:
    // UUUH Why two constructors
    Player(const size_t numOfCoins);
    Player(const size_t numOfCoins, const GameLevel gameLevel);
    
    const CoinSelection &currStates() const;
    const History &currHistory() const;
    const bool isHuman() const;
    const bool readyToGuess() const; // Should be removed
    
    // Coin states manipulation
    void deselectCoin(const size_t coinIndex);
    void selectCoinToLeftGroup(const size_t coinIndex);
    void selectCoinToRightGroup(const size_t coinIndex);
    void selectCoinToGuess(const size_t coinIndex);
    
    void receiveWeighResult(const WeighResult weighResult);
    void historyIncrementIndex(); // Should be removed
    void historyDecrementIndex(); // Should be removed

private:
    CoinSelection coinStates;
    History history;
    std::unique_ptr<Computer> computer;
    
    void addWeighResult(const WeighResult weighResult);
    void resetStates();
    void computerSetup();
};

#endif
