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
    
    void highlightUp(Controller &view) override;
    void highlightDown(Controller &view) override;
    void highlightLeft(Controller &view) override;
    void highlightRight(Controller &view) override;
    void onCharInput(Controller &view, const char inputChar) override;
    void onReturnButton(Controller &view) override;
    void triggerDisplay(Controller &view, View &interface) override;
};

#endif
