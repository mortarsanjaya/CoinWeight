//
//  model.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <memory>
#include "gamelevel.hpp"
#include "gamemode.hpp"
#include "gamescreen.hpp"

namespace CoinWeight {



class View;

class Model {
public:
    Model(const size_t coinDisplayRows, const size_t coinDisplayColumns);

    // Input handling
    void onArrowUp();
    void onArrowDown();
    void onArrowLeft();
    void onArrowRight();
    void onCharInput(const char inputChar);
    void onReturnButton();

    // Screen switching
    void switchToTitle();
    void switchToInstruction();
    void switchToCredit();
    void switchToGameSettings();
    void switchToGamePlay(const size_t numOfCoins, const GameLevel level, const GameMode mode);
    void switchToGameOver(const bool isWin);
    
    // View updating
    void updateView(View &view);
    
private:
    const size_t coinDisplayRows;
    const size_t coinDisplayColumns;

    std::unique_ptr<GameScreenBase> screen;

};



}

#endif
