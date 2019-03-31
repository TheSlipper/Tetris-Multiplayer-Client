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
// Definitions
////////////////////////////////////////////////////////////
#define ANIMATION_TIME_INTERVAL .7f

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../Rounded Rectangle Shape/RoundedRectangleShape.hpp"
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>

namespace GameObjects
{
    class InputField : public sf::Drawable
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default InputField constructor
        ///
        /// \param width width of the input field
        ///
        /// \param height height of the input field
        ///
        /// \param xPos x position of the field
        ///
        /// \param yPos y position of the field
        ///
        ////////////////////////////////////////////////////////////
        InputField(sf::Clock &clock, float width=300.0f, float height=50.0f, float xPos=0.0f, float yPos=0.0f);
        
        ////////////////////////////////////////////////////////////
        /// \brief InputField constructor with a specified font
        ///
        /// \param font Font used on the input field's text
        ///
        /// \param width width of the input field
        ///
        /// \param height height of the input field
        ///
        /// \param xPos x position of the field
        ///
        /// \param yPos y position of the field
        ///
        ////////////////////////////////////////////////////////////
        InputField(sf::Font& font, float width=300.0f, float height=50.0f, float xPos=0.0f, float yPos=0.0f);
        
        ////////////////////////////////////////////////////////////
        /// \brief Appends a character to the input content string
        ///
        /// \param character adds this character to the input content string
        ///
        ////////////////////////////////////////////////////////////
        void AppendCharacter(char character);
        
        ////////////////////////////////////////////////////////////
        /// \brief Removes the last character (includes the '|' character)
        ///
        ////////////////////////////////////////////////////////////
        void RemoveLastChar();
        
        ////////////////////////////////////////////////////////////
        /// \brief Removes the last character before the '|'
        ///
        ////////////////////////////////////////////////////////////
        void RemoveLastContentChar();
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the position of the object on the canvas
        ///
        /// \param x the x position of the object
        ///
        /// \param y the y position of the object
        ///
        ////////////////////////////////////////////////////////////
        void SetPosition(float x, float y);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the font of the text in the input field
        ///
        /// \param font font that is to be used for the text
        ///
        ////////////////////////////////////////////////////////////
        void SetFont(sf::Font& font);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the focus of the input object
        ///
        /// \param focus focus of the object
        ///
        ////////////////////////////////////////////////////////////
        void SetFocus(bool focus);
        
        ////////////////////////////////////////////////////////////
        /// \brief Switches the status of the focus either from true to
        ///         false or the other way around
        ///
        ////////////////////////////////////////////////////////////
        void SwitchFocusState();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the position of the object
        ///
        /// \return sf::Vector2f with data of the position
        ///
        ////////////////////////////////////////////////////////////
        sf::Vector2f GetPosition();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns global bounds of the input field
        ///
        /// \return sf::FloatRect with global bounds
        ///
        ////////////////////////////////////////////////////////////
        sf::FloatRect GetGlobalBounds();
        
        ////////////////////////////////////////////////////////////
        /// \brief Used to determine if the input is focused on
        ///
        /// \return bool is it focused on
        ///
        ////////////////////////////////////////////////////////////
        bool HasFocus();
        
        ////////////////////////////////////////////////////////////
        /// \brief Procecess the animation of the indicator at the
        ///         end of the line if focused
        ///
        ////////////////////////////////////////////////////////////
        void ProcessFocusAnimation();
        
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
        /// \brief Centers the text on the vertical axis of the input
        ///         rounded shape
        ///
        ////////////////////////////////////////////////////////////
        void centerTextVert();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        const sf::Color INPUT_OUTLINE_COL; ///< Color of the input field's outline
        
        const sf::Color INPUT_INNER_COL; ///< Color of the input field's inner rectangle
        
        bool focus = false; ///< Flag of input field's focus
        
        sf::RoundedRectangleShape rrs; ///< Shape of the input field
        
        sf::Clock *clock; ///< Pointer to the game's clock
        
        float timeFocused; ///< Time when the object was focused
        
        sf::String inputContent = ""; ///< Content of the input text
        
        sf::Text inputText; ///< Drawable text with the content of input content
    };
}
