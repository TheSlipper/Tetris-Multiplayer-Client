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
#include "GameOverState.hpp"

namespace States
{
	////////////////////////////////////////////////////////////
	GameOverState::GameOverState(ArktisEngine::UserData opponentData, ArktisEngine::GameDataRef data) :_data(data)
	{
		this->opponentData = opponentData;
	}

	////////////////////////////////////////////////////////////
	void GameOverState::Init()
	{
		std::string resp = this->_data->messaging.GetStringResponse();
		this->parseResponseData(resp);
	}

	////////////////////////////////////////////////////////////
	void GameOverState::HandleInput()
	{
		sf::Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->messaging.DisconnectSocket();
				this->_data->window.close();
			}
		}
	}

	////////////////////////////////////////////////////////////
	void GameOverState::Update(float dt)
	{
	}

	////////////////////////////////////////////////////////////
	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);

		this->_data->window.display();
	}

	////////////////////////////////////////////////////////////
	void GameOverState::parseResponseData(const std::string &data)
	{
		ArktisEngine::StringTokenizer tokenizer{data};
		int iterator = 0;
		for (const auto &t : tokenizer)
		{
			switch (iterator)
			{
			case 3:
				this->_data->userData.elo = std::stoi(t);
				break;
			case 4:
				this->_data->userData.unrankedWins = std::stoi(t);
				break;
			case 5:
				this->_data->userData.unrankedLosses = std::stoi(t);
				break;
			case 6:
				this->_data->userData.rankedWins = std::stoi(t);
				break;
			case 7:
				this->_data->userData.rankedLosses = std::stoi(t);
				break;
			case 8:
				this->_data->userData.tetrominoPoints = std::stoi(t);
				break;
			case 9:
				this->_data->userData.timePlayed = std::stol(t);
				break;
			case 10:
				this->playerPoints = std::stoi(t);
				break;
			case 11:
				this->time = std::stol(t);
				break;
			}
			iterator++;
		}
		return;
	}
}
