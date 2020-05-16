//
//  gamescreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamescreen_hpp
#define gamescreen_hpp

#include <memory>

class GameView;
class GameUI;

class GameScreen {
public:
    virtual ~GameScreen() = default;

    // Action on arrow button press
    // Generally, does not change the view itself other than the screen
    virtual void highlightUp(GameView &view) = 0;
    virtual void highlightDown(GameView &view) = 0;
    virtual void highlightLeft(GameView &view) = 0;
    virtual void highlightRight(GameView &view) = 0;
    
    // Action on character input press
    virtual void onCharInput(GameView &view, const char inputChar) = 0;
    
    // Action on return button press (most certainly screen switching)
    virtual void onReturnButton(GameView &view) = 0;
    
    // Accepts a UI for displaying the current screen
    virtual void triggerDisplay(GameUI &interface) = 0;
    
};

#endif
