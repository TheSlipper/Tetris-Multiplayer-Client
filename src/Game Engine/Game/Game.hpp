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
#include <fstream>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "../GameData/GameData.hpp"
#include "../../Definitions/METADATA_DEFINITIONS.h"
#include "../../Game States/Splash State/SplashState.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    /// \brief The whole game runs inside of this class
    ///
    ////////////////////////////////////////////////////////////
    class Game
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param std::string title of the window
        ///
        ////////////////////////////////////////////////////////////
        Game();
        
        ////////////////////////////////////////////////////////////
        /// \brief Loads the settings from the given file
        ///
        /// \param std::string settingsFilePath path to the file
        ///
        ////////////////////////////////////////////////////////////
        void LoadGamesSettings();
        
    private:
        ////////////////////////////////////////////////////////////
        /// \brief Runs the game
        ///
        ////////////////////////////////////////////////////////////
        void Run();
        
        void loadIcon();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        const float dt = 1.0f / 60.0f;  ///< Delta time
        
		const char *settingsFilePath = "Resources/settings.conf";

        sf::Clock _clock;   ///< Game's clock
        
        GameDataRef _data = std::make_shared<GameData>();   ///< Pointer to the GameData
    };
}
