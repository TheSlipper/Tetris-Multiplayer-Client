////////////////////////////////////////////////////////////
// Created by Kornel Domeradzki and Kamil Kwaśnik.
// Copyright © 2018 Kornel Domeradzki and Kamil Kwaśnik. All rights reserved.
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
