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
#include <sstream>
#include "../GameData/GameData.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    /// \brief Scales the sprite to the given width and height
    ///
    /// \param spr sprite
    ///
    /// \param width new width of the sprite
    ///
    /// \param height new height of the sprite
    ///
    ////////////////////////////////////////////////////////////
    void ScaleSprToDims(sf::Sprite& spr, float &width, float &height);
    
    ////////////////////////////////////////////////////////////
    /// \brief Scales the sprite to the given width and height
    ///
    /// \param spr sprite
    ///
    /// \param vect vector with dimensions
    ///
    ////////////////////////////////////////////////////////////
    void ScaleSprToDims(sf::Sprite& spr, sf::Vector2f& vect);
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the position of an object with the given
    ///         percent values
    ///
    /// \param verticalPercent percentage of how much an object
    ///         should be moved down on the canvas
    ///
    /// \param horizontalPercent percentage of how much an object
    ///         should be moved to the right on the canvas
    ///
    /// \param settings game settings
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f GetPosRelToScreenByPrct(float verticalPercent, float horizontalPercent, GameSettings &settings);
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the y position of an object with the given
    ///         percent value
    ///
    /// \param yPerc position of the object in percents
    ///
    /// \param settings game settings
    ///
    /// \return y position of the object
    ///
    ////////////////////////////////////////////////////////////
    float GetYPosRelToScreenByPrct(float yPerc, GameSettings &settings);
    
    ////////////////////////////////////////////////////////////
    /// \brief Gets the x position of an object with the given
    ///         percent value
    ///
    /// \param xPerc position of the object in percents
    ///
    /// \param settings game settings
    ///
    /// \return x position of the object
    ///
    ////////////////////////////////////////////////////////////
    float GetXPosRelToScreenByPrct(float xPerc, GameSettings &settings);
    
    ////////////////////////////////////////////////////////////
    /// \brief Centers horizontally the given text on the screen and moves it on the y axis by the given pixel amount.
    ///
    /// \param text target text
    ///
    /// \param settings game settings
    ///
    /// \param y defines how much the text should be moved down vertically
    ///
    ////////////////////////////////////////////////////////////
    void CenterHorizontally(sf::Text &text, GameSettings &settings, float y = 0.f);
    
    ////////////////////////////////////////////////////////////
    /// \brief Centers horizontally the given text in a rectangle area on
    ///        the screen and moves it on the y axis by the given pixel amount.
    ///
    /// \param text target text
    ///
    /// \param areaWidth width of the rectangle area
    ///
    /// \param y defines how much the text should be moved down vertically
    ///
    ////////////////////////////////////////////////////////////
    void CenterHorizontallyInArea(sf::Text &text, float areaWidth, float y);
    
    ////////////////////////////////////////////////////////////
    /// \brief Centers horizontally the given button in a rectangle area on
    ///        the screen and moves it on the y axis by the given pixel amount.
    ///
    /// \param button target button
    ///
    /// \param areaWidth width of the rectangle area
    ///
    /// \param y defines how much the text should be moved down vertically
    ///
    ////////////////////////////////////////////////////////////
    void CenterHorizontallyInArea(GameObjects::Button &button, float areaWidth, float y);
    
    ////////////////////////////////////////////////////////////
    /// \brief Converts a floating point value to a string and sets
    ///         takes only given amount of numbers after the '.' into consideration
    ///
    /// \param a_value the floating point variable
    ///
    /// \param n amount of characters after the '.'
    ///
    /// \return formatted floating point number in std::string
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    std::string to_string_with_precision(const T a_value, const int n = 6)
    {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << a_value;
        return out.str();
    }
}
