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
// Headers
////////////////////////////////////////////////////////////
#include "../State/State.hpp"
#include "../../Game Engine/GameData/GameData.hpp"
#include "../../Definitions/FONT_DEFINITIONS.h"
#include "../Game State/GameState.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    /// \brief Loading Screen State
    ///
    ////////////////////////////////////////////////////////////
    class LoadingScreenState : public State
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param GameDataRef data pointer to the game's crucial data
        ///
        ////////////////////////////////////////////////////////////
        LoadingScreenState(ArktisEngine::GameDataRef data);
        
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
        /// \brief Centers the status text on the screen
        ///
        ////////////////////////////////////////////////////////////
        void centerText();

        ////////////////////////////////////////////////////////////
        /// \brief Sends a matchmaking request to the server
        ///
        ////////////////////////////////////////////////////////////
        void sendMatchmakingReq();

        ////////////////////////////////////////////////////////////
        /// \brief Gets data on the opponent
        ///
        ////////////////////////////////////////////////////////////
		ArktisEngine::UserData getOpponentData();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::Text loadingScreenText; ///< Text with the matchmaking status
        
        std::string serverResponse; ///< String with server response
        
        bool firstDraw = true; ///< First draw flag
        
        ArktisEngine::GameDataRef _data; ///< Pointer to game's crucial data
    };
}
