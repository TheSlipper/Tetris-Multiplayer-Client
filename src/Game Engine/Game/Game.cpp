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
#include "Game.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    Game::Game()
    {
        this->LoadGamesSettings("game_settings.conf");
        
        _data->window.create(sf::VideoMode(this->_data->settings.width,
                                           this->_data->settings.height), GAME_NAME, sf::Style::Close
                             | sf::Style::Titlebar);
        
        _data->machine.AddState(StateRef(new States::SplashState(this->_data)));
        
        this->Run();
    }
    
    ////////////////////////////////////////////////////////////
    void Game::LoadGamesSettings(std::string settingsFilePath)
    {
        // TODO: This function
        this->_data->settings.width = 1920;
        this->_data->settings.height = 1080;
        this->_data->settings.master_vol = 100;
        this->_data->settings.sfx_vol = 100;
        this->_data->settings.music_vol = 100;
    }
    
    ////////////////////////////////////////////////////////////
    void Game::Run()
    {
        float newTime, frameTime, interpolation;
        
        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;
        
        while (this->_data->window.isOpen())
        {
            this->_data->machine.ProcessStateChanges();
            
            newTime = this->_clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;
            
            if (frameTime > 0.25f)
                frameTime = 0.25f;
            
            currentTime = newTime;
            accumulator += frameTime;
            
            while (accumulator >= dt)
            {
                this->_data->machine.GetActiveState()->HandleInput();
                this->_data->machine.GetActiveState()->Update(dt);
                
                accumulator -= dt;
            }
            
            interpolation = accumulator / dt;
            this->_data->machine.GetActiveState()->Draw(interpolation);
        }
    }
}
