//
//  gameviewsdl.cpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#include <iostream>
#include <string>
#include "gameviewsdl.hpp"
#include "sdlexception.hpp"

GameViewSDL::GameViewSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        throw Exception<GameViewSDL>("Unable to initialize SDL.");
    }
    
    historyWindow = SDL_CreateWindow("Coin Weighting", 100, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (historyWindow == nullptr) {
        SDL_Log("Unable to create history window: %s", SDL_GetError());
        throw Exception<GameViewSDL>("Unable to create history window.");
    }
    historyWindowId = SDL_GetWindowID(historyWindow);
    
    historyRenderer = SDL_CreateRenderer(historyWindow, -1, 0);
    if (historyRenderer == nullptr) {
        SDL_Log("Unable to create history renderer: %s", SDL_GetError());
        throw Exception<GameViewSDL>("Unable to create history renderer.");
    }
    
    mainWindow = SDL_CreateWindow("Coin Weighting", 0, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (mainWindow == nullptr) {
        SDL_Log("Unable to create main window: %s", SDL_GetError());
        throw Exception<GameViewSDL>("Unable to create main window.");
    }
    mainWindowId = SDL_GetWindowID(mainWindow);
    
    mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);
    if (mainRenderer == nullptr) {
        SDL_Log("Unable to create main renderer: %s", SDL_GetError());
        throw Exception<GameViewSDL>("Unable to create main renderer.");
    }
    
    if (TTF_Init() != 0) {
        throw Exception<GameViewSDL>("Unable to initialize TTF.");
    }
    
    smallFont = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", SMALL_FONT_SIZE);
    if (smallFont == nullptr) {
        throw Exception<GameViewSDL>("Unable to create small font.");
    }
    
    defaultFont = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", DEFAULT_FONT_SIZE);
    if (defaultFont == nullptr) {
        throw Exception<GameViewSDL>("Unable to create default font.");
    }
    
    hugeFont = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", HUGE_FONT_SIZE);
    if (hugeFont == nullptr) {
        throw Exception<GameViewSDL>("Unable to create huge font.");
    }
    
    SDL_SetEventFilter([](void *userdata, SDL_Event *event) {
        return (event->type == SDL_KEYDOWN || event->type == SDL_QUIT) ? 1 : 0;
    }, nullptr);
}

void GameViewSDL::drawText(DrawingWindow window, std::string text, int x, int y, int fontSize, SDL_Color color, bool boxed) {
    TTF_Font *font;
    if (fontSize == SMALL_FONT_SIZE) {
        font = smallFont;
    } else if (fontSize == DEFAULT_FONT_SIZE) {
        font = defaultFont;
    } else if (fontSize == HUGE_FONT_SIZE) {
        font = hugeFont;
    } else {
        font = defaultFont;
    }
    
    SDL_Renderer* renderer = appropriateRenderer(window);
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect msgRect;
    SDL_QueryTexture(texture, NULL, NULL, &msgRect.w, &msgRect.h);
    msgRect.x = x - msgRect.w / 2;
    msgRect.y = y - msgRect.h / 2;
    
    SDL_RenderCopy(renderer, texture, NULL, &msgRect);
    
    if (boxed) {
        drawRectangle(window, msgRect.x - 20, msgRect.y - 20, msgRect.w + 40, msgRect.h + 40, false, MAIN_COLOR);
    }
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void GameViewSDL::drawCircle(DrawingWindow window, int centerX, int centerY, int r, bool fill, SDL_Color color) {
    SDL_Renderer* renderer = appropriateRenderer(window);
    
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
    if (fill) {
        for (int w = 0; w < r * 2; ++w) {
            for (int h = 0; h < r * 2; ++h) {
                int dx = r - w;
                int dy = r - h;
                if (dx*dx + dy*dy <= r * r) {
                    SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
                }
            }
        }
    } else {
        const int32_t diameter = (r * 2);
        
        int32_t x = (r - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);
        
        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
            
            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }
            
            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }
}

void GameViewSDL::drawRectangle(DrawingWindow window, int x, int y, int width, int height, bool fill, SDL_Color color) {
    SDL_Renderer* renderer = appropriateRenderer(window);
    
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    if (fill) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void GameViewSDL::drawButton(DrawingWindow window, std::string text, int x, int y, int fontSize, SDL_Color color) {
    drawText(window, text, x, y, fontSize, color, true);
}

void GameViewSDL::drawScale(DrawingWindow window, int tilt) {
    SDL_Renderer* renderer = appropriateRenderer(window);
}

// helper functions for drawing

SDL_Renderer * GameViewSDL::appropriateRenderer(DrawingWindow window) const {
    return window == DrawingWindow::Main ? mainRenderer : historyRenderer;
}

const std::string GameViewSDL::numOfWeighsText(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) const {
    return "Number of comparisons remaining: " + std::to_string(numOfWeighsLeft)
            + " out of " + std::to_string(numOfWeighsMax);
}

void GameViewSDL::drawWeighResultText(const DrawingWindow window, const WeighResult weighResult) {
    const int xPos = window == DrawingWindow::Main ? 180 : WIDTH/2;
    const int yPos = 120;
    switch (weighResult) {
        case WeighResult::Start:
            break;
        case WeighResult::Balance:
            drawText(window, "The two groups are balanced.", xPos, yPos, SMALL_FONT_SIZE, MAIN_COLOR);
            break;
        case WeighResult::LeftHeavy:
            drawText(window, "The left group is heavier.", xPos, yPos, SMALL_FONT_SIZE, MAIN_COLOR);
            break;
        case WeighResult::RightHeavy:
            drawText(window, "The right group is heavier.", xPos, yPos, SMALL_FONT_SIZE, MAIN_COLOR);
            break;
        case WeighResult::Invalid:
            drawText(window, "Invalid move!", xPos, yPos, SMALL_FONT_SIZE, MAIN_COLOR);
            break;
    }
}

const SDL_Color GameViewSDL::coinColor(CoinGroup coinState) const {
    switch (coinState) {
        case CoinGroup::NoSelect:
            return GOLD;
        case CoinGroup::LeftWeigh:
            return RED;
        case CoinGroup::RightWeigh:
            return BLUE;
        case CoinGroup::Guess:
            return GREEN;
    }
}

void GameViewSDL::drawCoin(DrawingWindow window, CoinGroup coinState, size_t coinIndex) {
    const int x_pos = coin0XPos + coinDist * (coinIndex % coinsPerRow);
    const int y_pos = coin0YPos + coinDist * (coinIndex / coinsPerRow);
    drawCircle(window, x_pos, y_pos, coinRadius, true, coinColor(coinState));
    drawCircle(window, x_pos, y_pos, coinRadius, false, MAIN_COLOR);
    drawText(window, std::to_string(coinIndex + 1), x_pos + 1, y_pos, SMALL_FONT_SIZE, BLACK, false);
}

void GameViewSDL::drawReturnButton() {
    drawText(DrawingWindow::Main, "Return", WIDTH / 2, HEIGHT - 60, DEFAULT_FONT_SIZE, HIGHLIGHTED_COLOR);
}

void GameViewSDL::drawGamePlayHumanHighlight(const GamePlayHumanScreen::ScreenHighlight screenHighlight, const size_t coinHighlight) {
    const int x_pos = coin0XPos - coinRadius - 5 + coinDist * (coinHighlight % coinsPerRow);
    const int y_pos = coin0YPos - coinRadius - 5 + coinDist * (coinHighlight / coinsPerRow);
    drawText(DrawingWindow::Main, "Weigh", WIDTH / 2, coin0YPos - 2 * coinDist, DEFAULT_FONT_SIZE,
             screenHighlight == GamePlayHumanScreen::ScreenHighlight::WeighButton ? HIGHLIGHTED_COLOR : MAIN_COLOR);
    drawText(DrawingWindow::Main, "Guess", WIDTH / 2, coin0YPos - coinDist, DEFAULT_FONT_SIZE,
             screenHighlight == GamePlayHumanScreen::ScreenHighlight::GuessButton ? HIGHLIGHTED_COLOR : MAIN_COLOR);
    if (screenHighlight == GamePlayHumanScreen::ScreenHighlight::Coins) {
        drawRectangle(DrawingWindow::Main, x_pos, y_pos, coinRadius * 2 + 10, coinRadius * 2 + 10, false, MAIN_COLOR);
    }
    flushMainScreen();
}

void GameViewSDL::drawGamePlayNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) {
    drawText(DrawingWindow::Main, numOfWeighsText(numOfWeighsLeft, numOfWeighsMax), 200, 50, SMALL_FONT_SIZE, MAIN_COLOR);
}

// Game Over screen
void GameViewSDL::drawGameOverEndMessage(const GuessResult guessResult) {
    auto guessStr = [&guessResult]() -> std::string {
        switch (guessResult) {
            case GuessResult::Correct:
                return "You Win!";
            case GuessResult::Incorrect:
                return "You Lose :(";
            case GuessResult::Invalid:
                return "WHAT...";
        }
    }();
    
    drawText(DrawingWindow::Main, guessStr, WIDTH/2, HEIGHT/2, HUGE_FONT_SIZE, MAIN_COLOR);
}

void GameViewSDL::drawGameOverNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) {
    drawText(DrawingWindow::Main, numOfWeighsText(numOfWeighsLeft, numOfWeighsMax), WIDTH/2, HEIGHT/2 + 100, DEFAULT_FONT_SIZE, MAIN_COLOR);
    flushMainScreen();
}

// History screen
void GameViewSDL::drawHistoryIndexText(const size_t index, const size_t numOfWeighs) {
    drawText(DrawingWindow::History, "Move " + std::to_string(index + 1) + " out of " + std::to_string(numOfWeighs),
             WIDTH/2, 50, SMALL_FONT_SIZE, MAIN_COLOR);
    flushHistoryScreen();
}

void GameViewSDL::drawEmptyHistoryScreen() {
    drawText(DrawingWindow::History, "You have not made any moves.", WIDTH/2, HEIGHT/2, DEFAULT_FONT_SIZE, MAIN_COLOR);
    flushHistoryScreen();
}

// Clear screen
void GameViewSDL::clearMainScreen() {
    SDL_RenderClear(mainRenderer);
}

void GameViewSDL::clearHistoryScreen() {
    SDL_RenderClear(historyRenderer);
}

void GameViewSDL::clearScreen(const DrawingWindow dwindow) {
    switch (dwindow) {
        case GameView::DrawingWindow::Main:
            clearMainScreen();
            break;
        case GameView::DrawingWindow::History:
            clearHistoryScreen();
            break;
    }
}

// Flush screen
void GameViewSDL::flushMainScreen() {
    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
    SDL_RenderPresent(mainRenderer);
}

void GameViewSDL::flushHistoryScreen() {
    SDL_SetRenderDrawColor(historyRenderer, 0, 0, 0, 255);
    SDL_RenderPresent(historyRenderer);
}

// draw screen functions

void GameViewSDL::drawTitleScreen(const TitleScreen::Highlight screenHighlight) {
    clearScreen(DrawingWindow::Main);
    
    drawText(DrawingWindow::Main, "Coin Weighting", WIDTH/2, 100, HUGE_FONT_SIZE, MAIN_COLOR);
    drawText(DrawingWindow::Main, "Play", WIDTH/2, HEIGHT/2, DEFAULT_FONT_SIZE, screenHighlight == TitleScreen::Highlight::Play ? HIGHLIGHTED_COLOR : MAIN_COLOR);
    drawText(DrawingWindow::Main, "Instructions", WIDTH/2, HEIGHT/2 + 50, DEFAULT_FONT_SIZE, screenHighlight == TitleScreen::Highlight::Instruction ? HIGHLIGHTED_COLOR : MAIN_COLOR);
    drawText(DrawingWindow::Main, "Credits", WIDTH/2, HEIGHT/2 + 100, DEFAULT_FONT_SIZE, screenHighlight == TitleScreen::Highlight::Credit ? HIGHLIGHTED_COLOR : MAIN_COLOR);
    drawCircle(DrawingWindow::Main, 100, 400, 50, true, GOLD);
    drawCircle(DrawingWindow::Main, 650, 280, 80, true, GOLD);
    drawCircle(DrawingWindow::Main, 450, 550, 30, true, GOLD);
    
    flushMainScreen();
}

void GameViewSDL::drawInstructionScreen() {
    clearScreen(DrawingWindow::Main);
    
    const int x_pos = WIDTH / 2;
    int y_pos = 100;
    const int y_pos_incr = 20;
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
        "Press '0' to undo moving selected coin to any set",
        "Press '1' to move selected coin to the red (left) set.",
        "Press '2' to move selected coin to the blue (right) set.",
        "Press '3' to move selected coin to the green (guess) set."
    });
    displayStrings.emplace_back(std::vector<std::string>{
        "Game Play Page (Computer play):",
        "Press Enter/Return to trigger the computer's move."
    });
    displayStrings.emplace_back(std::vector<std::string>{
        "Game History Page:",
        "Press Enter/Return to go back to the game play page.",
        "Press Left/Right to switch between previous moves."
    });
    
    for (auto pageStrList : displayStrings) {
        for (int i = 0; i < pageStrList.size(); ++i) {
            drawText(DrawingWindow::Main, pageStrList[i], x_pos,
                     y_pos, SMALL_FONT_SIZE, MAIN_COLOR);
            y_pos += y_pos_incr;
        }
        y_pos += y_pos_incr;
    }
    
    drawReturnButton();
    
    flushMainScreen();
}

void GameViewSDL::drawCreditScreen() {
    clearScreen(DrawingWindow::Main);
    
    const int x_pos = WIDTH / 2;
    int y_pos = 70;
    const int y_pos_incr = 25;
    
    drawText(DrawingWindow::Main, "credits...", x_pos,
             y_pos, SMALL_FONT_SIZE, MAIN_COLOR);
    
    drawReturnButton();
    
    flushMainScreen();
}

void GameViewSDL::drawGameOptionScreen(const GameOptionScreen::Highlight screenHighlight,
                          const GameSettings &currSettings) {
    clearScreen(DrawingWindow::Main);
    
    const std::string gameLevelStr = [&currSettings]() -> std::string {
        switch (currSettings.gameLevel()) {
            case GameLevel::Easy:
                return "Easy";
            case GameLevel::Medium:
                return "Medium";
            case GameLevel::Hard:
                return "Hard";
        }
    }();
    
    drawText(DrawingWindow::Main, "Coin Weighting", WIDTH / 2, 100, HUGE_FONT_SIZE, MAIN_COLOR);
    drawText(DrawingWindow::Main, "Number of Coins:", WIDTH / 2 - 80, HEIGHT / 2, DEFAULT_FONT_SIZE, MAIN_COLOR);
    drawText(DrawingWindow::Main, "Level:", WIDTH / 2 - 12, HEIGHT / 2 + 50, DEFAULT_FONT_SIZE, MAIN_COLOR);
    drawText(DrawingWindow::Main, "Mode:", WIDTH / 2 - 12, HEIGHT / 2 + 100, DEFAULT_FONT_SIZE, MAIN_COLOR);
    
    drawText(DrawingWindow::Main, "< " + std::to_string(currSettings.numOfCoins()) + " >",  WIDTH / 2 + 120, HEIGHT / 2,
               DEFAULT_FONT_SIZE, screenHighlight == GameOptionScreen::Highlight::NumOfCoins ? HIGHLIGHTED_COLOR : MAIN_COLOR);
    drawText(DrawingWindow::Main, "< " + gameLevelStr + " >", WIDTH / 2 + 120, HEIGHT / 2 + 50, DEFAULT_FONT_SIZE,
             screenHighlight == GameOptionScreen::Highlight::Level ? HIGHLIGHTED_COLOR : MAIN_COLOR);
    drawText(DrawingWindow::Main, currSettings.isHumanMode() ? "< Human >" : "< Computer >", WIDTH / 2 + 120,
             HEIGHT / 2 + 100, DEFAULT_FONT_SIZE,
             screenHighlight == GameOptionScreen::Highlight::Mode ? HIGHLIGHTED_COLOR : MAIN_COLOR);
    
    flushMainScreen();
}

// input functions

Input GameViewSDL::lastInput() {
    Input::Source source;
    if (event.window.windowID == mainWindowId) {
        source = Input::Source::Main;
    } else if (event.window.windowID == historyWindowId) {
        source = Input::Source::History;
    } else {
        return Input(Input::Source::Main);
    }
    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.repeat) return Input(source);
            switch (event.key.keysym.sym) {
                case SDLK_UP: return Input(source, Input::Arrow::Up);
                case SDLK_LEFT: return Input(source, Input::Arrow::Left);
                case SDLK_RIGHT: return Input(source, Input::Arrow::Right);
                case SDLK_DOWN: return Input(source, Input::Arrow::Down);
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER: return Input(source, '\n');
                case SDLK_0:
                case SDLK_KP_0: return Input(source, '0');
                case SDLK_1:
                case SDLK_KP_1: return Input(source, '1');
                case SDLK_2:
                case SDLK_KP_2: return Input(source, '2');
                case SDLK_3:
                case SDLK_KP_3: return Input(source, '3');
                default: return Input(source);
            }
            break;
        case SDL_QUIT:
            SDL_Quit();
            TTF_Quit();
            return Input(source);
            break;
        default:
            return Input(source);
    }
    return Input(Input::Source::Main);
}

std::vector<Input> GameViewSDL::processInputs() {
    std::vector<Input> inputs;
    while (SDL_PollEvent(&event)) {
        inputs.emplace_back(lastInput());
    }
    return inputs;
}
