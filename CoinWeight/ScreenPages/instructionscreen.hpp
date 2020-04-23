//
//  instructionscreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef instructionscreen_hpp
#define instructionscreen_hpp

class InstructionScreen {
public:
    enum class Highlight {
        Return
    };
    
    InstructionScreen();
    
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
    
    static constexpr Highlight defaultHighlight = Highlight::Return;
};

#endif
