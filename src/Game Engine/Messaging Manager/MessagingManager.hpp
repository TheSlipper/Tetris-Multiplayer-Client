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
		/// \deprecated This is to be removed in the future versions
		///					because it's not used by anything
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
		
		////////////////////////////////////////////////////////////
		/// \brief Sets the ip address of the server
		///
		////////////////////////////////////////////////////////////
		void SetIpAddress(sf::IpAddress addr);

		////////////////////////////////////////////////////////////
		/// \brief Sets the socket type flag to true
		///
		////////////////////////////////////////////////////////////
		void SetToTcp(bool usingTcp);

		////////////////////////////////////////////////////////////
		/// \brief Sets the socket type flag to false
		///
		////////////////////////////////////////////////////////////
		void SetToUdp(bool usingUdp);

    private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
		bool usingTcp = true; ///< Flag that determines which socket should be used

		sf::IpAddress serverIpAddress; ///< Ip address of the server

		const unsigned short mainServerPort = 7001; ///< Port used for sending a request for a unique client dedicated port

		unsigned short serverPort; ///< Port assigned for the client by the server

        sf::TcpSocket tcpSocket; ///< Socket used in tcp connections

		sf::UdpSocket udpSocket; ///< Socket used in udp connections
    };
}
