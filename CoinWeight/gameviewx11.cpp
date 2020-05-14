//
//  gameviewx11.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-03-03.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameviewx11.hpp"
#include "exception.hpp"
#include <utility>
#include <cmath>

//************************** Constructor
GameViewX11::GameViewX11() {
    const int width = 800;
    const int height = 800;

    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        throw Exception<GameViewX11>("Cannot open display");
    }
    
    screen = XDefaultScreen(display);
    mainWindow = XCreateSimpleWindow(display, XRootWindow(display, screen), 0, 0,
        width, height, 1, XBlackPixel(display, screen), XWhitePixel(display, screen));
    historyWindow = XCreateSimpleWindow(display, XRootWindow(display, screen), 0, 0,
        width, height, 1, XBlackPixel(display, screen), XWhitePixel(display, screen));
        
    XSelectInput(display, mainWindow, KeyPressMask);
    XSelectInput(display, historyWindow, KeyPressMask);
    
    XStoreName(display, mainWindow, "Coin Weight");
    XStoreName(display, historyWindow, "Coin Weight History");
    
    gc = XCreateGC(display, mainWindow, 0, 0);

    XColor xcolor;
    Colormap cmap;

    std::vector<std::string> colorVals = {
        "black", "white", "red", "blue", "green", "gold"
    };
    
    cmap = DefaultColormap(display, DefaultScreen(display));
    
    for (unsigned int i = 0; i < colorVals.size(); ++i) {
        if (XParseColor(display, cmap, colorVals[i].c_str(), &xcolor) == 0) {
            throw Exception<GameViewX11>("Cannot parse color");
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
    XSetNormalHints(display, mainWindow, &hints);
    XSetNormalHints(display, historyWindow, &hints);
    
    XMapRaised(display, historyWindow);
    XMapRaised(display, mainWindow);
    XFlush(display);
 
    sleep(1);
}



//************************** Private methods
//******************** Basic drawing functions
void GameViewX11::drawString(DrawingWindow window, int x_pos, int y_pos, const std::string &msg, int color, bool boxed) {
    XSetForeground(display, gc, colors[color]);
    XDrawString(display, windowToDraw(window), gc, x_pos, y_pos, msg.c_str(), msg.length());
    XSetForeground(display, gc, colors[defaultFGColor]);
    if (boxed) {
        const int border_dist = font_width;
        drawRectangle(window, x_pos - font_width, y_pos - font_height - font_width,
            font_width * msg.length() + 2 * border_dist, font_height + 2 * font_width);
    }
    XFlush(display);
}

void GameViewX11::drawCircle(DrawingWindow window, int x_pos, int y_pos, unsigned int radius, int color) {
    if (color > colors.size()) throw Exception<GameViewX11>("Invalid color");
    XSetForeground(display, gc, colors[color]);
    XDrawArc(display, windowToDraw(window), gc, x_pos, y_pos, radius, radius, 0, circle_full_arc);
    XSetForeground(display, gc, colors[defaultFGColor]);
    XFlush(display);
}

void GameViewX11::fillCircle(DrawingWindow window, int x_pos, int y_pos, unsigned int radius, int color) {
    if (color > colors.size()) throw Exception<GameViewX11>("Invalid color");
    XSetForeground(display, gc, colors[color]);
    XFillArc(display, windowToDraw(window), gc, x_pos, y_pos, radius, radius, 0, circle_full_arc);
    XSetForeground(display, gc, colors[defaultFGColor]);
    XFlush(display);
}

void GameViewX11::drawRectangle(DrawingWindow window, int x_pos, int y_pos, int width, int height) {
    XDrawLine(display, windowToDraw(window), gc, x_pos, y_pos, x_pos + width, y_pos);
    XDrawLine(display, windowToDraw(window), gc, x_pos, y_pos, x_pos, y_pos + height);
    XDrawLine(display, windowToDraw(window), gc, x_pos + width, y_pos, x_pos + width, y_pos + height);
    XDrawLine(display, windowToDraw(window), gc, x_pos, y_pos + height, x_pos + width, y_pos + height);
    XFlush(display);
}

//******************** Tons of helper functions
//**** Number of weighings
const std::string GameViewX11::numOfWeighsText(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) const {
    std::string numOfWeighsStr = "Number of comparisons remaining: ";
    numOfWeighsStr += std::to_string(numOfWeighsLeft);
    numOfWeighsStr += " out of ";
    numOfWeighsStr += std::to_string(numOfWeighsMax);
    return numOfWeighsStr;
}

//**** Window to draw
const Window GameViewX11::windowToDraw(const DrawingWindow window) const {
    switch (window) {
        case DrawingWindow::Main:
            return mainWindow;
        case DrawingWindow::History:
            return historyWindow;
    }
}

//**** Weigh result
void GameViewX11::drawWeighResultText(const DrawingWindow window, const WeighResult weighResult) {
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
    const Window &win = (window == DrawingWindow::Main) ? mainWindow : historyWindow;
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
        XFillPolygon(display, win, gc, xpoints.begin().base(), xpoints.size(), Nonconvex, CoordModeOrigin);
    }
    
    {
        const int radius = 20;
        XSetForeground(display, gc, colors[Green]);
        XFillArc(display, win, gc, 100 - radius, 181 - 2 * radius, radius * 2, radius * 2, 0, circle_full_arc);
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
        XDrawLine(display, win, gc, left_anchor.x, left_anchor.y, right_anchor.x, right_anchor.y);
        XDrawLine(display, win, gc, left_anchor.x, left_anchor.y, weighpoints[0].x, weighpoints[0].y);
        XDrawLine(display, win, gc, left_anchor.x, left_anchor.y, weighpoints[1].x, weighpoints[1].y);
        XDrawLine(display, win, gc, right_anchor.x, right_anchor.y, weighpoints[2].x, weighpoints[2].y);
        XDrawLine(display, win, gc, right_anchor.x, right_anchor.y, weighpoints[3].x, weighpoints[3].y);
        
        XSetForeground(display, gc, colors[Red]);
        XFillArc(display, win, gc, left_center.x - radius, left_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        XSetForeground(display, gc, colors[Blue]);
        XFillArc(display, win, gc, right_center.x - radius, right_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        
        XSetForeground(display, gc, colors[White]);
        std::vector<XPoint> leftTrianglePoints{left_center, weighpoints[0], weighpoints[1]};
        XFillPolygon(display, win, gc, leftTrianglePoints.begin().base(), leftTrianglePoints.size(), Convex, CoordModeOrigin);
        std::vector<XPoint> rightTrianglePoints{right_center, weighpoints[2], weighpoints[3]};
        XFillPolygon(display, win, gc, rightTrianglePoints.begin().base(), rightTrianglePoints.size(), Convex, CoordModeOrigin);
        
        XSetForeground(display, gc, colors[Black]);
        XDrawArc(display, win, gc, left_center.x - radius, left_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
        XDrawArc(display, win, gc, right_center.x - radius, right_center.y - radius, 2 * radius, 2 * radius, angle1, angle2);
    }
        
    XSetForeground(display, gc, colors[defaultFGColor]);
    

    switch (window) {
        case GameView::DrawingWindow::Main:
            drawString(window, 30, 90, weighResultText.first, weighResultText.second, false);
            break;
        case GameView::DrawingWindow::History:
            drawString(window, 30, 30, weighResultText.first, weighResultText.second, false);
            break;
    }
}

//**** Coin
const int GameViewX11::coinColor(CoinGroup coinState) const {
    switch (coinState) {
        case CoinGroup::NoSelect:
            return GameViewX11::Gold;
        case CoinGroup::LeftWeigh:
            return GameViewX11::Red;
        case CoinGroup::RightWeigh:
            return GameViewX11::Blue;
        case CoinGroup::Guess:
            return GameViewX11::Green;
    }
}

void GameViewX11::drawCoin(DrawingWindow window, CoinGroup coinState, size_t coinIndex) {

    const int x_pos = coin0XPos + coinDist * (coinIndex % coinsPerRow);
    const int y_pos = coin0YPos + coinDist * (coinIndex / coinsPerRow);
    fillCircle(window, x_pos, y_pos, coinRadius, coinColor(coinState));
    drawCircle(window, x_pos, y_pos, coinRadius, GameViewX11::Black);
    drawString(window, x_pos, y_pos, std::to_string(coinIndex + 1), defaultFGColor, false);
}

//**** Return button
void GameViewX11::drawReturnButton() {
    drawString(DrawingWindow::Main, 305, 515, "Return", defaultFGColor, true);
}

//**** Game Play screen
void GameViewX11::drawGamePlayHumanHighlight(const GamePlayHumanScreen::ScreenHighlight screenHighlight, const size_t coinHighlight) {
    const int x_pos = coin0XPos - 6 + coinDist * (coinHighlight % coinsPerRow);
    const int y_pos = coin0YPos - 12 + coinDist * (coinHighlight / coinsPerRow);
    drawString(DrawingWindow::Main, 300, coin0YPos - 2 * coinDist, "Weigh", defaultFGColor,
        screenHighlight == GamePlayHumanScreen::ScreenHighlight::WeighButton);
    drawString(DrawingWindow::Main, 300, coin0YPos - coinDist, "Guess", defaultFGColor,
        screenHighlight == GamePlayHumanScreen::ScreenHighlight::GuessButton);
    if (screenHighlight == GamePlayHumanScreen::ScreenHighlight::Coins) {
        drawCircle(DrawingWindow::Main, x_pos, y_pos, 15, Black); // magic number :(
    }
    
}

void GameViewX11::drawGamePlayNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) {
    drawString(DrawingWindow::Main, 30, 30, numOfWeighsText(numOfWeighsLeft, numOfWeighsMax), defaultFGColor, false);
    // magic number :(
}

//**** Game Over screen
void GameViewX11::drawGameOverEndMessage(const GuessResult guessResult) {
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
    
    drawString(DrawingWindow::Main, 300, 200, guessStr, defaultFGColor, false);
}
void GameViewX11::drawGameOverNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) {
    drawString(DrawingWindow::Main, 300, 300, numOfWeighsText(numOfWeighsLeft, numOfWeighsMax), defaultFGColor, false);
}

//**** History screen
void GameViewX11::drawHistoryIndexText(const size_t index, const size_t numOfWeighs) {
    drawString(DrawingWindow::History, 300, 50, "Move " + std::to_string(index + 1) + " out of " + std::to_string(numOfWeighs), defaultFGColor, false);
}

void GameViewX11::drawEmptyHistoryScreen() {
    drawString(DrawingWindow::History, 300, 200, "You have not made any moves.", defaultFGColor, false);
}

//**** Clear screen
void GameViewX11::clearMainScreen() {
    XClearWindow(display, mainWindow);
    XFlush(display);
}

void GameViewX11::clearHistoryScreen() {
    XClearWindow(display, historyWindow);
    XFlush(display);
}

void GameViewX11::clearScreen(const DrawingWindow window) {
    switch (window) {
        case GameView::DrawingWindow::Main:
            clearMainScreen();
            break;
        case GameView::DrawingWindow::History:
            clearHistoryScreen();
            break;
    }
}



//************************** Public methods
void GameViewX11::drawTitleScreen(const TitleScreen &titleScreen) {
    clearScreen(DrawingWindow::Main);
    
    const int stringHeight = 20;
    const TitleScreen::Highlight highlight = titleScreen.currHighlight();
    
    drawString(DrawingWindow::Main, 300, 50, "Coin Weight", defaultFGColor, false);
    drawString(DrawingWindow::Main, 300, 300 + stringHeight, "Play", defaultFGColor,
        highlight == TitleScreen::Highlight::Play);
    drawString(DrawingWindow::Main, 300, 300 + 2 * stringHeight, "Instruction", defaultFGColor,
        highlight == TitleScreen::Highlight::Instruction);
    drawString(DrawingWindow::Main, 300, 300 + 3 * stringHeight, "Credit", defaultFGColor,
        highlight == TitleScreen::Highlight::Credit);
}

void GameViewX11::drawInstructionScreen(const InstructionScreen &instructionScreen) {
    const int x_pos_page_name = 300;
    int y_pos = 100;
    const int x_pos_page_instr = 320;
    const int y_pos_incr = 20;
    clearScreen(DrawingWindow::Main);
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
            drawString(DrawingWindow::Main, i == 0 ? x_pos_page_name : x_pos_page_instr, y_pos,
                pageStrList[i], defaultFGColor, false);
            y_pos += y_pos_incr;
        }
    }
    
    drawReturnButton();
}

void GameViewX11::drawCreditScreen(const CreditScreen &creditScreen) {
    clearScreen(DrawingWindow::Main);
    drawString(DrawingWindow::Main, 300, 300, "---", defaultFGColor, false);
    drawReturnButton();
}

void GameViewX11::drawGameOptionScreen(const GameOptionScreen &gameOptionScreen)
{
    const int stringHeight = 20;
    clearScreen(DrawingWindow::Main);
    
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
    
    drawString(DrawingWindow::Main, 300, 50, "Coin Weight", defaultFGColor, false);
    drawString(DrawingWindow::Main, 300, 300 + stringHeight, "Number of Coins:", defaultFGColor, false);
    drawString(DrawingWindow::Main, 300, 300 + 2 * stringHeight, "Level:", defaultFGColor, false);
    drawString(DrawingWindow::Main, 300, 300 + 3 * stringHeight, "Mode:", defaultFGColor, false);
    
    drawString(DrawingWindow::Main, 405, 300 + stringHeight,
        std::to_string(settings.numOfCoins()),
        defaultFGColor, highlight == GameOptionScreen::Highlight::NumOfCoins);
    drawString(DrawingWindow::Main, 405, 300 + 2 * stringHeight, gameLevelStr,
        defaultFGColor, highlight == GameOptionScreen::Highlight::Level);
    drawString(DrawingWindow::Main, 405, 300 + 3 * stringHeight,
        settings.isHumanMode() ? "Human" : "Computer",
        defaultFGColor, highlight == GameOptionScreen::Highlight::Mode);
}

void GameViewX11::receiveInput() {
    XNextEvent(display, &event);
}

const Input GameViewX11::lastInput() {
    if (event.type == KeyPress) {
        Input::Source source;
        if (event.xkey.window == mainWindow) {
            source = Input::Source::Main;
        } else {
            source = Input::Source::History;
        }
        switch (XLookupKeysym(&(event.xkey), 0)) {
            case XK_0:          return Input(source, '0');
            case XK_1:          return Input(source, '1');
            case XK_2:          return Input(source, '2');
            case XK_3:          return Input(source, '3');
            case XK_Return:     return Input(source, '\n');
            case XK_Left:       return Input(source, Input::Arrow::Left);
            case XK_Right:      return Input(source, Input::Arrow::Right);
            case XK_Up:         return Input(source, Input::Arrow::Up);
            case XK_Down:       return Input(source, Input::Arrow::Down);
            default:            return Input(source);
        }
    } else {
        return Input(Input::Source::Main);
    }
}



//************************** Game View X11 Exception header message
template<> const std::string Exception<GameViewX11>::headerMessage() const {
    return "Game View X11 Failure: ";
}
