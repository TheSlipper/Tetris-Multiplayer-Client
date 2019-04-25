////////////////////////////////////////////////////////////
/// Tetris Multiplayer Game - PvP Tetris Experience
/// Copyright (C) 2019 Kornel Domeradzki
///
/// This program is free software; you can redistribute it and/or
/// modify it under the terms of the GNU General Public License
/// as published by the Free Software Foundation; either version 2
/// of the License, or (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program; if not, write to the Free Software
/// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////
#define GRID_WIDTH 10
#define GRID_HEIGHT 20

// TODO: Scalability
#define X_OFFSET 210.f
#define Y_OFFSET 126.f

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "../State/State.hpp"
#include "../../Game Engine/GameData/GameData.hpp"
#include "../../Definitions/TEXTURE_DEFINITIONS.h"
#include "../Login State/LoginState.hpp"
#include "../../Game Engine/Misc Utils/MiscUtils.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    /// \brief Splash State
    ///
    ////////////////////////////////////////////////////////////
    class GameState : public State
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param GameDataRef data pointer to the game's crucial data
        ///
        ////////////////////////////////////////////////////////////
        GameState(ArktisEngine::GameDataRef data);
        
        ////////////////////////////////////////////////////////////
        /// \brief Initialization of the state
        ///
        ////////////////////////////////////////////////////////////
        void Init();
        
        ////////////////////////////////////////////////////////////
        /// \brief Handles scene-specific user input
        ///
        ////////////////////////////////////////////////////////////
        void HandleInput();
        
        ////////////////////////////////////////////////////////////
        /// \brief Updates the scene (call the animation or physics
        ///         methods here)
        ///
        ////////////////////////////////////////////////////////////
        void Update(float dt);
        
        ////////////////////////////////////////////////////////////
        /// \brief Draws to the screen
        ///
        ////////////////////////////////////////////////////////////
        void Draw(float dt);
        
    private:
        void move();
        
        void rotation();
        
        void tick();
        
        bool check();
        
        void checkLines();
        
        bool isItGameOver();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        const int M = GRID_HEIGHT;
        const int N = GRID_WIDTH;
        
        int field[GRID_HEIGHT][GRID_WIDTH] = {0};
        
        struct Point
        {
            int x = 0, y = 0;
        } a[4], b[4];
        
        int figures[7][4] = ///< Figures available in Tetris
        {
            1, 3, 5, 7,     // I
            2, 4, 5, 7,     // Z
            3, 5, 4, 6,     // S
            3, 5, 4, 7,     // T
            2, 3, 5, 7,     // L
            3, 5, 7, 6,     // J
            2, 3, 4, 5      // O
        };
        
        sf::Sprite s, background;
        
        int dx = 0, colorNum = 1;
        
        float timer = 0.f, delay = .7f, tileWidth, tileHeight;
        
        bool rotate = 0;
        
        sf::Clock gameClock;
        
        ArktisEngine::GameDataRef _data; ///< Pointer to game's crucial data
    };
}
