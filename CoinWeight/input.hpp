//
//  input.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-19.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

/*
    Warning:
        Don't call whatArrow() if the input type is Char
        Don't call whatChar() if the input type is Arrow
*/
class Input {
public:
    enum class Type { Unknown , Char, Arrow };
    enum class Arrow { Up, Down, Left, Right };
    
private:
    Type type;
    union {
        char charInp;
        Arrow arrowInp;
    };
    
public:
    Input(char inp);
    Input(Arrow inp);
    Input();
    const Type inputType() const;
    const char whatChar() const;
    const Arrow whatArrow() const;
};

#endif
