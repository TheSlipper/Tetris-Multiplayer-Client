////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
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
//        std::fstream fileReader(settingsFilePath, std::ios::in);
//        unsigned short int settIterator = 0;  // 0 = width, 1 = height;
//        std::string readLine;
//        unsigned int width, height, master_vol, sfx_vol, music_vol;
//
//        if (!fileReader.good())
//            exit(-255); // TODO: Show some info on no settings file
//
//        while(!fileReader.eof())
//        {
//            getline(fileReader, readLine);
//            if (isdigit(readLine[0]) || isalpha(readLine[0]))
//            {
//                switch (settIterator)
//                {
//                    case 0:
//                        width = std::stoi(readLine);
//                        break;
//                    case 1:
//                        height = std::stoi(readLine);
//                        break;
//                    case 2:
//                        master_vol = std::stoi(readLine);
//                        break;
//                    case 3:
//                        sfx_vol = std::stoi(readLine);
//                        break;
//                    case 4:
//                        music_vol = std::stoi(readLine);
//                        break;
//                    default:
//                        break;
//                }
//                settIterator++;
//            }
//        }
//        fileReader.clear();
//        fileReader.close();
//        this->_data->settings.width = width;
//        this->_data->settings.height = height;
//        this->_data->settings.master_vol = master_vol;
//        this->_data->settings.sfx_vol = sfx_vol;
//        this->_data->settings.music_vol = music_vol;
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
