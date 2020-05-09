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
    enum class Source { Main, History }; // The screen source of input
    enum class Type { Unknown, Char, Arrow };
    enum class Arrow { Up, Down, Left, Right };
    
private:
    Source source;
    Type type;
    union {
        char charInp;
        Arrow arrowInp;
    };
    
public:
    Input(Source source, char inp);
    Input(Source source, Arrow inp);
    Input(Source source);
    const Source sourceScreen() const;
    const Type inputType() const;
    const char whatChar() const;
    const Arrow whatArrow() const;
};

#endif
