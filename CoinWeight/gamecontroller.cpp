//
//  gamecontroller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-20.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamecontroller.hpp"

const Input GameController::interpretInput() {
    receiveInput();
    return lastInput();
}
