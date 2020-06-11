//
//  title.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef title_hpp
#define title_hpp

#include "gamescreen.hpp"

namespace CoinWeight {



class Title final : public GameScreenBase {
public:
    Title();

    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(ViewX11 &view) const override;
    
private:
    enum class Highlight {
        Play,
        Instruction,
        Credit
    };

    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::Play;
    
    void displayLayout(ViewX11 &view) const;
    void displayHighlight(ViewX11 &view) const;
};



};

#endif
