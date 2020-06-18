//
//  gameplaycomputer.cpp
//  CoinWeight
//
//  Created by Gian Cordana Sanjaya on 2020-04-22.
//  Copyright © 2020 -. All rights reserved.
//

#include "gameplaycomputer.hpp"
#include "model.hpp"
#include "viewx11.hpp"
#include "computerfactory.hpp"

#include <cmath>

using namespace CoinWeight;
using namespace CoinWeight::X11;

//************************** Constructor
GamePlayComputer::GamePlayComputer(const size_t nCoinsTotal, const GameLevel level) :
buttonHighlight(ButtonHighlight::NextMove),
coinNavigator(nCoinsTotal, rowsDisplay, coinsPerRow),
isOnButtonHighlight(true),
coinSet(nCoinsTotal),
selection(nCoinsTotal),
history(),
computer(),
lastResult(WeighResult::Start),
counter(nCoinsTotal, level)
{
    computer = ComputerFactory::create(nCoinsTotal, level);
    computerSetSelection();
}



//************************** Arrow button handling
//**** Main
void GamePlayComputer::onArrowUp() {
    if (isOnButtonHighlight) {
        buttonHighlightUp();
    } else {
        coinHighlightUp();
    }
}

void GamePlayComputer::onArrowDown() {
    if (isOnButtonHighlight) {
        buttonHighlightDown();
    } else {
        coinHighlightDown();
    }
}

void GamePlayComputer::onArrowLeft() {
    if (isOnButtonHighlight) {
        buttonHighlightLeft();
    } else {
        coinHighlightLeft();
    }
}

void GamePlayComputer::onArrowRight() {
    if (isOnButtonHighlight) {
        buttonHighlightRight();
    } else {
        coinHighlightRight();
    }
}

//**** Helper (button highlight)
void GamePlayComputer::buttonHighlightUp() {
}

void GamePlayComputer::buttonHighlightDown() {
}

void GamePlayComputer::buttonHighlightLeft() {}

void GamePlayComputer::buttonHighlightRight() {
    transitionToCoinHighlight();
}


//**** Helper (coin highlight)
void GamePlayComputer::coinHighlightUp() {
    coinNavigator.scrollUp();
}

void GamePlayComputer::coinHighlightDown() {
    coinNavigator.scrollDown();
}

void GamePlayComputer::coinHighlightLeft() {
    if (coinNavigator.currColumn() == 0) {
        transitionToButtonHighlight();
    } else {
        coinNavigator.scrollLeft();
    }
}

void GamePlayComputer::coinHighlightRight() {
    coinNavigator.scrollRight();
}

//**** Helper (transition)
void GamePlayComputer::transitionToButtonHighlight() {
    isOnButtonHighlight = true;
}

void GamePlayComputer::transitionToCoinHighlight() {
    isOnButtonHighlight = false;
}



//************************** Character input handling
void GamePlayComputer::onCharInput(const char inputChar) {}



//************************** Return button handling
void GamePlayComputer::onReturnButton(Model &model) {
    if (isOnButtonHighlight) {
        if (selection.sizeOfGuessGroup() == 0) {
            if (counter.isCappedOut()) {
                lastResult = WeighResult::Invalid;
            } else {
                lastResult = compareWeight();
            }
            
            computer->changeState(lastResult);
            selection.reset();
            
            if (lastResult != WeighResult::Invalid) {
                history.add(selection, lastResult);
                counter.weighingDone();
            }
            
            computerSetSelection();
            
        } else {
            const GuessResult result = guessFakeCoins();
            switch (result) {
                case GuessResult::Invalid:
                    model.switchToGameOver(false);
                    break;
                case GuessResult::Correct:
                    model.switchToGameOver(true);
                    break;
                case GuessResult::Incorrect:
                    model.switchToGameOver(false);
                    break;
            }
        }
    }
}
//**** Game operations as helper
const WeighResult GamePlayComputer::compareWeight() const {
    return coinSet.compareWeight(selection);
}

const GuessResult GamePlayComputer::guessFakeCoins() const {
    return coinSet.guessFakeCoins(selection);
}



//************************** Computer sets up selection
void GamePlayComputer::computerSetSelection() {
    computer->setSelection(selection);
}



//************************** UI display
void GamePlayComputer::triggerDisplay(Renderer &view) const {
    displayLayoutGamePlayComputer(view);
    displayCoinSelection(view);
    displayWeighResult(view);
    displayWeighCounter(view);
    if (isOnButtonHighlight) {
        displayButtonHighlight(view);
    } else {
        displayCoinHighlight(view);
    }
}

void GamePlayComputer::displayLayoutGamePlayComputer(Renderer &view) const {
    view.clearWindow();
    view.setForeground(RenderConst::defaultFGColor);

    const std::string &nextMoveStr = "Next Move";
    
    view.drawString(50 + RenderConst::border, 300 + RenderConst::total_string_height - RenderConst::border, nextMoveStr);
    
    view.flushDisplay();
}

void GamePlayComputer::displayButtonHighlight(Renderer &view) const {
    switch (buttonHighlight) {
        case GamePlayComputer::ButtonHighlight::NextMove:
            view.drawRectangle(50, 300, 64, RenderConst::total_string_height);
            break;
    }
    
    view.flushDisplay();
}

void GamePlayComputer::displayCoinSelection(Renderer &view) const {
    for (size_t row = 0; row < coinNavigator.numOfRowsDisplayed(); ++row) {
        bool coinExhausted = false;
        for (size_t column = 0; column < coinNavigator.numOfColumns(); ++column) {
            const size_t coinIndex = (row + coinNavigator.currTopRow()) * coinNavigator.numOfColumns() + column;
            if (coinIndex >= selection.totalSize()) {
                coinExhausted = true;
                break;
            }
            drawCoin(view, selection.at(coinIndex), coinIndex, row, column);
        }
        
        if (coinExhausted) break;
    }
    
    view.flushDisplay();
}

void GamePlayComputer::displayWeighResult(Renderer &view) const {
    drawWeighResultText(view);
    drawWeighingScale(view);
    
    view.flushDisplay();
}

void GamePlayComputer::displayWeighCounter(Renderer &view) const {
    view.setForeground(RenderConst::Black);
    std::string numOfWeighsStr = "Number of comparisons done: ";
    numOfWeighsStr += std::to_string(counter.numOfWeighsDone());
    numOfWeighsStr += " out of ";
    numOfWeighsStr += std::to_string(counter.numOfWeighsMax());
    view.drawString(30, 60, numOfWeighsStr);
    
    view.flushDisplay();
}

void GamePlayComputer::displayCoinHighlight(Renderer &view) const {
    view.drawRectangle(coin0XPos + coinDist * coinNavigator.currColumn(), coin0YPos + coinDist * coinNavigator.currRowDisplay(), coinDist, coinDist);
    
    view.flushDisplay();
}



//******************** Draw coin
void GamePlayComputer::drawCoin(Renderer &view, const CoinGroup group, const size_t coinIndex,
                          const size_t row, const size_t column) const
{
    const int x_pos = coin0XPos + coinOffset + coinDist * column;
    const int y_pos = coin0YPos + coinOffset + coinDist * row;
    view.setForeground(coinColor(group));
    view.fillFullCircle(x_pos, y_pos, coinDiameter);
    view.setForeground(RenderConst::Black);
    view.drawFullCircle(x_pos, y_pos, coinDiameter);
    view.setForeground(RenderConst::defaultFGColor);
    view.drawString(x_pos, y_pos, std::to_string(coinIndex + 1));
}

const int GamePlayComputer::coinColor(const CoinGroup group) {
    switch (group) {
        case CoinGroup::NoSelect:
            return RenderConst::Gold;
        case CoinGroup::LeftWeigh:
            return RenderConst::Red;
        case CoinGroup::RightWeigh:
            return RenderConst::Blue;
        case CoinGroup::Guess:
            return RenderConst::Green;
    }
}



//******************** Helper functions for drawing weigh result
void GamePlayComputer::drawWeighResultText(Renderer &view) const {
    const int x_pos = 30;
    const int y_pos = 90;
    view.setForeground(RenderConst::Black);
    switch (lastResult) {
        case WeighResult::Start:
            view.drawString(x_pos, y_pos, "");
            break;
        case WeighResult::Balance:
            view.drawString(x_pos, y_pos, "The two groups are balanced.");
            break;
        case WeighResult::LeftHeavy:
            view.drawString(x_pos, y_pos, "The left group is heavier.");
            break;
        case WeighResult::RightHeavy:
            view.drawString(x_pos, y_pos, "The right group is heavier.");
            break;
        case WeighResult::Invalid:
            view.setForeground(RenderConst::Red);
            view.drawString(x_pos, y_pos, "Invalid move!");
            break;
    }
    
    view.setForeground(RenderConst::defaultFGColor);
}

void GamePlayComputer::drawWeighingScale(Renderer &view) const {
    {
        
        std::vector<XPoint> xpoints {
            {695, 60},
            {695, 120},
            {690, 120},
            {660, 140},
            {650, 160},
            {650, 180},
            {750, 180},
            {750, 160},
            {740, 140},
            {710, 120},
            {705, 120},
            {705, 60}
        };
        
        view.setForeground(RenderConst::Blue);
        view.fillPolygon(xpoints, Nonconvex, CoordModeOrigin);
    }
    
    {
        const int radius = 20;
        view.setForeground(RenderConst::Green);
        view.fillFullCircle(700 - radius, 61 - 2 * radius, radius * 2);
    }
    
    {
        const WeighResult weighResult = lastResult;
        const auto anchors = [&weighResult]() -> std::pair<XPoint, XPoint> {
            const int x_base = 700;
            const int y_base = 60;
            const int x_shift = 50;
            const int y_tilt = 20;
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
        
        const short center_anchor_y_shift = 20;
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
        
        view.setForeground(RenderConst::Black);
        view.drawLine(left_anchor.x, left_anchor.y, right_anchor.x, right_anchor.y);
        view.drawLine(left_anchor.x, left_anchor.y, weighpoints[0].x, weighpoints[0].y);
        view.drawLine(left_anchor.x, left_anchor.y, weighpoints[1].x, weighpoints[1].y);
        view.drawLine(right_anchor.x, right_anchor.y, weighpoints[2].x, weighpoints[2].y);
        view.drawLine(right_anchor.x, right_anchor.y, weighpoints[3].x, weighpoints[3].y);
        
        view.setForeground(RenderConst::Red);
        view.fillArc(left_center.x - radius, left_center.y - radius, 2 * radius, angle1, angle2);
        view.setForeground(RenderConst::Blue);
        view.fillArc(right_center.x - radius, right_center.y - radius, 2 * radius, angle1, angle2);
        
        view.setForeground(RenderConst::White);
        std::vector<XPoint> leftTrianglePoints{left_center, weighpoints[0], weighpoints[1]};
        view.fillPolygon(leftTrianglePoints, Convex, CoordModeOrigin);
        std::vector<XPoint> rightTrianglePoints{right_center, weighpoints[2], weighpoints[3]};
        view.fillPolygon(rightTrianglePoints, Convex, CoordModeOrigin);
        
        view.setForeground(RenderConst::Black);
        view.drawArc(left_center.x - radius, left_center.y - radius, 2 * radius, angle1, angle2);
        view.drawArc(right_center.x - radius, right_center.y - radius, 2 * radius, angle1, angle2);
    }
}
