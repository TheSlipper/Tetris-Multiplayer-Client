////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki and Kamil Kwaśnik.
// Copyright © 2018 Kornel Domeradzki and Kamil Kwaśnik. All rights reserved.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "AssetManager.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    void AssetManager::LoadTexture(std::string name, std::string filePath)
    {
        sf::Texture tex;
        
        if (tex.loadFromFile(filePath))
            this->textures[name] = tex;
    }
    
    ////////////////////////////////////////////////////////////
    void AssetManager::LoadRepetitiveTexture(std::string name, std::string filePath)
    {
        sf::Texture tex;
        
        if (tex.loadFromFile(filePath)) {
            tex.setRepeated(true);
            this->textures[name] = tex;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AssetManager::RemoveTexture(std::string name)
    {
        this->textures.erase(name);
    }
    
    ////////////////////////////////////////////////////////////
    sf::Texture &AssetManager::GetTexture(std::string name)
    {
        return this->textures.at(name);
    }
    
    ////////////////////////////////////////////////////////////
    void AssetManager::LoadFont(std::string name, std::string filePath)
    {
        sf::Font font;
        
        if (font.loadFromFile(filePath))
        {
            this->fonts[name] = font;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AssetManager::RemoveFont(std::string name)
    {
        this->fonts.erase(name);
    }
    
    ////////////////////////////////////////////////////////////
    sf::Font &AssetManager::GetFont(std::string name)
    {
        return this->fonts.at(name);
    }
    
    ////////////////////////////////////////////////////////////
    void AssetManager::LoadSoundBuffer(std::string name, std::string filePath)
    {
        sf::SoundBuffer sndb;
        
        if (sndb.loadFromFile(filePath))
        {
            this->soundBuffers[name] = sndb;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AssetManager::removeSoundBuffer(std::string name)
    {
        this->soundBuffers.erase(name);
    }
    
    ////////////////////////////////////////////////////////////
    sf::SoundBuffer& AssetManager::getSoundBuffer(std::string name)
    {
        return this->soundBuffers.at(name);
    }
}
