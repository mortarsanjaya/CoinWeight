//
//  credit.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef credit_hpp
#define credit_hpp

#include "modelstate.hpp"

namespace CoinWeight {



class Credit final : public ModelState {
public:
    Credit();
    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(View &view) override;
};



};

#endif
