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
#include "Button.hpp"

namespace GameObjects
{
    ////////////////////////////////////////////////////////////
    Button::Button(std::string label, float x, float y, float width, float height)
    {
        this->rrs.setCornerPointCount(4);
        this->rrs.setPosition(x, y);
        this->rrs.setSize(sf::Vector2f(width, height));
        this->rrs.setFillColor(sf::Color(0,0,0));
        this->buttonLabel.setString(label);
        this->buttonLabel.setCharacterSize(9.0f * this->rrs.getGlobalBounds().width / 100.0f);
        this->buttonLabel.setFillColor(sf::Color(255,255,255));
        this->centerTextVert();
    }
    
    ////////////////////////////////////////////////////////////
    Button::Button(sf::Font &font, std::string label, float x, float y, float width, float height)
    {
        this->SetFont(font);
        this->rrs.setCornerPointCount(4);
        this->rrs.setPosition(x, y);
        this->rrs.setSize(sf::Vector2f(width, height));
        this->rrs.setFillColor(sf::Color(0,0,0));
        this->buttonLabel.setString(label);
        this->buttonLabel.setPosition(x, y);
        this->buttonLabel.setCharacterSize(9.0f * this->rrs.getGlobalBounds().width / 100.0f);
//        this->buttonLabel.setFillColor(sf::Color(255,255,255));
        this->buttonLabel.setFillColor(sf::Color(255,255,255));
        this->centerTextVert();
    }
    
    ////////////////////////////////////////////////////////////
    void Button::SetFont(sf::Font &font)
    {
        this->buttonLabel.setFont(font);
    }
    
    ////////////////////////////////////////////////////////////
    sf::FloatRect Button::GetGlobalBounds()
    {
        return this->rrs.getGlobalBounds();
    }
    
    sf::Vector2f Button::GetPosition()
    {
        return this->rrs.getPosition();
    }
    
    ////////////////////////////////////////////////////////////
    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(this->rrs);
        target.draw(this->buttonLabel);
    }
    
    ////////////////////////////////////////////////////////////
    void Button::centerTextVert()
    {
        sf::FloatRect textBounds = this->buttonLabel.getGlobalBounds();
        sf::FloatRect rrsBounds = this->rrs.getGlobalBounds();
        
        this->buttonLabel.setOrigin(textBounds.width/2.0f, textBounds.height/2.0f);
        this->buttonLabel.setPosition(rrsBounds.left + rrsBounds.width/2.0f, rrsBounds.top + rrsBounds.height/2.75f);
    }
}
