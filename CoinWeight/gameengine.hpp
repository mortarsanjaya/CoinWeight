//
//  gameengine.hpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 17/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameengine_hpp
#define gameengine_hpp

#include "game.hpp"
#include "gameview.hpp"

class GameEngine {
    enum class GamePhase { Start, Instruction, Credits, OptionSelection, Gameplay, EndScreen };
    enum class CoinState { Scale1, Scale2, NotSelected };
    
    std::unique_ptr<Game> game;
    std::unique_ptr<GameViewSDL> gameView;
    GamePhase gamePhase;
    std::vector<CoinState> coinStates;
    std::string currentInputText;
    /*
     options:
        Start           -> Play, Instructions, Credits (vertical layout)
        Instruction     -> Return
        Credits         -> Return
        OptionSelection -> Number of Coins Input, Level Input, Continue (vertical layout)
        Gameplay        -> Weigh, Guess, each coin (weigh, guess vertical layout, below are coins in a rectangle)
        EndScreen       -> Play Again, Quit (vertical layout)
     
     options is resized every game phase change
     
     selectionX, selectionY indicates indexes of options that store the current selected option
        changes according to keyboard presses
        edge case: only can select a coin with a NotSelected CoinState
    */
    int selectionX, selectionY;
    std::vector<std::vector<std::string>> options;
    
public:
    GameEngine(std::unique_ptr<GameViewSDL> gameView);
    void quit();
    void onKeyPress(SDL_Keycode keyCode);
};

#endif /* gameengine_hpp */
