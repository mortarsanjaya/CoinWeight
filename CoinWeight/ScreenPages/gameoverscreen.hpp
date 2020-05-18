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
    
    void highlightUp(Controller &view) override;
    void highlightDown(Controller &view) override;
    void highlightLeft(Controller &view) override;
    void highlightRight(Controller &view) override;
    void onCharInput(Controller &view, const char inputChar) override;
    void onReturnButton(Controller &view) override;
    void triggerDisplay(Controller &view, View &interface) override;
    
private:
    bool playerWin;
};

#endif
