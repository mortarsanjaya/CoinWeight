//
//  gamecore.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamecore_hpp
#define gamecore_hpp

#include "coinset.hpp"
#include "coinselection.hpp"
#include "weighresult.hpp"
#include "gamesettings.hpp"
#include <memory>

namespace CoinWeight {
  


class GameCore {
public:
    virtual ~GameCore() = default;
    
    const CoinSelection &currSelection() const;
    const WeighResult lastWeighResult() const;
        
    const bool gameOver() const;
    const bool playerWin() const;
    
    void setSelectionGroup(const size_t index, const CoinGroup group);
    
    // Returns true if the moves are successful
    // Does not change the state of the core if false is returned
    const bool compareWeight();
    const bool guessFakeCoins();
    
    static std::unique_ptr<GameCore> createGame(const GameSettings &settings);

protected:
    GameCore(const size_t numOfCoins);
    
    // If possible, revert these back to private
    CoinSelection selection;
    WeighResult lastResult;
    
private:
    CoinSet coinSet;
    
    bool isGameOver;
    bool isPlayerWin;

    virtual const bool ableToCompareWeight() const = 0;
    virtual void afterWeigh() = 0;
};



}

#endif
