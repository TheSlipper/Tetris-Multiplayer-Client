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
#include "../State Machine/StateMachine.hpp"
#include "../Asset Manager/AssetManager.hpp"
#include "../Input Manager/InputManager.hpp"
#include "../Messaging Manager/MessagingManager.hpp"
#include <SFML/Network.hpp>
#include <boost/tokenizer.hpp>

namespace ArktisEngine
{
    struct UserData
    {
        int elo, privilegeGroup, unrankedWins, unrankedLosses, rankedWins, rankedLosses;
        long tetrominoPoints, timePlayed;
        std::string username, password;
		int matchId;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Contains all of the important game settings
    ///
    ////////////////////////////////////////////////////////////
    struct GameSettings
    {
        float width, height;
        float master_vol, sfx_vol, music_vol;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Contains the game essentials
    ///
    ////////////////////////////////////////////////////////////
    struct GameData
    {
        StateMachine machine;
        sf::RenderWindow window;
        sf::Clock gameClock;
        AssetManager assets;
        InputManager input;
        GameSettings settings;
        MessagingManager messaging;
        UserData userData;
    };
    
    typedef std::shared_ptr<GameData> GameDataRef;  ///< Definition of shared pointer to the GameData struct
    
    typedef boost::tokenizer<boost::char_separator<char>> StringTokenizer; ///< Definition of a java-style tokenizer
}
