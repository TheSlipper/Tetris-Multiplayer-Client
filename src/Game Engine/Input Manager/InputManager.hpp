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

namespace ArktisEngine
{
    
    ////////////////////////////////////////////////////////////
    /// \brief Class that manages game's input
    ///
    ////////////////////////////////////////////////////////////
    class InputManager
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        InputManager() {}
        
        ////////////////////////////////////////////////////////////
        /// \brief Default destructor
        ///
        ////////////////////////////////////////////////////////////
        ~InputManager() {}
        
        ////////////////////////////////////////////////////////////
        /// \brief Checks if a given sprite was clicked
        ///
        /// \param sf::Sprite object object that could be clicked
        ///
        /// \param sf::Mouse::Button button
        ///
        /// \param sf::RenderWindow &window reference to the window
        ///
        ////////////////////////////////////////////////////////////
        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
        
        ////////////////////////////////////////////////////////////
        /// \brief Checks if a given text was clicked
        ///
        /// \param sf::Text object object that could be clicked
        ///
        /// \param sf::Mouse::Button button
        ///
        /// \param sf::RenderWindow &window reference to the window
        ///
        ////////////////////////////////////////////////////////////
        bool IsTextClicked(sf::Text object, sf::Mouse::Button button, sf::RenderWindow &window);
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the position of the mouse in relation to
        ///         the window
        ///
        ////////////////////////////////////////////////////////////
        sf::Vector2i GetMousePosition(sf::RenderWindow &window);
    };
}
