//
//  instructionscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef instructionscreen_hpp
#define instructionscreen_hpp

#include "modelstate.hpp"

class InstructionScreen final : public ModelState {
public:
    InstructionScreen();
    
    void highlightUp(Controller &controller) override;
    void highlightDown(Controller &controller) override;
    void highlightLeft(Controller &controller) override;
    void highlightRight(Controller &controller) override;
    void onCharInput(Controller &controller, const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(Controller &controller, View &interface) override;
};

#endif
