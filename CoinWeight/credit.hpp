//
//  credit.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef credit_hpp
#define credit_hpp

#include "gamescreen.hpp"

namespace CoinWeight {



class Credit final : public GameScreenBase {
public:
    Credit();
    
    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(ViewX11 &view) override;
    
private:
    void displayLayout(ViewX11 &view);
};



};

#endif
