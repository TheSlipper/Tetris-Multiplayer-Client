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
#include "LoginState.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    LoginState::LoginState(ArktisEngine::GameDataRef data) :_data(data), BG_COLOR(sf::Color(245, 246, 250))
    {
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::Init()
    {
        // Load UI font
        if (!this->_data->assets.LoadFont(UI_FONT_NAME, UI_FONT_PATH))
            exit(ERROR_CODE_FONT_NOT_LOADED);
        
        // Set up the state
        this->setUpGameLogo();
        this->centerAndPositionLogo();
        this->setUpLabels();
        this->centerAndPositionLabels();
        this->setUpForm();
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::HandleInput()
    {
        sf::Event event;
        
        while(this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
                this->_data->window.close();
            else if (sf::Event::MouseButtonPressed == event.type)
            {
                this->passwordInput->SetFocus(false);
                this->loginInput->SetFocus(false);
                
                if (this->_data->input.IsInputFieldClicked(*this->loginInput, sf::Mouse::Left, this->_data->window))
                    this->loginInput->SwitchFocusState();
                else if (this->_data->input.IsInputFieldClicked(*this->passwordInput, sf::Mouse::Left, this->_data->window))
                    this->passwordInput->SwitchFocusState();
                else if (this->_data->input.IsButtonClicked(*this->btn, sf::Mouse::Left, this->_data->window))
                {
                    // TODO: New state
                }
            }
            else if (sf::Event::TextEntered == event.type)
            {
                char inputCharacter = static_cast<char>(event.text.unicode);
                if (inputCharacter == (char)8)
                {
                    if (this->loginInput->HasFocus())
                        this->loginInput->RemoveLastContentChar();
                    else if (this->passwordInput->HasFocus())
                        this->passwordInput->RemoveLastContentChar();
                }
                else if (inputCharacter == (char)9)
                {
                }
                else
                {
                    if (this->loginInput->HasFocus())
                        this->loginInput->AppendCharacter(inputCharacter);
                    else if (this->passwordInput->HasFocus())
                        this->passwordInput->AppendCharacter(inputCharacter);
                }
            }
        }
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::Update(float dt)
    {
        this->loginInput->ProcessFocusAnimation();
        this->passwordInput->ProcessFocusAnimation();
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::Draw(float dt)
    {
        this->_data->window.clear(this->BG_COLOR);
 
        this->_data->window.draw(this->logo);
        
        this->_data->window.draw(this->loginLabel);
        
        this->_data->window.draw(*this->loginInput);
        
        this->_data->window.draw(this->passwdLabel);
        
        this->_data->window.draw(*this->passwordInput);
        
        this->_data->window.draw(*this->btn);
        
        this->_data->window.display();
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::centerAndPositionLogo()
    {
        sf::FloatRect spriteRect = this->logo.getGlobalBounds();
        this->logo.setOrigin(spriteRect.left + spriteRect.width/2.0f, 0.0f);
        this->logo.setPosition(sf::Vector2f(this->_data->settings.width / 2.40f, this->_data->settings.height * 5.0f / 100.0f));
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::centerAndPositionLabels()
    {
        sf::FloatRect localRect = this->logo.getGlobalBounds();
        this->loginLabel.setPosition(localRect.left - (5.0f * this->_data->settings.width / 100.0f),
                                     localRect.height + localRect.top + (5.0f * this->_data->settings.height / 100.0f));
        localRect = this->loginLabel.getGlobalBounds();
        this->passwdLabel.setPosition(localRect.left, localRect.height + localRect.top + (4.0f * this->_data->settings.height / 100.0f));
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::setUpLabels()
    {
        // Login
        this->loginLabel.setString("Login: ");
        this->loginLabel.setFillColor(sf::Color::Black);
        this->loginLabel.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        
        // Password
        this->passwdLabel.setString("Password: ");
        this->passwdLabel.setFillColor(sf::Color::Black);
        this->passwdLabel.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::setUpGameLogo()
    {
        if (!this->_data->assets.LoadTexture(TETRISMP_LOGO_NAME, TETRISMP_LOGO_PATH))
            exit(ERROR_CODE_TEXTURE_NOT_LOADED);
        this->logo = this->_data->assets.GetScaledSprite(TETRISMP_LOGO_NAME); // TODO: Check if scaled sprite works for everything
    }
    
    ////////////////////////////////////////////////////////////
    void LoginState::setUpForm()
    {
        this->loginInput = std::make_unique<GameObjects::InputField>(this->_data->gameClock);
        this->passwordInput = std::make_unique<GameObjects::InputField>(this->_data->gameClock);
        
        sf::FloatRect localRect = this->passwdLabel.getGlobalBounds();
        this->passwordInput->SetPosition(localRect.left + localRect.width + (this->_data->settings.width * 2.5f / 100.0f),
                                        localRect.top - (this->_data->settings.height * 1.0f / 100.0f));
        this->passwordInput->SetFont(this->_data->assets.GetFont(UI_FONT_NAME));
        
        this->btn = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), "Log in", localRect.left, localRect.top + localRect.width + 10.0f);
        
        localRect = this->loginLabel.getGlobalBounds();
        this->loginInput->SetPosition(20.0f, 20.0f);
        this->loginInput->SetPosition(localRect.left + localRect.width + (this->_data->settings.width * 5.6f / 100.0f),
                                        localRect.top - (this->_data->settings.height * 1.0f / 100.0f));
        this->loginInput->SetFont(this->_data->assets.GetFont(UI_FONT_NAME));
        this->loginInput->SetFocus(true);
    }
}
