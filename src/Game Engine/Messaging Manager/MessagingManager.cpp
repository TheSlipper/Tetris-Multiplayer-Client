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
#include "MessagingManager.hpp"

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    bool MessagingManager::ConnectToServer()
    {
        return this->socket.connect(SERVER_IP, SERVER_PORT) == sf::Socket::Done;
    }
    
    ////////////////////////////////////////////////////////////
    bool MessagingManager::SendStringData(std::string stringData)
    {
        char *data = strdup(stringData.c_str());
        return this->socket.send(data, strlen(data)) == sf::Socket::Done;
    }
    
    ////////////////////////////////////////////////////////////
    std::string MessagingManager::GetStringResponse()
    {
        static char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
        std::size_t received = 0;
        if (this->socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
            return "DATA_GET_ERR";
        else
        {
            std::string stringBuff(buffer);
            return stringBuff.substr(0, received);
        }
    }
    
	////////////////////////////////////////////////////////////
	std::string MessagingManager::GetStringResponse(const int bufferSize)
	{
		char *buffer = new char[bufferSize];
		std::size_t received = 0;
		if (this->socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
			return "DATA_GET_ERR";
		else
		{
			std::string stringBuff(buffer);
			return stringBuff.substr(0, received);
		}
	}

	////////////////////////////////////////////////////////////
	bool MessagingManager::DisconnectSocket()
    {
        bool res = this->SendStringData("LOGOUT");
        this->socket.disconnect();
        return res;
    }
}
