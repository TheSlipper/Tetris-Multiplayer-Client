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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "MessageBox.hpp"

namespace GameObjects
{
    ////////////////////////////////////////////////////////////
    MessageBox::MessageBox(MessageBoxType type, sf::Font &font, std::string headerText, std::string contentText, float x, float y, float width, float height)
    {
        float xPadding = width * 5.f / 100.f, yPadding = height * 5.f / 100.f;
        
        this->headerText.setString(headerText);
        this->headerText.setFont(font);
        this->headerText.setFillColor(sf::Color::White);
        this->headerText.setPosition(x + xPadding, y + yPadding);
        
        this->xButton.setString("[X]");
        this->xButton.setFont(font);
        this->xButton.setFillColor(sf::Color::White);
        this->xButton.setPosition(x + (width - xButton.getGlobalBounds().width) - xPadding, y + yPadding);
        
        this->contentText.setString(contentText);
        this->contentText.setFont(font);
        this->contentText.setFillColor(sf::Color::White);
        this->contentText.setPosition(this->headerText.getLocalBounds().top, y + this->headerText.getLocalBounds().height + yPadding * 3);
        
        this->messageBoxShape.setPosition(x, y);
        this->messageBoxShape.setSize(sf::Vector2f(width, height));
        this->messageBoxShape.setFillColor(sf::Color::Black);
        
        this->_button = std::make_unique<Button>(font, "ok", 0.f, 0.f, width/2.f, height / 2.f); // TOOD: Center stuff and other parameters
        this->_button->SetTextFillColor(sf::Color::Black);
        this->_button->SetRrsFillColor(sf::Color::White);
        ArktisEngine::CenterHorizontallyInArea(*this->_button, width, this->contentText.getGlobalBounds().top + yPadding);
    }
    
    ////////////////////////////////////////////////////////////
    void MessageBox::Hide()
    {
        this->hidden = true;
    }
    
    ////////////////////////////////////////////////////////////
    void MessageBox::PopUp()
    {
        this->hidden = false;
    }
    
    ////////////////////////////////////////////////////////////
    bool MessageBox::IsHidden()
    {
        return this->hidden;
    }
    
    ////////////////////////////////////////////////////////////
    sf::FloatRect MessageBox::GetXBounds()
    {
        return this->xButton.getGlobalBounds();
    }
    
    ////////////////////////////////////////////////////////////
    void MessageBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (this->hidden)
            return;
        target.draw(this->messageBoxShape);
        target.draw(this->headerText);
        target.draw(this->xButton);
        target.draw(this->contentText);
        target.draw(*this->_button);
    }
    
    ////////////////////////////////////////////////////////////
    void MessageBox::wrapText()
    {
        
    }
}
