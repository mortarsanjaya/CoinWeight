//
//  main.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-21.
//  Copyright © 2020 -. All rights reserved.
//

#include <iostream>
#include <memory>
#include <string>
#include "game.hpp"
#include "human.hpp"
#include "computerhard.hpp"
#include "gameviewx11.hpp"

using namespace std;

int main() {
    try {
        auto gameview = std::make_unique<GameViewX11>();
        sleep(1);
        gameview->drawMainScreen();
        
        cout << "You are playing a coin weight game.\n";
        sleep(2);
        gameview->drawPlayScreen1();
        
        cout << "Number of coins: ";
        std::string numOfCoins_str;
        cin >> numOfCoins_str;
        gameview->coreGraphics.drawString(405, 315, numOfCoins_str);
        /*
        while (true) {
            char c;
            cin >> c;
            if (c == '\n') break;
            numOfCoins_str += c;
            gameview->coreGraphics.drawString(405, 315, numOfCoins_str);
        }
        */
        int numOfCoins = stoi(numOfCoins_str);
        
        cout << "Difficulty: ";
        std::string level_str;
        cin >> level_str;
        gameview->coreGraphics.drawString(405, 335, level_str);
        Game::Level level;
        if (level_str == "Easy") level = Game::Level::Easy;
        else if (level_str == "Medium") level = Game::Level::Medium;
        else if (level_str == "Hard") level = Game::Level::Hard;
        else if (level_str == "Insane") level = Game::Level::Insane;
        else {
            cerr << "WHAT?" << endl;
            return 1;
        }
           
        cout << "Mode (Human or Computer): ";
        std::string playerType;
        cin >> playerType;
        gameview->coreGraphics.drawString(405, 355, playerType);
        std::unique_ptr<Player> player;
        if (playerType == "Human") {
            player = std::make_unique<Human>(numOfCoins, 2);
        } else if (playerType == "Computer") {
            player = std::make_unique<ComputerHard>(numOfCoins, 2);
        } else {
            cerr << "WHAT?" << endl;
            return 1;
        }
           
        Game game(numOfCoins, std::move(player), level);
        sleep(1);
        gameview->drawPlayScreen2(numOfCoins);
        
        cout << "Game starts!\n";
        
        long weighingCap = game.maxNumOfWeighings();
        cout << "There are up to " << weighingCap
            << " weighings available to determine the fake coins.\n";

        bool isWeigh = true;
        while (isWeigh) {
            isWeigh = game.move();
            sleep(1);
        }
        return 0;
    } catch (Exception &e) {
        cout << e.fullMessage() << endl;
        return 1;
    }
}
