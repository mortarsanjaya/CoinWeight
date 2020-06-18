//
//  title.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-21.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef title_hpp
#define title_hpp

#include "gamescreen.hpp"
#include <string>
#include <vector>

namespace CoinWeight {
namespace X11 {



class TitleScreen final : public GameScreenBase {
public:
    TitleScreen();

    void onArrowUp() override;
    void onArrowDown() override;
    void onArrowLeft() override;
    void onArrowRight() override;
    void onCharInput(const char inputChar) override;
    void onReturnButton(Model &model) override;
    void triggerDisplay(Renderer &view) const override;
    
private:
    enum Highlight {
        Play,
        Instruction,
        Credit
    };

    Highlight highlight;
    
    static constexpr Highlight defaultHighlight = Highlight::Play;
    
    static constexpr int screen_name_x_pos = 300;
    static constexpr int screen_name_y_pos = 50;
    inline static const std::string screenName = "Coin Weight";
    
    static constexpr int text_x_pos = 300;
    static constexpr int top_button_y_pos = 300;
    inline static const std::vector<std::string> buttons {
        "Play", "Instruction", "Credit"
    };
};



}
}

#endif
