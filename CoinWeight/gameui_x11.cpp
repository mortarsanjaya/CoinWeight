//
//  gameui_x11.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameui_x11.hpp"
#include "exception.hpp"
#include <utility>
#include <cmath>

//************************** Constructor
GameUI_X11::GameUI_X11() {
    const int width = 800;
    const int height = 800;

    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        throw Exception<GameUI_X11>("Cannot open display");
    }
    
    screen = XDefaultScreen(display);
    window = XCreateSimpleWindow(display, XRootWindow(display, screen), 0, 0,
        width, height, 1, XBlackPixel(display, screen), XWhitePixel(display, screen));
        
    XSelectInput(display, window, KeyPressMask);
    
    XStoreName(display, window, "Coin Weight");
    
    gc = XCreateGC(display, window, 0, 0);

    XColor xcolor;
    Colormap cmap;

    std::vector<std::string> colorVals = {
        "black", "white", "red", "blue", "green", "gold"
    };
    
    cmap = DefaultColormap(display, DefaultScreen(display));
    
    for (unsigned int i = 0; i < colorVals.size(); ++i) {
        if (XParseColor(display, cmap, colorVals[i].c_str(), &xcolor) == 0) {
            throw Exception<GameUI_X11>("Cannot parse color");
        }
        XAllocColor(display, cmap, &xcolor);
        colors.emplace_back(xcolor.pixel);
    }

    XSetForeground(display, gc, colors[defaultFGColor]);

    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = height;
    hints.min_height = height;
    hints.max_height = height;
    hints.width = hints.base_width = width;
    hints.min_width = width;
    hints.max_width = width;
    XSetNormalHints(display, window, &hints);
    
    XMapRaised(display, window);
    XFlush(display);
 
    sleep(1);
}



//************************** Private methods
//******************** Basic drawing functions
void GameUI_X11::drawString(int x_pos, int y_pos, const std::string &msg, int color, bool boxed) {
    XSetForeground(display, gc, colors[color]);
    XDrawString(display, window, gc, x_pos, y_pos, msg.c_str(), msg.length());
    XSetForeground(display, gc, colors[defaultFGColor]);
    if (boxed) {
        const int border_dist = font_width;
        drawRectangle(x_pos - font_width, y_pos - font_height - font_width,
            font_width * msg.length() + 2 * border_dist, font_height + 2 * font_width);
    }
    XFlush(display);
}

void GameUI_X11::drawCircle(int x_pos, int y_pos, unsigned int radius, int color) {
    if (color > colors.size()) throw Exception<GameUI_X11>("Invalid color");
    XSetForeground(display, gc, colors[color]);
    XDrawArc(display, window, gc, x_pos, y_pos, radius, radius, 0, circle_full_arc);
    XSetForeground(display, gc, colors[defaultFGColor]);
    XFlush(display);
}

void GameUI_X11::fillCircle(int x_pos, int y_pos, unsigned int radius, int color) {
    if (color > colors.size()) throw Exception<GameUI_X11>("Invalid color");
    XSetForeground(display, gc, colors[color]);
    XFillArc(display, window, gc, x_pos, y_pos, radius, radius, 0, circle_full_arc);
    XSetForeground(display, gc, colors[defaultFGColor]);
    XFlush(display);
}

void GameUI_X11::drawRectangle(int x_pos, int y_pos, int width, int height) {
    XDrawLine(display, window, gc, x_pos, y_pos, x_pos + width, y_pos);
    XDrawLine(display, window, gc, x_pos, y_pos, x_pos, y_pos + height);
    XDrawLine(display, window, gc, x_pos + width, y_pos, x_pos + width, y_pos + height);
    XDrawLine(display, window, gc, x_pos, y_pos + height, x_pos + width, y_pos + height);
    XFlush(display);
}

//******************** Tons of helper functions
//**** Number of weighings
const std::string GameUI_X11::numOfWeighsText(const WeighCounter &counter) const {
    std::string numOfWeighsStr = "Number of comparisons remaining: ";
    numOfWeighsStr += std::to_string(counter.numOfWeighsLeft());
    numOfWeighsStr += " out of ";
    numOfWeighsStr += std::to_string(counter.numOfWeighsMax());
    return numOfWeighsStr;
}

//**** Weigh result
void GameUI_X11::drawWeighResultText(const WeighResult weighResult) {
    const std::pair<std::string, int> weighResultText = [&weighResult]() {
        switch (weighResult) {
            case WeighResult::Start:
                return std::pair<std::string, int>("", Black);
            case WeighResult::Balance:
                return std::pair<std::string, int>("The two groups are balanced.", Black);
            case WeighResult::LeftHeavy:
                return std::pair<std::string, int>("The left group is heavier.", Black);
            case WeighResult::RightHeavy:
                return std::pair<std::string, int>("The right group is heavier.", Black);
            case WeighResult::Invalid:
                return std::pair<std::string, int>("Invalid move!", Red);
        }
    }();
    
    // Hack: Draw scale as well, lol
    {
        
        std::vector<XPoint> xpoints {
            {95, 180},
            {95, 280},
            {90, 280},
            {60, 300},
            {50, 320},
            {50, 340},
            {150, 340},
            {150, 320},
            {140, 300},
            {110, 280},
            {105, 280},
            {105, 180}
        };
        
        XSetForeground(display, gc, colors[Blue]);
        XFillPolygon(display, window, gc, xpoints.begin().base(), xpoints.size(), Nonconvex, CoordModeOrigin);
    }
    
    {
        const int radius = 20;
        XSetForeground(display, gc, colors[Green]);
        XFillArc(display, window, gc, 100 - radius, 181 - 2 * radius, radius * 2, radius * 2, 0, circle_full_arc);
    }
    
    {
        const auto anchors = [&weighResult]() -> std::pair<XPoint, XPoint> {
            const int y_tilt = 20;
            const int y_base = 180;
            const int x_base = 100;
            const int x_shift = 50;
            switch (weighResult) {
                case WeighResult::Start:
                case WeighResult::Invalid:
                case WeighResult::Balance:
                    return {{x_base - x_shift, y_base}, {x_base + x_shift, y_base}};
                case WeighResult::LeftHeavy:
                    return {{x_base - x_shift, y_base + y_tilt}, {x_base + x_shift, y_base - y_tilt}};
                case WeighResult::RightHeavy:
                    return {{x_base - x_shift, y_base - y_tilt}, {x_base + x_shift, y_base + y_tilt}};
            }
        }();
        
        const short center_anchor_y_shift = 50;
        const XPoint left_anchor = anchors.first;
        const XPoint right_anchor = anchors.second;
        const XPoint left_center = {left_anchor.x, static_cast<short>(left_anchor.y + center_anchor_y_shift)};
        const XPoint right_center = {right_anchor.x, static_cast<short>(right_anchor.y + center_anchor_y_shift)};
        
        const int one_degree_scale = 64;
        const int south_degree = 270;
        const int range = 100;
        const int radius = 25;
        const int angle1 = one_degree_scale * (south_degree - range / 2);
        const int angle2 = one_degree_scale * range;
        
        const auto weighpoints = [&left_center, &right_center]() -> std::vector<XPoint> {
            const double converter = M_PI / (double(one_degree_scale) * 180);
            const double center_x_shift = - radius * cos(double(angle1) * converter);
            const double center_y_shift = - radius * sin(double(angle1) * converter);
            return std::vector<XPoint> {
                {static_cast<short>(left_center.x - center_x_shift), static_cast<short>(left_center.y + center_y_shift)},
                {static_cast<short>(left_center.x + center_x_shift), static_cast<short>(left_center.y + center_y_shift)},
                {static_cast<short>(right_center.x - center_x_shift), static_cast<short>(right_center.y + center_y_shift)},
                {static_cast<short>(right_center.x + center_x_shift), static_cast<short>(right_center.y + center_y_shift)}
            };
        }();
        
        XSetForeground(display, gc, colors[Black]);
        XDrawLine(display, window, gc, left_anchor.x, left_anchor.y, right_anchor.x, right_anchor.y);
        XDrawLine(display, window, gc, left_anchor.x, left_anchor.y, weighpoints[0].x, weighpoints[0].y);
        XDrawLine(display, window, gc, left_anchor.x, left_anchor.y, weighpoints[1].x, weighpoints[1].y);
        XDrawLine(display, window, gc, right_anchor.x, right_anchor.y, weighpoints[2].x, weighpoints[2].y);
        XDrawLine(display, window, gc, right_anchor.x, right_anchor.y, weighpoints[3].x, weighpoints[3].y);
        
        XSetForeground(display, gc, colors[Red]);
        XFillArc(display, window, gc, left_center.x - radius, left_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        XSetForeground(display, gc, colors[Blue]);
        XFillArc(display, window, gc, right_center.x - radius, right_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        
        XSetForeground(display, gc, colors[White]);
        std::vector<XPoint> leftTrianglePoints{left_center, weighpoints[0], weighpoints[1]};
        XFillPolygon(display, window, gc, leftTrianglePoints.begin().base(), leftTrianglePoints.size(), Convex, CoordModeOrigin);
        std::vector<XPoint> rightTrianglePoints{right_center, weighpoints[2], weighpoints[3]};
        XFillPolygon(display, window, gc, rightTrianglePoints.begin().base(), rightTrianglePoints.size(), Convex, CoordModeOrigin);
        
        XSetForeground(display, gc, colors[Black]);
        XDrawArc(display, window, gc, left_center.x - radius, left_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        XDrawArc(display, window, gc, right_center.x - radius, right_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
    }
        
    XSetForeground(display, gc, colors[defaultFGColor]);
    
    drawString(30, 90, weighResultText.first, weighResultText.second, false);
}

//**** Coin
const int GameUI_X11::coinColor(CoinSelection::Group coinState) const {
    switch (coinState) {
        case CoinSelection::Group::NoSelect:
            return GameUI_X11::Gold;
        case CoinSelection::Group::LeftWeigh:
            return GameUI_X11::Red;
        case CoinSelection::Group::RightWeigh:
            return GameUI_X11::Blue;
        case CoinSelection::Group::Guess:
            return GameUI_X11::Green;
    }
}

void GameUI_X11::drawCoin(const CoinSelection::Group coinState, const size_t coinIndex) {

    const int x_pos = coin0XPos + coinDist * (coinIndex % coinsPerRow);
    const int y_pos = coin0YPos + coinDist * (coinIndex / coinsPerRow);
    fillCircle(x_pos, y_pos, coinRadius, coinColor(coinState));
    drawCircle(x_pos, y_pos, coinRadius, GameUI_X11::Black);
    drawString(x_pos, y_pos, std::to_string(coinIndex + 1), defaultFGColor, false);
}

//**** Return button
void GameUI_X11::drawReturnButton() {
    drawString(305, 515, "Return", defaultFGColor, true);
}

//**** Game Play screen
void GameUI_X11::drawGamePlayHumanHighlight(const GamePlayHumanScreen &screen) {
    const GamePlayHumanScreen::ScreenHighlight screenHighlight = screen.currScreenHighlight();
    const size_t coinHighlight = screen.currCoinHighlight();
    const int x_pos = coin0XPos - 6 + coinDist * (coinHighlight % coinsPerRow);
    const int y_pos = coin0YPos - 12 + coinDist * (coinHighlight / coinsPerRow);
    drawString(300, coin0YPos - 2 * coinDist, "Weigh", defaultFGColor,
        screenHighlight == GamePlayHumanScreen::ScreenHighlight::WeighButton);
    drawString(300, coin0YPos - coinDist, "Guess", defaultFGColor,
        screenHighlight == GamePlayHumanScreen::ScreenHighlight::GuessButton);
    if (screenHighlight == GamePlayHumanScreen::ScreenHighlight::Coins) {
        drawCircle(x_pos, y_pos, 15, Black); // magic number :(
    }
    
}

void GameUI_X11::drawGamePlayNumOfWeighs(const WeighCounter &counter) {
    drawString(30, 30, numOfWeighsText(counter), defaultFGColor, false);
    // magic number :(
}

//**** Game Over screen
void GameUI_X11::drawGameOverEndMessage(const GuessResult guessResult) {
    auto guessStr = [&guessResult]() -> std::string {
        switch (guessResult) {
            case GuessResult::Correct:
                return "You Win!";
                break;
            case GuessResult::Incorrect:
                return "You Lose :(";
                break;
            case GuessResult::Invalid:
                return "WHAT...";
                break;
        }
    }();
    
    drawString(300, 200, guessStr, defaultFGColor, false);
}
void GameUI_X11::drawGameOverNumOfWeighs(const WeighCounter &counter) {
    drawString(300, 300, numOfWeighsText(counter), defaultFGColor, false);
}

//**** Clear screen
void GameUI_X11::clearScreen() {
    XClearWindow(display, window);
    XFlush(display);
}



//************************** Public methods
void GameUI_X11::drawTitleScreen(const TitleScreen &titleScreen) {
    clearScreen();
    
    const int stringHeight = 20;
    const TitleScreen::Highlight highlight = titleScreen.currHighlight();
    
    drawString(300, 50, "Coin Weight", defaultFGColor, false);
    drawString(300, 300 + stringHeight, "Play", defaultFGColor,
        highlight == TitleScreen::Highlight::Play);
    drawString(300, 300 + 2 * stringHeight, "Instruction", defaultFGColor,
        highlight == TitleScreen::Highlight::Instruction);
    drawString(300, 300 + 3 * stringHeight, "Credit", defaultFGColor,
        highlight == TitleScreen::Highlight::Credit);
}

void GameUI_X11::drawInstructionScreen(const InstructionScreen &instructionScreen) {
    const int x_pos_page_name = 300;
    int y_pos = 100;
    const int x_pos_page_instr = 320;
    const int y_pos_incr = 20;
    clearScreen();
    std::vector<std::vector<std::string>> displayStrings;
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Main Page:",
        "Press Up/Down to select buttons.",
        "Press Enter/Return to switch page."
    });
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Option Page:",
        "Press Left/Right to change selected option.",
        "Press Enter/Return to start game."
    });
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Game Play Page (Human play):",
        "Press arrow keys to select coins.",
        "Press '1' to move selected coin to the red (left) set.",
        "Press '2' to move selected coin to the blue (right) set.",
        "Press '3' to move selected coin to the green (guess) set.",
        "Press 'w' to weigh.",
        "Press 'g' to guess.",
        "Press 'h' to switch to history."
    });
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Game Play Page (Computer play):",
        "Press Enter/Return to trigger the computer's move.",
        "Press 'h' to switch to history."
    });
    
    displayStrings.emplace_back(std::vector<std::string>{
        "Game History Page:",
        "Press Enter/Return to go back to the game play page.",
        "Press Left/Right to switch between previous moves."
    });
    
        
    for (auto pageStrList : displayStrings) {
        for (int i = 0; i < pageStrList.size(); ++i) {
            drawString(i == 0 ? x_pos_page_name : x_pos_page_instr, y_pos,
                pageStrList[i], defaultFGColor, false);
            y_pos += y_pos_incr;
        }
    }
    
    drawReturnButton();
}

void GameUI_X11::drawCreditScreen(const CreditScreen &creditScreen) {
    clearScreen();
    drawString(300, 300, "---", defaultFGColor, false);
    drawReturnButton();
}

void GameUI_X11::drawGameOptionScreen(const GameOptionScreen &gameOptionScreen)
{
    const int stringHeight = 20;
    clearScreen();
    
    const GameOptionScreen::Highlight highlight = gameOptionScreen.currHighlight();
    const  GameSettings &settings = gameOptionScreen.currSettings();
    
    const std::string gameLevelStr = [&settings]() -> std::string {
        switch (settings.gameLevel()) {
            case GameLevel::Easy:
                return "Easy";
                break;
            case GameLevel::Medium:
                return "Medium";
                break;
            case GameLevel::Hard:
                return "Hard";
                break;
            }
    }();
    
    drawString(300, 50, "Coin Weight", defaultFGColor, false);
    drawString(300, 300 + stringHeight, "Number of Coins:", defaultFGColor, false);
    drawString(300, 300 + 2 * stringHeight, "Level:", defaultFGColor, false);
    drawString(300, 300 + 3 * stringHeight, "Mode:", defaultFGColor, false);
    
    drawString(405, 300 + stringHeight,
        std::to_string(settings.numOfCoins()),
        defaultFGColor, highlight == GameOptionScreen::Highlight::NumOfCoins);
    drawString(405, 300 + 2 * stringHeight, gameLevelStr,
        defaultFGColor, highlight == GameOptionScreen::Highlight::Level);
    drawString(405, 300 + 3 * stringHeight,
        settings.isHumanMode() ? "Human" : "Computer",
        defaultFGColor, highlight == GameOptionScreen::Highlight::Mode);
}

void GameUI_X11::receiveInput() {
    XNextEvent(display, &event);
}

const Input GameUI_X11::lastInput() {
    if (event.type == KeyPress) {
        switch (XLookupKeysym(&(event.xkey), 0)) {
            case XK_0:          return Input('0');
            case XK_1:          return Input('1');
            case XK_2:          return Input('2');
            case XK_3:          return Input('3');
            case XK_Return:     return Input('\n');
            case XK_Left:       return Input(Input::Arrow::Left);
            case XK_Right:      return Input(Input::Arrow::Right);
            case XK_Up:         return Input(Input::Arrow::Up);
            case XK_Down:       return Input(Input::Arrow::Down);
            default:            return Input();
        }
    } else {
        return Input();
    }
}



//************************** Game View X11 Exception header message
template<> const std::string Exception<GameUI_X11>::headerMessage() const {
    return "Game View X11 Failure: ";
}
