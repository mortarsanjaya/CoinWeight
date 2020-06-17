//
//  gamesinglecomp.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamesinglecomp_hpp
#define gamesinglecomp_hpp

#include "gamecore.hpp"

#include "weighcounter.hpp"
#include "history.hpp"
#include "computer.hpp"

namespace CoinWeight {
  


class Computer;

class GameSingleComp : public GameCore {
public:
    GameSingleComp(const size_t numOfCoins, const GameLevel level);
    
    const WeighCounter &counter() const;

private:
    WeighCounter theCounter;
    History history;
    std::unique_ptr<Computer> computer;

    const bool ableToCompareWeight() const override;
    void afterWeigh() override;
    
    void computerSetup();
};
  
  
  
}

#endif
