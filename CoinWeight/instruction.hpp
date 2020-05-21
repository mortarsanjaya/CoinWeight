//
//  instruction.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef instruction_hpp
#define instruction_hpp

#include "modelstate.hpp"

namespace CoinWeight {



class Instruction final : public ModelState {
public:
    Instruction();
    
    void highlightUp() override;
    void highlightDown() override;
    void highlightLeft() override;
    void highlightRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(View &view) override;
};



};

#endif
