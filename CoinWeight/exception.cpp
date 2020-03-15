//
//  exception.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-15.
//  Copyright © 2020 -. All rights reserved.
//

#include "exception.hpp"

Exception::Exception(std::string coreMessage) : coreMessage{std::move(coreMessage)} {}
const std::string Exception::fullMessage() const {
    return (headerMessage() + coreMessage);
}
