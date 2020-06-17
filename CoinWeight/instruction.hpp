//
//  instruction.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef instruction_hpp
#define instruction_hpp

#include "gamescreen.hpp"

namespace CoinWeight {
namespace X11 {



class InstructionScreen final : public GameScreenBase {
public:
    InstructionScreen();
    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(Renderer &view) const override;
};



}
}

#endif
