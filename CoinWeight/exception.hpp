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

class Exception {
    std::string coreMessage;
    virtual const std::string headerMessage() const = 0;
    
public:
    Exception(std::string message);
    const std::string fullMessage() const;
};

#endif
