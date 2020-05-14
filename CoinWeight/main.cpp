//
//  main.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include "coinset.hpp"
#include "computer.hpp"
#include "computerhard.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include "gamemodel.hpp"
#include "gameui_x11.hpp"
#include "gamecontroller.hpp"
#include "input.hpp"

template <size_t n> static const size_t log_ceil(size_t k) {
	if (k == 0) exit(100);
	size_t res = 0;
	while (k > 1) {
		k = (k - 1) / n + 1;
		++res;
	}
	return res;
}

void test() {
    for (size_t numOfCoins = 3; numOfCoins <= 50; ++numOfCoins) {
        auto coinSet = std::make_unique<CoinSet>(numOfCoins);
        size_t worstCaseWeigh = 0;
        for (size_t i = 0; i < numOfCoins; ++i) {
            for (size_t j = i + 1; j < numOfCoins; ++j) {
                coinSet->fakeCoinI1 = i;
                coinSet->fakeCoinI2 = j;
                auto computer = std::make_unique<ComputerHard>(numOfCoins);
                CoinSelection coinStates(numOfCoins);
                size_t numOfWeigh = 0;
                while (true) {
                    if (computer->readyToGuess()) {
                        computer->pickToGuess(coinStates);
                        const GuessResult guessResult = coinSet->guessFakeCoins(coinStates);
                        if (guessResult == GuessResult::Correct) break;
                        else exit(1);
                    } else {
                        computer->beforeWeigh();
                        computer->pickToWeigh(coinStates);
                        const WeighResult weighResult = coinSet->compareWeight(coinStates);
                        computer->afterWeigh(weighResult);
                        coinStates.reset();
                        ++numOfWeigh;
                    }
                }
                
                if (worstCaseWeigh < numOfWeigh) {
                    worstCaseWeigh = numOfWeigh;
                }
            }
        }
        
        std::cout << numOfCoins << " " << worstCaseWeigh << " " <<
            log_ceil<3>(numOfCoins * (numOfCoins - 1) / 2) + 1 << std::endl;
    }
}

void play() {
    std::shared_ptr<GameModel> model;
    std::unique_ptr<GameUI> view;
    GameController controller;
    
    model = std::make_shared<GameModel>();
    if (model == nullptr) {
        std::cout << "Oops. Cannot initialize model." << std::endl;
        return;
    } else {
        controller.registerModel(model);
    }
    
    view = std::make_unique<GameUI_X11>();
    if (view == nullptr) {
        std::cout << "Oops. Cannot open display." << std::endl;
        return;
    }
    
    sleep(1);
    controller.updateView(view.get());
    while (true) {
        view->receiveInput();
        controller.onReceivingInput(view->lastInput());
        controller.updateView(view.get());
    }
}

using namespace std;

int main() {
    test();
    play();
}
