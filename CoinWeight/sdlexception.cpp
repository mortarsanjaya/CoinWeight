//
//  sdlexception.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include "sdlexception.hpp"

const std::string SDLException::headerMessage() const {
    return "SDL Error: ";
}

SDLException::SDLException(std::string message): Exception(message) {}
