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
#include "InputManager.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(button))
        {
            sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
            
            if (playButtonRect.contains(sf::Mouse::getPosition(window)))
                return true;
        }
        
        return false;
    }
    
    ////////////////////////////////////////////////////////////
    bool InputManager::IsTextClicked(sf::Text object, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(button))
        {
            sf::IntRect playButtonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
            
            if (playButtonRect.contains(sf::Mouse::getPosition(window)))
                return true;
        }
        
        return false;
    }
    
    ////////////////////////////////////////////////////////////
    bool InputManager::IsInputFieldClicked(GameObjects::InputField inputField, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if(sf::Mouse::isButtonPressed(button))
        {
            sf::IntRect ifRect(inputField.GetPosition().x, inputField.GetPosition().y, inputField.GetGlobalBounds().width, inputField.GetGlobalBounds().height);
            if (ifRect.contains(sf::Mouse::getPosition(window)))
                return true;
        }
        
        return false;
    }
    
    ////////////////////////////////////////////////////////////
    bool InputManager::IsButtonClicked(GameObjects::Button btn, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if(sf::Mouse::isButtonPressed(button))
        {
            sf::IntRect btnRect(btn.GetPosition().x, btn.GetPosition().y, btn.GetGlobalBounds().width, btn.GetGlobalBounds().height);
            if (btnRect.contains(sf::Mouse::getPosition(window)))
                return true;
        }
        
        return false;
    }
    
    ////////////////////////////////////////////////////////////
    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window)
    {
        return sf::Mouse::getPosition(window);
    }
}
