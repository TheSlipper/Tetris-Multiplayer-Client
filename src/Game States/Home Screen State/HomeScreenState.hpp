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
#include <SFML/Graphics.hpp>
#include <memory>
#include "../../Definitions/TEXTURE_DEFINITIONS.h"
#include "../../Definitions/FONT_DEFINITIONS.h"
#include "../../Game Engine/GameData/GameData.hpp"
#include "../../Game Objects/Button/Button.hpp"
#include "../../Game Engine/Misc Utils/MiscUtils.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    /// \brief Splash State
    ///
    ////////////////////////////////////////////////////////////
    class HomeScreenState : public State
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param GameDataRef data pointer to the game's crucial data
        ///
        ////////////////////////////////////////////////////////////
        HomeScreenState(ArktisEngine::GameDataRef data);

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
        /// \brief Sets up the play buttons
        ///
        ////////////////////////////////////////////////////////////
        void setUpPlayButtons();

        ////////////////////////////////////////////////////////////
        /// \brief Sets up the account HUD
        ///
        ////////////////////////////////////////////////////////////
        void setUpAccHUD();

        ////////////////////////////////////////////////////////////
        /// \brief Sets up the news section
        ///
        ////////////////////////////////////////////////////////////
        void setUpNewsSection();

        ////////////////////////////////////////////////////////////
        /// \brief Loads the avatar textures to the asset manager
        ///
        ////////////////////////////////////////////////////////////
        void loadAvatarTextures();

        ////////////////////////////////////////////////////////////
        /// \brief Loads articles for the game from the database
        ///
        ////////////////////////////////////////////////////////////
        void loadArticles();

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::RoundedRectangleShape newsOutline; ///< Outline of the news section

        std::vector<sf::Text> articleHeaders; ///< Headers of the articles

        std::vector<sf::Text> articleContent; ///< Content of the articles

        std::unique_ptr<GameObjects::Button> _playNormal; ///< Play normal game box

        std::unique_ptr<GameObjects::Button> _playRanked; ///< Play ranked game box

        std::unique_ptr<GameObjects::Button> _nicknameBox; ///< User's nickname box

        std::unique_ptr<GameObjects::Button> _blocksBox; ///< User's block points box

        sf::Sprite gameLogo; ///< Game's logo

        sf::Sprite avatar; ///< User avatar

        sf::Sprite bgStylizedImage; ///< Stylized background image

        ArktisEngine::GameDataRef _data; ///< Pointer to game's crucial data
    };
}
