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
#include "InputField.hpp"

namespace GameObjects
{
    ////////////////////////////////////////////////////////////
    InputField::InputField(sf::Clock &clock, float width, float height, float xPos, float yPos)
    : INPUT_OUTLINE_COL(sf::Color(0, 0, 0)),
    INPUT_INNER_COL(sf::Color(0, 0, 0))
    {
        this->clock = &clock;
        this->rrs.setSize(sf::Vector2f(width, height));
        this->rrs.setOutlineColor(this->INPUT_OUTLINE_COL);
        this->rrs.setFillColor(this->INPUT_INNER_COL);
        this->rrs.setCornerPointCount(4);
        this->rrs.setOutlineThickness(2.0f);
        this->inputText.setFillColor(sf::Color::White);
        this->inputText.setString(this->inputContent);
        this->inputText.setCharacterSize(9.0f * this->rrs.getGlobalBounds().width / 100.0f);
        this->SetPosition(xPos, yPos);
    }
    
    ////////////////////////////////////////////////////////////
    InputField::InputField(sf::Font& font, float width, float height, float xPos, float yPos)
    {
        sf::Clock clock; // TODO: Check if clock disappears after this scope
        InputField(clock, width, height, xPos, yPos);
        this->inputText.setFont(font);
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::AppendCharacter(char character)
    {
        if(this->inputContent[this->inputContent.getSize()-1] == '|')
            this->RemoveLastChar();
        this->inputContent += character;
        this->inputText.setString(this->inputContent);
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::RemoveLastChar()
    {
        // TODO: Check if this works correctly
        // std::string content = this->inputContent.toAnsiString();
        // this->inputContent = sf::String(content.substr(0, content.length() - 2));
        this->inputContent = this->inputContent.substring(0, this->inputContent.getSize() - 1);
        this->inputText.setString(this->inputContent);
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::RemoveLastContentChar()
    {
        if (this->inputContent.getSize() == 0)
            return;
        if (this->inputContent[this->inputContent.getSize()-1] == '|')
            this->inputContent = this->inputContent.substring(0, this->inputContent.getSize() - 2);
        else
            this->inputContent = this->inputContent.substring(0, this->inputContent.getSize() - 1);
        this->inputText.setString(this->inputContent);
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::SetPosition(float x, float y)
    {
        this->rrs.setPosition(x, y);
        this->centerTextVert();
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::SetFont(sf::Font& font)
    {
        this->inputText.setFont(font);
    }
    
    ////////////////////////////////////////////////////////////
    char* InputField::GetCString()
    {
        return strdup(this->inputText.getString().toAnsiString().c_str());
    }
    
    ////////////////////////////////////////////////////////////
    std::string InputField::GetStdString()
    {
        return this->inputContent.toAnsiString();
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::SetFocus(bool focus)
    {
        this->focus = focus;
        this->timeFocused = this->clock->getElapsedTime().asSeconds();
        if (this->inputContent[this->inputContent.getSize()-1] == '|')
            this->RemoveLastChar();
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::SwitchFocusState()
    {
        if(this->focus)
            this->SetFocus(false);
        else
            this->SetFocus(true);
    }
    
    ////////////////////////////////////////////////////////////
    sf::Vector2f InputField::GetPosition()
    {
        return this->rrs.getPosition();
    }
    
    ////////////////////////////////////////////////////////////
    sf::FloatRect InputField::GetGlobalBounds()
    {
        return this->rrs.getGlobalBounds();
    }
    
    ////////////////////////////////////////////////////////////
    bool InputField::HasFocus()
    {
        return this->focus;
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::ProcessFocusAnimation()
    {
        if(!this->focus)
            return;
        else if(this->clock->getElapsedTime().asSeconds() > this->timeFocused + ANIMATION_TIME_INTERVAL)
        {
            if (this->inputContent[this->inputContent.getSize()-1] == '|')
                this->RemoveLastChar();
            else
                this->AppendCharacter('|');
            this->timeFocused = this->clock->getElapsedTime().asSeconds();
        }
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(this->rrs);
        target.draw(this->inputText);
    }
    
    ////////////////////////////////////////////////////////////
    void InputField::centerTextVert()
    {
        sf::FloatRect rrsBounds = this->rrs.getGlobalBounds();
        this->inputText.setPosition(rrsBounds.left + (rrsBounds.width * 2.5f/ 100.0f),
                                    rrsBounds.top + (rrsBounds.height * 20.0f / 100.0f));
    }
}
