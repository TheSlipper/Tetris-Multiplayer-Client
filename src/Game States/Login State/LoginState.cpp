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

#include <iostream>

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
        this->_data->messaging.ConnectToServer();
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
            {
                this->_data->messaging.DisconnectSocket();
                this->_data->window.close();
            }
            else if (sf::Event::MouseButtonPressed == event.type)
            {
                this->_passwordInput->SetFocus(false);
                this->_loginInput->SetFocus(false);

                if (this->_data->input.IsInputFieldClicked(*this->_loginInput, sf::Mouse::Left, this->_data->window))
                    this->_loginInput->SwitchFocusState();
                else if (this->_data->input.IsInputFieldClicked(*this->_passwordInput, sf::Mouse::Left, this->_data->window))
                    this->_passwordInput->SwitchFocusState();
                else if (this->_data->input.IsButtonClicked(*this->_loginButton, sf::Mouse::Left, this->_data->window))
                    this->sendFormData();
            }
            else if (sf::Event::TextEntered == event.type)
            {
                char inputCharacter = static_cast<char>(event.text.unicode);
                if (inputCharacter == (char)8)
                {
                    // Backspace
                    if (this->_loginInput->HasFocus())
                        this->_loginInput->RemoveLastContentChar();
                    else if (this->_passwordInput->HasFocus())
                    {
                        this->passwd.pop_back();
                        this->_passwordInput->RemoveLastContentChar();
                    }
                }
                else if (inputCharacter == (char)9)
                {
                    // Tab
                    if (this->_loginInput->HasFocus())
                    {
                        this->_loginInput->SwitchFocusState();
                        this->_passwordInput->SetFocus(true);
                    }
                    else
                    {
                        this->_loginInput->SetFocus(true);
                        this->_passwordInput->SwitchFocusState();
                    }
                }
                else if (inputCharacter == (char)10 || inputCharacter == (char)13) // Enter
                    this->sendFormData();
                else
                {
                    if (this->_loginInput->HasFocus())
                        this->_loginInput->AppendCharacter(inputCharacter);
                    else if (this->_passwordInput->HasFocus())
                    {
                        this->passwd += inputCharacter;
                        this->_passwordInput->AppendCharacter('*');
                    }
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void LoginState::Update(float dt)
    {
        this->_loginInput->ProcessFocusAnimation();
        this->_passwordInput->ProcessFocusAnimation();
    }

    ////////////////////////////////////////////////////////////
    void LoginState::Draw(float dt)
    {
        this->_data->window.clear(this->BG_COLOR);

        this->_data->window.draw(this->logo);

        this->_data->window.draw(this->loginLabel);

        this->_data->window.draw(*this->_loginInput);

        this->_data->window.draw(this->passwdLabel);

        this->_data->window.draw(*this->_passwordInput);

        this->_data->window.draw(*this->_loginButton);

        this->_data->window.display();
    }

    ////////////////////////////////////////////////////////////
    void LoginState::centerAndPositionLogo()
    {
        sf::FloatRect spriteRect = this->logo.getGlobalBounds();
        this->logo.setOrigin(spriteRect.left + spriteRect.width/2.0f, 0.0f);
        this->logo.setPosition(sf::Vector2f(this->_data->settings.width / 2.40f, this->_data->settings.height * 5.0f / 100.0f));
        this->logo.move(-1 * ArktisEngine::GetXPosRelToScreenByPrct(10.f, this->_data->settings), 0.f);
    }

    ////////////////////////////////////////////////////////////
    void LoginState::centerAndPositionLabels()
    {
//        sf::FloatRect localRect = this->logo.getGlobalBounds();
        sf::FloatRect localRect;
        localRect.width = this->_data->settings.width;
        localRect.height = this->_data->settings.height;
//        this->loginLabel.setPosition(localRect.left - (5.0f * this->_data->settings.width / 100.0f),
//                                     localRect.height + localRect.top + (5.0f * this->_data->settings.height / 100.0f));
        this->loginLabel.setPosition(localRect.width/2.75f, localRect.height - (localRect.height * 30.f / 100.f));
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
        // this->logo = this->_data->assets.GetScaledSprite(TETRISMP_LOGO_NAME); // TODO: Check if scaled sprite works for everything
        this->logo.setTexture(this->_data->assets.GetTexture(TETRISMP_LOGO_NAME));
        float width = this->_data->settings.width / 2.f, height = this->_data->settings.height / 2.f;
        ArktisEngine::ScaleSprToDims(this->logo, width, height);
    }

    ////////////////////////////////////////////////////////////
    void LoginState::setUpForm()
    {
        this->_loginInput = std::make_unique<GameObjects::InputField>(this->_data->gameClock);
        this->_passwordInput = std::make_unique<GameObjects::InputField>(this->_data->gameClock);

        sf::FloatRect localRect = this->passwdLabel.getGlobalBounds();
        this->_passwordInput->SetPosition(localRect.left + localRect.width + (this->_data->settings.width * 2.5f / 100.0f),
                                        localRect.top - (this->_data->settings.height * 1.0f / 100.0f));
        this->_passwordInput->SetFont(this->_data->assets.GetFont(UI_FONT_NAME));

        this->_loginButton = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), "Log in", this->passwdLabel.getGlobalBounds().left + localRect.width/2.f, localRect.top + (localRect.width/2.f) + 10.0f);

        localRect = this->loginLabel.getGlobalBounds();
        this->_loginInput->SetPosition(localRect.left + localRect.width + (this->_data->settings.width * 5.6f / 100.0f),
                                        localRect.top - (this->_data->settings.height * 1.0f / 100.0f));
        this->_loginInput->SetFont(this->_data->assets.GetFont(UI_FONT_NAME));
        this->_loginInput->SetFocus(true);
    }

    ////////////////////////////////////////////////////////////
    void LoginState::sendFormData()
    {
        this->_data->messaging.SendStringData("LOGIN " + this->_loginInput->GetStdString() + " " + this->passwd);
        std::string response = this->_data->messaging.GetStringResponse();
        if (response.substr(0, 20 + this->_loginInput->GetStdString().length()).compare("CORRECT_CREDENTIALS " + this->_loginInput->GetStdString()) == 0)
        {
            this->_data->userData.username = this->_loginInput->GetStdString();
            this->_data->userData.password = this->passwd;
            this->_data->machine.AddState((ArktisEngine::StateRef)new HomeScreenState(this->_data), true);
        }
        else
        {
            // TODO: Handle wrong credentials
        }
    }
}
