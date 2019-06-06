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
#define X_OFFSET 215.f
#define Y_OFFSET 167.f

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <functional>
#include "../State/State.hpp"
#include "../../Game Engine/GameData/GameData.hpp"
#include "../../Definitions/TEXTURE_DEFINITIONS.h"
#include "../../Definitions/AUDIO_DEFINITIONS.h"
#include "../Game Over State/GameOverState.hpp"
#include "../../Game Engine/Misc Utils/MiscUtils.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    /// \brief Game State
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
		/// \brief Default constructor
		///
		/// \param opponentData data of the opponent
		///
		/// \param data pointer to the game's crucial data
		///
		////////////////////////////////////////////////////////////
		GameState(ArktisEngine::UserData opponentData, ArktisEngine::GameDataRef data);
        
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
        ////////////////////////////////////////////////////////////
        /// \brief Sets up all of the game labels
        ///
        ////////////////////////////////////////////////////////////
        void setUpLabels();
        
        ////////////////////////////////////////////////////////////
        /// \brief Positions all of the label contents in a given order
        ///         specified by the implementation of this function
        ///
        /// \param rowHeader header/name of the row
        ///
        /// \param p1 content of first player's label
        ///
        /// \param p2 content of second player's label
        ///
        /// \param topMrgnPrct specifies top margin of the row in percents
        ///
        /// \param rowStr std::string content of the row header
        ///
        /// \param p1String std::string content of the p1 label
        ///
        /// \param p2String std::string content of the p2 label
        ///
        ////////////////////////////////////////////////////////////
        void positionRowOfLabels(sf::Text &rowHeader, sf::Text &p1, sf::Text &p2, const float topMrgnPrct, const std::string rowStr, const std::string p1String, const std::string p2String);
        
        ////////////////////////////////////////////////////////////
        /// \brief Draws all of the labels to the screen
        ///
        ////////////////////////////////////////////////////////////
        void drawLabels();

        ////////////////////////////////////////////////////////////
        /// \brief Draws the game fields to the screen
        ///
        ////////////////////////////////////////////////////////////
		void drawFields();
        
        ////////////////////////////////////////////////////////////
        /// \brief Moves the falling tetromino
        ///
        ////////////////////////////////////////////////////////////
        void move();
        
        ////////////////////////////////////////////////////////////
        /// \brief Rotates the falling tetromino
        ///
        ////////////////////////////////////////////////////////////
        void rotation();
        
        ////////////////////////////////////////////////////////////
        /// \brief Performs all of the actions that should be handled
        ///         on a "tick"
        ///
        ////////////////////////////////////////////////////////////
        void tick();
        
        ////////////////////////////////////////////////////////////
        /// \brief Checks if the falling tetromino have reached the point
        ///         where they should stop falling
        ///
        ////////////////////////////////////////////////////////////
        bool check();
        
        ////////////////////////////////////////////////////////////
        /// \brief Checks if there is a full line and if there is one
        ///         it deletes it
        ///
        ////////////////////////////////////////////////////////////
        void checkLines();
        
        ////////////////////////////////////////////////////////////
        /// \brief Checks if the game is over
        ///
        ////////////////////////////////////////////////////////////
        bool isItGameOver();
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the time spent in-game in std::string
        ///
        ////////////////////////////////////////////////////////////
        const std::string timeSpent();

        ////////////////////////////////////////////////////////////
        /// \brief Networking data thread function
        ///
        ////////////////////////////////////////////////////////////
		void handleNetworking();

        ////////////////////////////////////////////////////////////
        /// \brief Sends the player's field data
        ///
        /// \param matchId Id of the match
        ///
        ////////////////////////////////////////////////////////////
		void sendFieldData(const int &matchId);

        ////////////////////////////////////////////////////////////
        /// \brief Receives the opponent's field data
        ///
        ////////////////////////////////////////////////////////////
		void receiveFieldData();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
		ArktisEngine::UserData opponentData;

        const int M = GRID_HEIGHT;
        const int N = GRID_WIDTH;
        
        int field[GRID_HEIGHT][GRID_WIDTH] = {0};
		
		int opponentField[GRID_HEIGHT][GRID_WIDTH] = {0};
        
		bool p1LostGame = false, p2LostGame = false;
        
        struct Point
        {
            int x = 0, y = 0;
        } a[4], b[4], opponentA[4], opponentB[4];
        
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
        
        sf::Sprite s, background, frame;
        
        sf::Text p1UserName, p2UserName;
        
        sf::Text p1Elo, p2Elo, eloText;
        
        sf::Text p1Pts, p2Pts, ptsText;
        
        sf::Text p1Lines, p2Lines, linesText;
        
        sf::Text p1Delay, p2Delay, delayText;
        
        sf::Text timeText;

		sf::Text p1GameOver, p2GameOver;
        
        sf::Music backgroundMusic;
        
        int directionX = 0, colorNum = 1;
        
        float baseDelay = .7f;
        
        float timer = 0.f, delay = baseDelay, tileWidth, tileHeight;
        
        bool rotate = 0;
        
        sf::Clock gameClock, timeSpentClock;

		sf::Thread networkingThread;

		bool sending = true;

		bool abortThread = false;
        
        ArktisEngine::GameDataRef _data; ///< Pointer to game's crucial data
    };
}
