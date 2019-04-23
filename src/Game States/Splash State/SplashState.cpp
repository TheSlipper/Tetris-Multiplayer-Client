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
#include "SplashState.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    SplashState::SplashState(ArktisEngine::GameDataRef data) : _data(data)
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void SplashState::Init()
    {
        this->startTime = this->_data->gameClock.getElapsedTime().asSeconds();
        if (!this->_data->assets.LoadTexture(SPLASHSCREEN_NAME, SPLASHSCREEN_PATH))
            exit(ERROR_CODE_TEXTURE_NOT_LOADED);
        this->logo.setTexture(this->_data->assets.GetTexture(SPLASHSCREEN_NAME));
        ArktisEngine::ScaleSprToDims(this->logo, this->_data->settings.width, this->_data->settings.height);
    }
    
    ////////////////////////////////////////////////////////////
    void SplashState::HandleInput()
    {
        sf::Event event;
        
        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
                this->_data->window.close();
        }
    }
    
    ////////////////////////////////////////////////////////////
    void SplashState::Update(float dt)
    {
        float updatedTime = this->_data->gameClock.getElapsedTime().asSeconds();
        if (updatedTime - this->startTime > 3.0)
            this->_data->machine.AddState(ArktisEngine::StateRef(new LoginState(this->_data)), true);
    }
    
    ////////////////////////////////////////////////////////////
    void SplashState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);
        
        this->_data->window.draw(this->logo);
        
        this->_data->window.display();
    }
}
