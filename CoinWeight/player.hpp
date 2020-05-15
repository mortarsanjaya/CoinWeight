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
#include "coinselection.hpp"
#include "history.hpp"
#include "gamelevel.hpp"
#include "weighresult.hpp"

class Player {
public:
    virtual ~Player() = default;

    const CoinSelection &currSelection() const;
    const History &currHistory() const;
    
    void setSelectionGroup(const size_t coinIndex, const CoinGroup group);
    
    void receiveWeighResult(const WeighResult weighResult);

    virtual const bool isAbleToWeigh() const = 0;
    
protected:
    Player(const size_t numOfCoins);
    const size_t numOfCoins() const;

private:
    CoinSelection selection;
    History history;
    
    void addWeighResult(const WeighResult weighResult);
    virtual void afterWeigh(const WeighResult weighResult) = 0;
    void resetStates();
};

#endif
