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
#include "../Rounded Rectangle Shape/RoundedRectangleShape.hpp"
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>

namespace GameObjects
{
    class Button : public sf::Drawable
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param label content of the button's label
        ///
        /// \param x x coordinate of the object
        ///
        /// \param y y coordinate of the object
        ///
        /// \param width width of the button
        ///
        /// \param height height of the button
        ///
        ////////////////////////////////////////////////////////////
        Button(std::string label, float x=0.f, float y=0.f, float width=300.f, float height=50.f);
        
        ////////////////////////////////////////////////////////////
        /// \brief Button constructor
        ///
        /// \param font font to be used on the label
        ///
        /// \param label content of the button's label
        ///
        /// \param x x coordinate of the object
        ///
        /// \param y y coordinate of the object
        ///
        /// \param width width of the button
        ///
        /// \param height height of the button
        ///
        ////////////////////////////////////////////////////////////
        Button(sf::Font &font, std::string label, float x=0.f, float y=0.f, float width=300.f, float height=50.f);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the font for the label
        ///
        /// \param font
        ///
        ////////////////////////////////////////////////////////////
        void SetFont(sf::Font &font);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the rounded rectangle shape's fill color
        ///
        /// \param clr color used on the rounded rectangle shape
        ///
        ////////////////////////////////////////////////////////////
        void SetRrsFillColor(sf::Color clr);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the rounded rectangle shape's outline color
        ///
        /// \param clr color used on the rounded rectangle shape's
        ///         outline
        ///
        ////////////////////////////////////////////////////////////
        void SetRrsOutlineColor(sf::Color clr);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the fill color of the text
        ///
        /// \param clr color used on the text
        ///
        ////////////////////////////////////////////////////////////
        void SetTextFillColor(sf::Color clr);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the outline color of the text
        ///
        /// \param clr color used on the outline of the text
        ///
        ////////////////////////////////////////////////////////////
        void SetTextOutlineColor(sf::Color clr);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the position of the object
        ///
        /// \param vect new coordinates of the object
        ///
        ////////////////////////////////////////////////////////////
        void SetPosition(sf::Vector2f vect);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the position of the object
        ///
        /// \param x new x coordinate of the object
        ///
        /// \param y new y coordinate of the object
        ///
        ////////////////////////////////////////////////////////////
        void SetPosition(float x, float y);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the dimensions of the object
        ///
        /// \brief vect new dimensions of the object
        ///
        ////////////////////////////////////////////////////////////
        void SetSize(sf::Vector2f vect);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the origin of the object
        ///
        /// \param x x coordinate of the origin
        ///
        /// \param y y coordinate of the origin
        ///
        ////////////////////////////////////////////////////////////
        void SetOrigin(float x, float y);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the origin of the object
        ///
        /// \param vect vector with x and y coordinates of the origin
        ///
        ////////////////////////////////////////////////////////////
        void SetOrigin(sf::Vector2f vect);
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the global bounds of the object
        ///
        /// \return sf::FloatRect global bounds
        ///
        ////////////////////////////////////////////////////////////
        sf::FloatRect GetGlobalBounds();
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the position of the object
        ///
        /// \return sf::Vector2f position
        ///
        ////////////////////////////////////////////////////////////
        sf::Vector2f GetPosition();
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the position of the center of the object
        ///
        /// \return sf::Vector2f center position
        ///
        ////////////////////////////////////////////////////////////
        sf::Vector2f GetCenterCoord();
        
    private:
        ////////////////////////////////////////////////////////////
        /// \brief Defines how an instance of this class should be drawn
        ///
        /// \param target target on which the object is going to be drawn
        ///
        /// \param states
        ///
        ////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
        ////////////////////////////////////////////////////////////
        /// \brief Centers the text vertically
        ///
        ////////////////////////////////////////////////////////////
        void centerTextVert();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::Text buttonLabel; ///< Label of the button
        
        sf::RoundedRectangleShape rrs; ///< Outline of the button
    };
}
