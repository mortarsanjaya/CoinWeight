//
//  exception.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-15.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef exception_hpp
#define exception_hpp

#include <string>

template <typename T> class Exception {
    std::string coreMessage;
    
public:
    Exception(std::string coreMessage) : coreMessage{coreMessage} {}
    const std::string headerMessage() const;
    const std::string fullMessage() const {
        return headerMessage() + coreMessage;
    }
};

#endif
