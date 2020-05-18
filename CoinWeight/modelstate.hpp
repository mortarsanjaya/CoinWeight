//
//  modelstate.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef modelstate_hpp
#define modelstate_hpp

#include <memory>

class Controller;
class View;

class ModelState {
public:
    virtual ~ModelState() = default;

    // Action on arrow button press
    // Generally, does not change the controller itself
    virtual void highlightUp(Controller &controller) = 0;
    virtual void highlightDown(Controller &controller) = 0;
    virtual void highlightLeft(Controller &controller) = 0;
    virtual void highlightRight(Controller &controller) = 0;
    
    // Action on character input press
    virtual void onCharInput(Controller &controller, const char inputChar) = 0;
    
    // Action on return button press (most certainly screen switching)
    virtual void onReturnButton(Controller &controller) = 0;
    
    // Triggers View and UI for displaying the current screen
    virtual void triggerDisplay(Controller &controller, View &view) = 0;
    
};

#endif
