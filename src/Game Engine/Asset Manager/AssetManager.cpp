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
#include "AssetManager.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    bool AssetManager::LoadTexture(std::string name, std::string filePath)
    {
        sf::Texture tex;
        
        if (tex.loadFromFile(filePath))
        {
            this->textures[name] = tex;
            return true;
        }
        
        return false;
    }
    
    ////////////////////////////////////////////////////////////
    bool AssetManager::LoadRepetitiveTexture(std::string name, std::string filePath)
    {
        sf::Texture tex;
        
        if (tex.loadFromFile(filePath))
        {
            tex.setRepeated(true);
            this->textures[name] = tex;
            return true;
        }
        
        return false;
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
    bool AssetManager::LoadFont(std::string name, std::string filePath)
    {
        sf::Font font;
        
        if (font.loadFromFile(filePath))
        {
            this->fonts[name] = font;
            return true;
        }
        
        return false;
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
    bool AssetManager::LoadSoundBuffer(std::string name, std::string filePath)
    {
        sf::SoundBuffer sndb;
        
        if (sndb.loadFromFile(filePath))
        {
            this->soundBuffers[name] = sndb;
            return true;
        }
        
        return false;
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
