//
//  controller.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-14.
//  Copyright © 2020 -. All rights reserved.
//

#include "controller.hpp"
#include "modelstatefactory.hpp"

using namespace CoinWeight;

//************************** Constructor
Controller::Controller() :
model(), ui()
{}



//************************** Input processing
void Controller::processInput() {
    const Input input = ui.nextInput();
    switch (input.inputType()) {
        case Input::Type::Unknown:
            break;
        case Input::Type::Char:
            model.onCharInput(input.whatChar());
            break;
        case Input::Type::Arrow:
            switch (input.whatArrow()) {
                case Input::Arrow::Up:
                    model.onArrowUp();
                    break;
                case Input::Arrow::Down:
                    model.onArrowDown();
                    break;
                case Input::Arrow::Left:
                    model.onArrowLeft();
                    break;
                case Input::Arrow::Right:
                    model.onArrowRight();
                    break;
            }
            break;
        case Input::Type::Return:
            model.onReturnButton();
            break;
    }
}



//************************** Display updating
void Controller::updateDisplay() {
    model.updateView(ui);
}
