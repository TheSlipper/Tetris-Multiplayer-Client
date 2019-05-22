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
#include <SFML/Network.hpp>
#include <string.h>
#include "../../Definitions/METADATA_DEFINITIONS.h"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    /// \brief Class that manages all of the asset data.
    ///
    ////////////////////////////////////////////////////////////
    class MessagingManager
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        MessagingManager() { }

        ////////////////////////////////////////////////////////////
        /// \brief Default destructor
        ///
        ////////////////////////////////////////////////////////////
        ~MessagingManager() { }

        ////////////////////////////////////////////////////////////
        /// \brief Connects to the main game server
        ///
        /// \returns true on success
        ///
        ////////////////////////////////////////////////////////////
        bool ConnectToServer();

        ////////////////////////////////////////////////////////////
        /// \brief Sends string data to the host
        ///
        ///
        ////////////////////////////////////////////////////////////
        bool SendStringData(std::string stringData);

        ////////////////////////////////////////////////////////////
        /// \brief Gets the string response from the host
        ///
        ///
        ////////////////////////////////////////////////////////////
        std::string GetStringResponse();

		////////////////////////////////////////////////////////////
		/// \brief Gets the string response from the host
		///
		/// \param bufferSize defines the size of buffer used to 
		///			get the message
		///
		////////////////////////////////////////////////////////////
		std::string GetStringResponse(const int bufferSize);
        
        ////////////////////////////////////////////////////////////
        /// \brief Sends a message about client shutdown and gently
        ///         disconnects the socket
        ///
        ///
        ////////////////////////////////////////////////////////////
        bool DisconnectSocket();

    private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::TcpSocket socket;
    };
}
