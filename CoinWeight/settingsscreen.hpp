//
//  settingsscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-06-17.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef settingsscreen_hpp
#define settingsscreen_hpp

#include "gamescreen.hpp"
#include "gamesettings.hpp"

namespace CoinWeight {
namespace X11 {



class SettingsScreen final : public GameScreenBase {
public:
    SettingsScreen();

    void onArrowUp() final;
    void onArrowDown() final;
    void onArrowLeft() final;
    void onArrowRight() final;
    void onCharInput(const char inputChar) final;
    void onReturnButton(Model &model) final;
    void triggerDisplay(Renderer &view) const final;

private:
    enum class Highlight {
        NumOfCoins,
        Level,
        Mode,
        Start,
        GoBack
    };

    Highlight highlight;

    static GameSettings settings;

    static constexpr Highlight defaultHighlight = Highlight::NumOfCoins;
    static constexpr size_t numOfCoinsLowerBound = 3;
    static constexpr size_t numOfCoinsUpperBound = 200;
    static constexpr size_t defaultNumOfCoins = 38;
    static constexpr GameLevel defaultLevel = GameLevel::Easy;
    static constexpr GameMode defaultMode = GameMode::Standard;
    
    void increaseNumOfCoins();
    void decreaseNumOfCoins();
    void increaseLevel();
    void decreaseLevel();
    void nextMode();
    void prevMode();
};



}
}

#endif
