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
    
    void highlightUp(Controller &view) override;
    void highlightDown(Controller &view) override;
    void highlightLeft(Controller &view) override;
    void highlightRight(Controller &view) override;
    void onCharInput(Controller &view, const char inputChar) override;
    void onReturnButton(Controller &view) override;
    void triggerDisplay(Controller &view, View &interface) override;
    
private:
    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::Play;
};

#endif
