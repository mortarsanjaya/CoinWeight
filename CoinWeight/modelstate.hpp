//
//  modelstate.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef modelstate_hpp
#define modelstate_hpp

namespace CoinWeight {


class Model;
class View;

class ModelState {
public:
    virtual ~ModelState() = default;

    // Action on arrow button press
    virtual void onArrowUp() = 0;
    virtual void onArrowDown() = 0;
    virtual void onArrowLeft() = 0;
    virtual void onArrowRight() = 0;
    
    // Action on character input press
    virtual void onCharInput(const char inputChar) = 0;

    // Action on return button press (most certainly screen switching)
    // Assumes that the model is the owner of the caller model state
    virtual void onReturnButton(Model &model) = 0;
    
    // Triggers View and UI for displaying the current screen
    virtual void triggerDisplay(View &view) = 0;
};



};

#endif
