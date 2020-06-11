//
//  main.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinset.hpp"
#include "computertest.hpp"
#include "controller.hpp"

#include <iostream>
#include <chrono>
#include <thread>

using namespace CoinWeight;
using namespace std::chrono;

int main() {
    computerTest(75, GameLevel::Easy);
    computerTest(100, GameLevel::Medium);
    computerTest(100, GameLevel::Hard);

/*
    Controller controller;
    while (true) {
        controller.updateDisplay();
        
        auto before_input = steady_clock::now();
        controller.processInput();
        while (true) {
            auto after_input = steady_clock::now();
            auto duration = duration_cast<milliseconds>(after_input - before_input);
            if (duration.count() >= 10) break;
        }
    }
*/
}
