//
//  gameoverscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameoverscreen_hpp
#define gameoverscreen_hpp

#include "modelstate.hpp"

class GameOverScreen final : public ModelState {
public:
    
    GameOverScreen(const bool doesPlayerWin);
    
    const bool doesPlayerWin() const;
    
    void highlightUp() override;
    void highlightDown() override;
    void highlightLeft() override;
    void highlightRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(View &view) override;
    
private:
    bool playerWin;
};

#endif
