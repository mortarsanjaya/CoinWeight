//
//  input.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-19.
//  Copyright © 2020 -. All rights reserved.
//

#include "input.hpp"
#include "exception.hpp"

//************************** Constructor
Input::Input(Source source, char inp) :
    source{source}, type{Type::Char}, charInp{inp} {}
Input::Input(Source source, Arrow inp) :
    source{source}, type{Type::Arrow}, arrowInp{inp} {}
Input::Input(Source source) :
    source{source}, type{Type::Unknown} {}



//************************** Public methods
const Input::Source Input::sourceScreen() const {
    return source;
}

const Input::Type Input::inputType() const {
    return type;
}

const char Input::whatChar() const {
    if (inputType() != Type::Char) {
        throw Exception<Input>("Input not a character.");
    }
    return charInp;
}

const Input::Arrow Input::whatArrow() const {
    if (inputType() != Type::Arrow) {
        throw Exception<Input>("Input not an arrow.");
    }
    return arrowInp;
}



//************************** Input Failure
template<> const std::string Exception<Input>::headerMessage() const {
    return "Input Failure: ";
}
