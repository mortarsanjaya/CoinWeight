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
#include "viewx11.hpp"

#include <chrono>
#include <thread>

using namespace std;

int main() {
    computerTest(75, GameLevel::Easy);
    computerTest(100, GameLevel::Medium);

    auto controller = std::make_unique<Controller>(std::make_unique<ViewX11>());
    while (true) {
        controller->updateDisplay();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        controller->processInput();
    }
}
