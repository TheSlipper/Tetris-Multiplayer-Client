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
#include "../Button/Button.hpp"
#include "../../Game Engine/Misc Utils/MiscUtils.hpp"

enum MessageBoxType {MB_OK, MB_HELP, MB_ERROR};
namespace GameObjects
{
    class MessageBox : public sf::Drawable
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default messagebox constructor
        ///
        /// \param type Type of the message box (Defines the style of
        ///         the messagebox
        ///
        /// \param headerText content of the message box's header
        ///
        /// \param contentText content of the message box
        ///
        /// \param x x position on the canvas of the message box
        ///
        /// \param y y position on the canvas of the message box
        ///
        /// \param width width of the message box
        ///
        /// \param height height of the message box
        ///
        ////////////////////////////////////////////////////////////
        MessageBox(MessageBoxType type, sf::Font &font, std::string headerText, std::string contentText, float x = 0.f, float y = 0.f, float width = 300.f, float height = 100.f);
        
        
        ////////////////////////////////////////////////////////////
        /// \brief Hides the message box
        ///
        ////////////////////////////////////////////////////////////
        void Hide();
        
        ////////////////////////////////////////////////////////////
        /// \brief Displays the message box
        ///
        ////////////////////////////////////////////////////////////
        void PopUp();
        
        ////////////////////////////////////////////////////////////
        /// \brief Checks if the object is hidden
        ///
        /// \returns true if object is hidden
        ///
        ////////////////////////////////////////////////////////////
        bool IsHidden();
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the X bounds
        ///
        /// \returns true if object is hidden
        ///
        ////////////////////////////////////////////////////////////
        sf::FloatRect GetXBounds();
        
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
        /// \brief Wraps the line into multiple lines to prevent
        ///         leaving the boundaries of the rectangle shape
        ///
        ////////////////////////////////////////////////////////////
        void wrapText();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        bool hidden = true;
        
        sf::RectangleShape messageBoxShape;
        
        sf::Text headerText, contentText;
        
//        const static sf::Text xButton;
        sf::Text xButton;
        
        std::unique_ptr<Button> _button;
    };
}
