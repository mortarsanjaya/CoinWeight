//
//  gamescreen.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-30.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gamescreen_hpp
#define gamescreen_hpp

class GameScreen {
public:
    enum class Page {
        Title,               // Play, Instruction, Credit
        Instruction,
        Credit,
        GameOption,         // Number of coins, Difficulty, Human/Computer mode
        GamePlayHuman,      // Coins, Weigh, Guess
        GamePlayComputer,   // Next Step Only
        GameOver            // Lose, Win
    };

private:
    Page page;
    int highlight;

    // Modifier functions (private)
    const int minHighlight();
    const int maxHighlight();
    void resetHighlight();

public:
    GameScreen(Page page = Page::Title, int highlight = 0);
    
    const Page currentScreen() const;
    const int currentHighlight() const;
    
    // Modifier functions (public)
    void incrementHighlight();
    void decrementHighlight();
    void transition(const Page nextScreen);
};

#endif
