//
//  gameoverscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameoverscreen_hpp
#define gameoverscreen_hpp

class GameOverScreen {
public:
    enum class Highlight {
        BackToTitle
    };
    
    GameOverScreen();
    
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
    
    static constexpr Highlight defaultHighlight = Highlight::BackToTitle;
};

#endif
