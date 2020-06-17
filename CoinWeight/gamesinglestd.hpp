//
//  gamesinglestd.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamesinglestd_hpp
#define gamesinglestd_hpp

#include "gamecore.hpp"

#include "weighcounter.hpp"
#include "history.hpp"

namespace CoinWeight {
  
  

class GameSingleStd : public GameCore {
public:
    GameSingleStd(const size_t numOfCoins, const GameLevel level);
    
    const WeighCounter &counter() const;

private:
    WeighCounter theCounter;
    History history;

    const bool ableToCompareWeight() const override;
    void afterWeigh() override;
};
  
  
  
}


#endif
