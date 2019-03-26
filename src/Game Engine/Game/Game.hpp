////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
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
        void LoadGamesSettings(std::string settingsFilePath);
        
    private:
        ////////////////////////////////////////////////////////////
        /// \brief Runs the game
        ///
        ////////////////////////////////////////////////////////////
        void Run();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        // TODO: Confirm the assumption that it's delta time (forgot already lol)
        const float dt = 1.0f / 60.0f;  ///< Delta time
        
        // TODO: Is this clock redundant due to the clock in GameDataRef?
        sf::Clock _clock;   ///< Game's clock
        
        GameDataRef _data = std::make_shared<GameData>();   ///< Pointer to the GameData
    };
}
