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
    
    void highlightUp(Controller &controller) override;
    void highlightDown(Controller &controller) override;
    void highlightLeft(Controller &controller) override;
    void highlightRight(Controller &controller) override;
    void onCharInput(Controller &controller, const char inputChar) override;
    void onReturnButton(Controller &controller) override;
    void triggerDisplay(Controller &controller, View &interface) override;
    
private:
    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::Play;
};

#endif
