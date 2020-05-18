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
    
    void highlightUp(Controller &controller) override;
    void highlightDown(Controller &controller) override;
    void highlightLeft(Controller &controller) override;
    void highlightRight(Controller &controller) override;
    void onCharInput(Controller &controller, const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(Controller &controller, View &interface) override;
    
private:
    bool playerWin;
};

#endif
