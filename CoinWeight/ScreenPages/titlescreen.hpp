//
//  titlescreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef titlescreen_hpp
#define titlescreen_hpp

class TitleScreen {
public:
    enum class Highlight {
        Play,
        Instruction,
        Credit
    };
    
    TitleScreen();
    
    const Highlight currHighlight() const;
    
    // Manual highlight switch
    void highlightSwitch(const Highlight highlight);
    
    // Reset highlight
    void resetHighlight();
    
    // Arrow button highlight switch
    void highlightUp();
    void highlightDown();
    void highlightLeft();
    void highlightRight();
    
private:
    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::Play;
};

#endif
