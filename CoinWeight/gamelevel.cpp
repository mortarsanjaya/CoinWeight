//
//  gamelevel.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#include "gamelevel.hpp"

const std::string toString(const GameLevel gameLevel){
    switch (gameLevel) {
        case GameLevel::Easy:
            return "Easy";
        case GameLevel::Medium:
            return "Medium";
        case GameLevel::Hard:
            return "Hard";
    }
}
