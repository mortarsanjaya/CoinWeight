//
//  input.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-19.
//  Copyright © 2020 -. All rights reserved.
//

#include "input.hpp"

//***************************************************** Constructor
Input::Input(char inp) : type{Type::Char}, charInp{inp} {}
Input::Input(Arrow inp) : type{Type::Arrow}, arrowInp{inp} {}
Input::Input() : type{Type::Unknown} {}


//***************************************************** Public methods
const Input::Type Input::inputType() const { return type; }
const char Input::whatChar() const { return charInp; }
const Input::Arrow Input::whatArrow() const { return arrowInp; }
