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
#include "MiscUtils.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    void ScaleSprToDims(sf::Sprite& spr, float &width, float &height)
    {
        sf::FloatRect bounds = spr.getGlobalBounds();
        spr.setScale((width * 100.0 / bounds.width) * 0.01, (height * 100.0 / bounds.height) * 0.01);
    }
    
    ////////////////////////////////////////////////////////////
    void ScaleSprToDims(sf::Sprite& spr, sf::Vector2f& vect)
    {
        sf::FloatRect bounds = spr.getGlobalBounds();
        spr.setScale((vect.x * 100.0 / bounds.width) * 0.01, (vect.y * 100.0 / bounds.height) * 0.01);
    }
    
    ////////////////////////////////////////////////////////////
    sf::Vector2f GetPosRelToScreenByPrct(float verticalPercent, float horizontalPercent, GameSettings &settings)
    {
        return sf::Vector2f(verticalPercent * settings.width / 100.f, horizontalPercent * settings.height / 100.f);
    }
    
    ////////////////////////////////////////////////////////////
    float GetYPosRelToScreenByPrct(float yPerc, GameSettings &settings)
    {
        return yPerc * settings.height / 100.f;
    }
    
    ////////////////////////////////////////////////////////////
    float GetXPosRelToScreenByPrct(float xPerc, GameSettings &settings)
    {
        return xPerc * settings.width / 100.f;
    }
    
    ////////////////////////////////////////////////////////////
    void CenterHorizontally(sf::Text &text, GameSettings &settings, float y)
    {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(settings.width / 2.0f, y));
    }
    
    ////////////////////////////////////////////////////////////
    void CenterHorizontallyInArea(sf::Text &text, float areaWidth, float y)
    {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        text.setPosition(sf::Vector2f(areaWidth / 2.f, y));
    }
    
    ////////////////////////////////////////////////////////////
    void CenterHorizontallyInArea(GameObjects::Button &button, float areaWidth, float y)
    {
        sf::FloatRect btnRect = button.GetGlobalBounds();
        button.SetOrigin(btnRect.left + btnRect.width / 2.f, btnRect.top + btnRect.height / 2.f);
        button.SetPosition(sf::Vector2f(areaWidth / 2.f, y));
    }
}
