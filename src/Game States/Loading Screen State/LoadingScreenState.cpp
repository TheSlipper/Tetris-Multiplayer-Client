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
#include "LoadingScreenState.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    LoadingScreenState::LoadingScreenState(ArktisEngine::GameDataRef data) :_data(data)
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingScreenState::Init()
    {
        this->loadingScreenText.setString("LOOKING FOR AN OPPONENT...");
        this->loadingScreenText.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        this->loadingScreenText.setCharacterSize(this->_data->settings.width * 128.f / 3820.f);
        this->loadingScreenText.setFillColor(sf::Color::Black);
        this->centerText();
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingScreenState::HandleInput()
    {
        sf::Event event;
        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->messaging.DisconnectSocket();
                this->_data->window.close();
            }
        }
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingScreenState::Update(float dt)
    {
        if (!this->firstDraw)
        {
            this->sendMatchmakingReq();
            if (this->serverResponse.substr(0, 10).compare("GAME_SETUP") == 0)
                this->_data->machine.AddState((ArktisEngine::StateRef)new GameState(this->_data), true);
        }
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingScreenState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::White);
        
        this->_data->window.draw(this->loadingScreenText);
        
        this->_data->window.display();
        
        this->firstDraw = false;
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingScreenState::centerText()
    {
        sf::FloatRect textRect = this->loadingScreenText.getLocalBounds();
        loadingScreenText.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
        loadingScreenText.setPosition(sf::Vector2f(this->_data->settings.width/2.0f, this->_data->settings.height/2.0f));
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingScreenState::sendMatchmakingReq()
    {
        const std::string gameSearch = "GAME_SEARCH " + this->_data->userData.username + " " + std::to_string(this->_data->userData.elo);
        this->_data->messaging.SendStringData(gameSearch);
        serverResponse = this->_data->messaging.GetStringResponse();
    }
}
