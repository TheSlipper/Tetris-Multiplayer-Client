////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki and Kamil Kwaśnik.
// Copyright © 2018 Kornel Domeradzki and Kamil Kwaśnik. All rights reserved.
////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../State/State.hpp"
#include "../../Game Engine/GameData/GameData.hpp"
#include "../../DEFINITIONS.h"

namespace States
{
    ////////////////////////////////////////////////////////////
    /// \brief Splash State
    ///
    ////////////////////////////////////////////////////////////
    class SplashState : public State
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param GameDataRef data pointer to the game's crucial data
        ///
        ////////////////////////////////////////////////////////////
        SplashState(ArktisEngine::GameDataRef data);
        
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
        // TODO: Comments
        // sf::Clock, sf::Text - Change to unique pointers
        sf::Clock _clock;
        
        sf::Text logoText;
        
        sf::Text pressToContinue;
        
        sf::SoundBuffer soundBuffer;
        
        std::unique_ptr<sf::Sound> _clickSound;
        
        ArktisEngine::GameDataRef _data;
        
        float previousTimeStamp;
        
        bool previousWasWhite;
        
        bool wasItClicked;
    };
}
