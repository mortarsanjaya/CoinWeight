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

class GameController;
class GameUI;

class GameScreen {
public:
    virtual ~GameScreen() = default;

    // Action on arrow button press
    // Generally, does not change the controller itself other than the screen
    virtual void highlightUp(GameController &controller) = 0;
    virtual void highlightDown(GameController &controller) = 0;
    virtual void highlightLeft(GameController &controller) = 0;
    virtual void highlightRight(GameController &controller) = 0;
    
    // Action on character input press
    virtual void onCharInput(GameController &controller, const char inputChar) = 0;
    
    // Action on return button press (most certainly screen switching)
    virtual void onReturnButton(GameController &controller) = 0;
    
    // Triggers View and UI for displaying the current screen
    virtual void triggerDisplay(GameController &controller, GameUI &interface) = 0;
    
};

#endif
