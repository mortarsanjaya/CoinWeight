//
//  controller.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-05-14.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef controller_hpp
#define controller_hpp

#include "viewx11.hpp"
#include "model.hpp"

#include "coingroup.hpp"
#include "weighresult.hpp"
#include "gamelevel.hpp"

namespace CoinWeight {



class Controller final {
public:
    Controller();
    
    // Input processing
    void processInput();
    
    // Update display
    void updateDisplay();

private:
    Model model;
    ViewX11 ui;
};



};

#endif
