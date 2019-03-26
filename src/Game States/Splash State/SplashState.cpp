////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Definitions
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
        this->_data->assets.LoadTexture(SPLASHSCREEN_NAME, SPLASHSCREEN_PATH);
        this->logo = this->_data->assets.GetScaledSprite(SPLASHSCREEN_NAME, this->_data->settings.height, this->_data->settings.width);
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
            exit(0);
    }
    
    ////////////////////////////////////////////////////////////
    void SplashState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);
        
        this->_data->window.draw(this->logo);
        
        this->_data->window.display();
    }
}
