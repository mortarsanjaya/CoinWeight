//
//  titlescreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef titlescreen_hpp
#define titlescreen_hpp

#include "modelstate.hpp"

class TitleScreen final : public ModelState {
public:
    enum class Highlight {
        Play,
        Instruction,
        Credit
    };
    
    TitleScreen();
    
    const Highlight currHighlight() const;
    
    void highlightUp() override;
    void highlightDown() override;
    void highlightLeft() override;
    void highlightRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(View &view) override;
    
private:
    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::Play;
};

#endif
