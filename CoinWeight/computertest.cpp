//
//  computertest.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-11.
//  Copyright © 2020 -. All rights reserved.
//

#include "computertest.hpp"

#include <iostream>
#include <iomanip>
#include <memory>
#include <chrono>
#include "coinset.hpp"
#include "computer.hpp"
#include "computerfactory.hpp"
#include "weighcounter.hpp"

void CoinWeight::computerTest(const size_t nCoinsCap, const GameLevel level) {

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    std::cout << "Level: ";
    
    switch (level) {
        case GameLevel::Easy:
            std::cout << "Easy." << std::endl;
            break;
        case GameLevel::Medium:
            std::cout << "Medium." << std::endl;
            break;
        case GameLevel::Hard:
            std::cout << "Hard." << std::endl;
            break;
    }

    for (size_t numOfCoins = 3; numOfCoins <= nCoinsCap; ++numOfCoins) {
        CoinSet coinSet(numOfCoins);
        size_t worstCaseWeigh = 0;
        for (size_t i = 0; i < numOfCoins; ++i) {
            for (size_t j = i + 1; j < numOfCoins; ++j) {
                coinSet.fakeCoinI1 = i;
                coinSet.fakeCoinI2 = j;
                const auto &computer = ComputerFactory::create(numOfCoins, level);
                size_t numOfWeigh = 0;
                CoinSelection selection(numOfCoins);
                while (true) {
                    computer->setSelection(selection);
                    
                    if (selection.sizeOfGuessGroup() != 0) {
                        const GuessResult guessResult = coinSet.guessFakeCoins(selection);
                        if (guessResult == GuessResult::Correct) break;
                        else {
                            std::cout << "Error." << std::endl;
                            std::cout << "Game Level: ";
                            switch (level) {
                                case GameLevel::Easy:
                                    std::cout << "Easy" << std::endl;
                                    break;
                                case GameLevel::Medium:
                                    std::cout << "Medium" << std::endl;
                                    break;
                                case GameLevel::Hard:
                                    std::cout << "Hard" << std::endl;
                                    break;
                            }
                            std::cout << "Number of coins: " << numOfCoins << std::endl;
                            std::cout << "Fake coin indices: " << i << " " << j << std::endl;
                            std::terminate();
                        }
                    } else {
                        const WeighResult weighResult = coinSet.compareWeight(selection);
                        computer->changeState(weighResult);
                        ++numOfWeigh;
                        selection.reset();
                    }
                }
                
                if (worstCaseWeigh < numOfWeigh) {
                    worstCaseWeigh = numOfWeigh;
                }
            }
        }
        
        // std::cout << "Computer checking with " << numOfCoins << " coins finished." << std::endl;
        // std::cout << "Worst case comparisons: " << worstCaseWeigh << std::endl;
        std::cout << numOfCoins << " " << worstCaseWeigh << " " <<
            WeighCounter::nWeighsCap(numOfCoins, level) << std::endl;
    }
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration<double>(end - start);
    
    std::cout << std::setprecision(10) << "Testing took " <<
        duration.count() << " seconds." << std::endl;
}
