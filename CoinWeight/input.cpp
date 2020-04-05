//
//  input.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-19.
//  Copyright © 2020 -. All rights reserved.
//

#include "input.hpp"

//***************************************************** Constructor
Input::Input(Source source, char inp) :
    source{source}, type{Type::Char}, charInp{inp} {}
Input::Input(Source source, Arrow inp) :
    source{source}, type{Type::Arrow}, arrowInp{inp} {}
Input::Input(Source source) :
    source{source}, type{Type::Unknown} {}



//***************************************************** Public methods
const Input::Source Input::sourceScreen() const {
    return source;
}

const Input::Type Input::inputType() const {
    return type;
}

const char Input::whatChar() const {
    if (inputType() != Type::Char) {
        throw InputFailure("Input not a character.");
    }
    return charInp;
}

const Input::Arrow Input::whatArrow() const {
    if (inputType() != Type::Arrow) {
        throw InputFailure("Input not an arrow.");
    }
    return arrowInp;
}



//***************************************************** Input Failure
InputFailure::InputFailure(std::string coreMessage) :
    Exception(coreMessage) {}
    
const std::string InputFailure::headerMessage() const {
    return "Input Failure: ";
}
