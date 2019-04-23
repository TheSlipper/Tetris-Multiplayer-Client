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
#include <memory>
#include "../State/State.hpp"
#include "../../Game Engine/GameData/GameData.hpp"
#include "../../Definitions/METADATA_DEFINITIONS.h"
#include "../../Definitions/FONT_DEFINITIONS.h"
#include "../../Definitions/TEXTURE_DEFINITIONS.h"
#include "../../Game Objects/Button/Button.hpp"
#include "../../Game Objects/Input Field/InputField.hpp"
#include "../Home Screen State/HomeScreenState.hpp"

namespace States
{
    class LoginState : public State
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param GameDataRef data pointer to the game's crucial data
        ///
        ////////////////////////////////////////////////////////////
        LoginState(ArktisEngine::GameDataRef data);
        
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
        /// \brief Centers and positions the logo sprite
        ///
        ////////////////////////////////////////////////////////////
        void centerAndPositionLogo();
        
        ////////////////////////////////////////////////////////////
        /// \brief Centers the labels on the horizontal axis of the canvas
        ///         and positions the labels
        ///
        ////////////////////////////////////////////////////////////
        void centerAndPositionLabels();
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets up the login and password labels
        ///
        ////////////////////////////////////////////////////////////
        void setUpLabels();
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets up the game logo
        ///
        ////////////////////////////////////////////////////////////
        void setUpGameLogo();
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets up the login and password inputs
        ///
        ////////////////////////////////////////////////////////////
        void setUpForm();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        const sf::Color BG_COLOR;
        
        sf::Sprite logo; ///< Logo of the game
        
        sf::Text loginLabel; ///< Login label
        
        sf::Text passwdLabel; ///< Password label
        
        std::string passwd = "";
        
        std::unique_ptr<GameObjects::InputField> _loginInput; ///< Login input field
        
        std::unique_ptr<GameObjects::InputField> _passwordInput; ///< Password input field
        
        std::unique_ptr<GameObjects::Button> _loginButton;
        
        ArktisEngine::GameDataRef _data; ///< Pointer to game's crucial data
    };
}
