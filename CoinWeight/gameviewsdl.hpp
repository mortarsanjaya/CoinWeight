//
//  gameviewsdl.hpp
//  CoinWeight
//
//  Created by Jamie Sebastian on 15/03/20.
//  Copyright © 2020 -. All rights reserved.
//

#ifndef gameviewsdl_hpp
#define gameviewsdl_hpp

#include <string>
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "input.hpp"
#include "gameview.hpp"

class GameViewSDL : public GameView {
    SDL_Window *mainWindow;
    Uint32 mainWindowId;
    SDL_Renderer *mainRenderer;
    
    SDL_Window *historyWindow;
    Uint32 historyWindowId;
    SDL_Renderer *historyRenderer;
    
    SDL_Surface *surface;
    SDL_Event event;
    
    TTF_Font *smallFont, *defaultFont, *hugeFont;
    
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 640;
    static constexpr int SMALL_FONT_SIZE = 14;
    static constexpr int DEFAULT_FONT_SIZE = 28;
    static constexpr int HUGE_FONT_SIZE = 60;
    static constexpr int coinRadius = 15;
    static constexpr int coinDist = 50;
    static constexpr int coin0XPos = 175;
    static constexpr int coin0YPos = 200;
    static constexpr int coinsPerRow = 10;
    static constexpr SDL_Color MAIN_COLOR = {255, 255, 255};
    static constexpr SDL_Color HIGHLIGHTED_COLOR = {0, 221, 255};
    static constexpr SDL_Color GOLD = {255, 204, 0};
    static constexpr SDL_Color RED = {255, 0, 0};
    static constexpr SDL_Color BLUE = {0, 0, 255};
    static constexpr SDL_Color GREEN = {0, 225, 0};
    static constexpr SDL_Color BLACK = {0, 0, 0};
    
    void drawText(DrawingWindow window, std::string text, int x, int y, int fontSize, SDL_Color color, bool boxed = false);
    void drawCircle(DrawingWindow window, int x, int y, int r, bool fill, SDL_Color color);
    void drawRectangle(DrawingWindow window, int x, int y, int width, int height, bool fill, SDL_Color color);
    void drawButton(DrawingWindow window, std::string text, int x, int y, int fontSize, SDL_Color color);
    void drawScale(DrawingWindow window, int tilt);
    
    // Get corresponding renderer from window
    SDL_Renderer *appropriateRenderer(DrawingWindow window) const;
    
    // Draw weigh result text
    const std::string numOfWeighsText(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) const;
    void drawWeighResultText(const DrawingWindow window, const WeighResult weighResult) override;
    
    // Draw coin
    const SDL_Color coinColor(CoinGroup coinState) const;
    void drawCoin(DrawingWindow window, CoinGroup coinState, size_t coinIndex) override;
    
    // Draw return button
    void drawReturnButton() override;
    
    // Game Play Human screen
    void drawGamePlayHumanHighlight(const GamePlayHumanScreen::ScreenHighlight screenHighlight, const size_t coinHighlight) override;
    void drawGamePlayNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) override;
    
    // Game Over screen
    void drawGameOverEndMessage(const GuessResult guessResult) override;
    void drawGameOverNumOfWeighs(const size_t numOfWeighsLeft, const size_t numOfWeighsMax) override;
    
    // History screen
    void drawHistoryIndexText(const size_t index, const size_t numOfWeighs) override;
    void drawEmptyHistoryScreen() override;
    
    // Clear screen
    void clearMainScreen();
    void clearHistoryScreen();
    void clearScreen(const DrawingWindow dwindow) override;
    
    // Flush screen
    void flushMainScreen();
    void flushHistoryScreen();
    
public:
    GameViewSDL();
    // Main drawing functions
    void drawTitleScreen(const TitleScreen::Highlight screenHighlight) override;
    void drawInstructionScreen() override;
    void drawCreditScreen() override;
    void drawGameOptionScreen(const GameOptionScreen::Highlight screenHighlight,
                              const GameSettings &currSettings) override;
    
    Input lastInput() override;
    std::vector<Input> processInputs() override;
};

#endif /* gameviewsdl_hpp */
