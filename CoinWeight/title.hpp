//
//  title.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef title_hpp
#define title_hpp

#include "modelstate.hpp"

namespace CoinWeight {



class Title final : public ModelState {
public:
    enum class Highlight {
        Play,
        Instruction,
        Credit
    };
    
    Title();

    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(View &view) override;
    
private:
    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::Play;
};



};

#endif
