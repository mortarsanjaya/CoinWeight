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
#include "x11graphics.hpp"

using namespace std;

int main() {

	cout << "You are playing a coin weight game.\n";
	cout << "Number of coins: ";
	int numOfCoins;
	cin >> numOfCoins;
	cout << "\n";
	
	cout << "Number of fake coins: 2\n";
	
	cout << "Difficulty: ";
	Game::Level level;
	cin >> level;
	cout << "\n";
	
	cout << "Please enter the player's type (Human or Computer): ";
	std::string playerType;
	cin >> playerType;
	cout << "\n";
	
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
	X11Graphics x11graphics{};

	cout << "Game starts!\n";
	
	cout << "There are up to " << game.maxNumOfWeighings()
		<< " weighings available to determine the fake coins.\n";
		
	bool isWeigh = true;
	while (isWeigh) {
		isWeigh = game.move();
	}
	return 0;
}
