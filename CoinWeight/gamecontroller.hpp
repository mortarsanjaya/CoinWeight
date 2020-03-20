//
//  gamecontroller.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-20.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamecontroller_hpp
#define gamecontroller_hpp

#include "input.hpp"

class GameController {
    virtual void receiveInput() = 0;
    virtual const Input lastInput() const = 0;
public:
    GameController() = default;
    const Input interpretInput();
};

#endif
