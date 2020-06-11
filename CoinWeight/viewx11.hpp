//
//  viewx11.hpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef viewx11_hpp
#define viewx11_hpp

#include <memory>
#include <string>
#include <array>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

#include "title.hpp"
#include "instruction.hpp"
#include "credit.hpp"
#include "gamesettings.hpp"
#include "gameplayhuman.hpp"
#include "gameplaycomputer.hpp"

#include "input.hpp"

#include "coinselection.hpp"
#include "weighresult.hpp"
#include "weighcounter.hpp"

#include "exception.hpp"

namespace CoinWeight {



class ViewX11 final {
public:
    ViewX11();
    ~ViewX11();
    
    
    
    //***************************************************************
    
    enum { Black, White, Red, Blue, Green, Gold, Max = Gold };
    
    // Display for Game Over
    void displayLayoutGameOver(const bool isWin);
    
    // Draw coins
    // Reverts foreground to default after use
    // The integer parameters are counted from 0
    void drawCoin(const CoinGroup group, const size_t coinIndex,
                  const size_t row, const size_t column);
    static const int coinColor(const CoinGroup group);
    
    // Draw weigh result, text and scalre
    // Reverts foreground to default after use
    void drawWeighResultText(const WeighResult weighResult);
    void drawWeighingScale(const WeighResult weighResult); // Need to be revised
    
    // Displaying details for text
    static constexpr int border = 5;
    static constexpr int font_width = 6;
    static constexpr int font_height = 10;
    static constexpr int total_string_width(const size_t string_len) {
        return font_width * string_len + 2 * border;
    }
    static constexpr int total_string_height = font_height + 2 * border;
    
    static constexpr int one_degree_to_unit = 64;
    static constexpr int circle_full_arc = 360 * one_degree_to_unit;
    
    // Coin configurations
    static constexpr int coinDiameter = 30;
    static constexpr int coinDist = 50;
    static constexpr int coin0XPos = 200;
    static constexpr int coin0YPos = 200;
    static constexpr int coinOffset = (coinDist - coinDiameter) / 2;
    static constexpr size_t coinsPerRow = 10;
    static constexpr size_t rowsDisplay = 8;
    static constexpr int defaultFGColor = Black;
    
    //*********************************************
    
    
    
    // Information for coin displaying
    const size_t numOfCoinsPerRow() const;
    const size_t numOfRowsPerDisplay() const;
    
    // Input handling functions
    const Input nextInput();
    
    // Set foreground
    void setForeground(const unsigned int colorIndex);
    
    // x_pos and y_pos for string is in its bottom-left corner position
    // Draws with the current foreground color
    void drawString(const int x_pos, const int y_pos, const std::string &str);
    
    // x_pos and y_pos for circle is in its upper-left dimension corner position
    // Draws with the current foreground color
    void drawFullCircle(const int x_pos, const int y_pos, const unsigned int diameter);
    void fillFullCircle(const int x_pos, const int y_pos, const unsigned int diameter);
    
    // x_pos and y_pos for rectangle is in its upper-left corner position
    // Draws with the current foreground color
    void drawRectangle(const int x_pos, const int y_pos, const int width, const int height);
    void fillPolygon(std::vector<XPoint> xpoints, int shape, int mode);
    
    // Clear window
    void clearWindow();
    
    // Flush display
    void flushDisplay();

private:
    
    Display *display;
    Window window;
    int screen;
    GC gc;
    XEvent event;
    
    std::array<unsigned long, Max + 1> colors;
};



};

#endif
