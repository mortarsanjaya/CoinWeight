//
//  sdlexception.hpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef sdlexception_hpp
#define sdlexception_hpp

#include "exception.hpp"

class SDLException : public Exception {
    const std::string headerMessage() const override;
    
public:
    SDLException(std::string message);
};

#endif /* sdlexception_hpp */
