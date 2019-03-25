#pragma once

#include "../State Machine/StateMachine.hpp"
#include "../Asset Manager/AssetManager.hpp"
#include "../Input Manager/InputManager.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    /// \brief Contains all of the important game settings
    ///
    ////////////////////////////////////////////////////////////
    struct GameSettings
    {
        unsigned int width, height;
        unsigned int master_vol, sfx_vol, music_vol;
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
    };
    
    typedef std::shared_ptr<GameData> GameDataRef;  ///< Definition of shared pointer to the GameData struct
}
