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

#include <iostream>

namespace ArktisEngine
{
    ////////////////////////////////////////////////////////////
    bool MessagingManager::ConnectToServer()
    {
		bool execStatus = true;
		if (this->usingTcp)
			execStatus = this->tcpSocket.connect(this->serverIpAddress, this->mainServerPort) == sf::Socket::Done;
		else
		{
			const char *connectionMsg = "PORT_ALLOC_REQ";
			char buff[100];
			std::size_t received;
			sf::IpAddress sender;
			unsigned short port;
			if (this->udpSocket.bind(7000) != sf::Socket::Done)
				return false;
			if (this->udpSocket.send(connectionMsg, strlen(connectionMsg), this->serverIpAddress, mainServerPort) != sf::Socket::Done)
				return false;
			if (this->udpSocket.receive(buff, 100, received, sender, port) != sf::Socket::Done)
				return false;
			this->serverPort = (short)std::stoi(std::string(buff).substr(14, 18));
		}

		return execStatus;
    }
    
    ////////////////////////////////////////////////////////////
    bool MessagingManager::SendStringData(std::string stringData)
    {
        char *data = strdup(stringData.c_str());
		bool execStatus = false;
		if (this->usingTcp)
			execStatus = this->tcpSocket.send(data, strlen(data)) == sf::Socket::Done;
		else
		{
			char buffer[3];
			memset(buffer, 0, 3);
			sf::IpAddress sender;
			std::size_t received = 0;
			unsigned short port;
			do
			{
				const static char *okChar = "OK";
				int checksum = this->getStrChecksum(data, strlen(data));
				std::cout << checksum << std::endl;
				execStatus = this->udpSocket.send(data, strlen(data), this->serverIpAddress, this->serverPort) == sf::Socket::Done;
				this->udpSocket.receive(buffer, 2, received, sender, port);
				execStatus = (strcmp(buffer, okChar) == 0) && execStatus;
			} while (!execStatus);
		}

		return execStatus;
    }
    
    ////////////////////////////////////////////////////////////
    std::string MessagingManager::GetStringResponse()
    {
        static char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
        std::size_t received = 0;
		sf::IpAddress sender;
		unsigned short port;
		bool execStatus = false;

		if (this->usingTcp)
			execStatus = this->tcpSocket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done;
		else 
		{
			execStatus = this->udpSocket.receive(buffer, sizeof(buffer), received, sender, port) == sf::Socket::Done;
			this->udpSocket.send("OK", strlen("OK"), this->serverIpAddress, this->serverPort);
		}
		
		return execStatus ? std::string(buffer).substr(0, received) : "DATA_GET_ERR";
    }
    
	////////////////////////////////////////////////////////////
	std::string MessagingManager::GetStringResponse(const int bufferSize)
	{
		char *buffer = new char[bufferSize];
		std::size_t received = 0;
		if (this->tcpSocket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done)
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
        this->tcpSocket.disconnect();
        return res;
    }
	
	////////////////////////////////////////////////////////////
	void MessagingManager::SetIpAddress(sf::IpAddress addr)
	{
		this->serverIpAddress = addr;
	}

	////////////////////////////////////////////////////////////
	void MessagingManager::SetToTcp(bool usingTcp)
	{
		this->usingTcp = usingTcp;
	}

	////////////////////////////////////////////////////////////
	void MessagingManager::SetToUdp(bool usingUdp)
	{
		this->SetToTcp(!usingUdp);
	}

	////////////////////////////////////////////////////////////
	int MessagingManager::getStrChecksum(const char *ptr, size_t sz)
	{
		int chk = 0;
		for (int i = 0; i < sz; i++)
			chk -= (int)*ptr++;
		return chk/sz;
	}
}
