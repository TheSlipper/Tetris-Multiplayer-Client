////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki.
// Copyright © 2018 Kornel Domeradzki. All rights reserved.
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
    sf::Sprite& AssetManager::GetScaledSprite(std::string name, int height, int width)
    {
        sf::Sprite sprite;
        sprite.setTexture(this->GetTexture(name));
        sprite.setScale((width * 100.0 / 3840.0) * 0.01, (height * 100.0 / 2160.0) * 0.01);
        
        return sprite;
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
