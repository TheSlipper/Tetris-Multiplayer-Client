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
#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    /// \brief Class that manages all of the asset data.
    ///
    ////////////////////////////////////////////////////////////
    class AssetManager
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        AssetManager() { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Default destructor
        ///
        ////////////////////////////////////////////////////////////
        ~AssetManager() { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Loads texture to the textures map
        ///
        /// \param std::string name index for the map entry
        ///
        /// \param std::string filePath relative path to the file
        ///
        ////////////////////////////////////////////////////////////
        void LoadTexture(std::string name, std::string filePath);
        
        ////////////////////////////////////////////////////////////
        /// \brief Loads texture to the textures map
        ///
        /// \param std::string name index for the map entry
        ///
        /// \param std::string filePath relative path to the file
        ///
        ////////////////////////////////////////////////////////////
        void LoadRepetitiveTexture(std::string name, std::string filePath);
        
        ////////////////////////////////////////////////////////////
        /// \brief Removes the texture from the textures map
        ///
        /// \param std::string name removes the texture with the
        ///                         given index from the map
        ///
        ////////////////////////////////////////////////////////////
        void RemoveTexture(std::string name);
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the reference to the sf::Texture object with
        ///          the given index
        ///
        /// \param std::string name index of the file in the map
        ///
        ////////////////////////////////////////////////////////////
        sf::Texture &GetTexture(std::string name);
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the reference to a scaled sf::Sprite object with
        ///          the specified texture's name
        ///
        /// \param std::string name of the file
        ///
        ////////////////////////////////////////////////////////////
        sf::Sprite& GetScaledSprite(std::string name, int height=1080, int width=1920);
        
        ////////////////////////////////////////////////////////////
        /// \brief Loads font to the fonts map
        ///
        /// \param std::string name index for the map entry
        ///
        /// \param std::string filePath relative path to the file
        ///
        ////////////////////////////////////////////////////////////
        void LoadFont(std::string name, std::string filePath);
        
        ////////////////////////////////////////////////////////////
        /// \brief Removes the font from the textures map
        ///
        /// \param std::string name removes the font with the given
        ///                         index from the map
        ///
        ////////////////////////////////////////////////////////////
        void RemoveFont(std::string name);
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the reference to the sf::Font object with
        ///         the given index
        ///
        /// \param std::string name index of the file in the map
        ///
        ////////////////////////////////////////////////////////////
        sf::Font &GetFont(std::string name);
        
        ////////////////////////////////////////////////////////////
        /// \brief Loads sound buffer object to the sound buffers map
        ///
        /// \param std::string name index for the map entry
        ///
        /// \param std::string filePath relative path to the file
        ///
        ////////////////////////////////////////////////////////////
        void LoadSoundBuffer(std::string name, std::string filePath);
        
        ////////////////////////////////////////////////////////////
        /// \brief Removes the sound buffer from the textures map
        ///
        /// \param std::string name removes the sound buffer with the
        ///                         given index from the map
        ///
        ////////////////////////////////////////////////////////////
        void removeSoundBuffer(std::string name);
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the reference to the sf::SoundBuffer object
        ///         with the given index
        ///
        /// \param std::string name index of the file in the map
        ///
        ////////////////////////////////////////////////////////////
        sf::SoundBuffer& getSoundBuffer(std::string name);
        
    private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        std::map<std::string, sf::Texture> textures;    ///< Textures' map
        
        std::map<std::string, sf::Font> fonts;  ///< Fonts' map
        
        std::map<std::string, sf::SoundBuffer> soundBuffers;    ///< Sound buffers' map
    };
}
