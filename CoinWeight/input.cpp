//
//  input.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-19.
//  Copyright © 2020 -. All rights reserved.
//

#include "input.hpp"

//***************************************************** Constructor
Input::Input(char inp) : charInp{inp}, type{Type::Char} {}
Input::Input(Arrow inp) : arrowInp{inp}, type{Type::Arrow} {}



//***************************************************** Public methods
const Input::Type Input::inputType() const { return type; }
const char whatChar() const { return charInp; }
const Input::Arrow whatArrow() const { return arrowInp; }
