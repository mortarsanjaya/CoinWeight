//
//  human.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-02-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "human.hpp"
#include <iostream>

//***************************************************** Constructor(s) and Destructor
Human::Human(size_t numOfCoins, size_t numOfFakeCoins) :
	Player(numOfCoins, numOfFakeCoins)
{}

Human::~Human() {}



//***************************************************** Hook methods
bool Human::determineStrategy() {
	while (true) {
		std::cout << "Choose to compare weight(w) or make a guess(g): ";
		char c;
		std::cin >> c;
		if (c == 'w') { return true; }
		if (c == 'g') { return false; }
		std::cout << "You didn't choose between weighing or making guess." << std::endl;
	}
}

const Weighing Human::pickToWeigh() const {
	auto fillGroup = [](std::vector<size_t> &oneGroup, int i) {
		oneGroup.clear();
		int setSize;
		std::cout << "Set " << i << " size: ";
		std::cin >> setSize;
		std::cout << "Set " << i << " coin(s) (by index): ";
		for (int j = 0; j < setSize; ++j) {
			size_t index;
			std::cin >> index;
			oneGroup.push_back(index);
		}
		std::cout << "Set " << i << " formed." << std::endl;
	};
	
	Weighing weighing{};
	std::cout << "Comparison between the two following sets: " << std::endl;
	fillGroup(weighing.leftGroup, 1);
	fillGroup(weighing.rightGroup, 2);
	return weighing;
}

void Human::afterWeigh(const int weighResult) {
	std::cout << "Comparison result: ";
	switch (weighResult) {
		case 1:
			std::cout << "The first set is heavier than the second set." << std::endl;
			break;
		case -1:
			std::cout << "The second set is heavier than the first set." << std::endl;
			break;
		case 0:
			std::cout << "The two sets have the same weight." << std::endl;
			break;
	}
	std::cout << "Number of weighings done: " << numOfWeighings() << std::endl;
}

const std::vector<size_t> Human::pickGuesses() const {
	std::vector<size_t> guess;
	std::cout << "Guess the " << numOfFakeCoins() << " fake coin(s): ";
	for (int i = 0; i < numOfFakeCoins(); ++i) {
		size_t index;
		std::cin >> index;
		guess.push_back(index);
	}
	return guess;
}

void Human::afterGuess(const int guessResult) const {
	switch (guessResult) {
		case 0:
			std::cout << "You guessed correctly! You win!" << std::endl;
			std::cout << "Total number of weighings done: " << numOfWeighings() << std::endl;
			break;
		case 1:
			std::cout << "You guessed incorrectly! Better luck next time!" << std::endl;
			break;
		case 2:
			std::cout << "Incorrect number of coins! \u306a\u306b!!!" << std::endl;
			break;
		default:
			exit(101);
	}
}
