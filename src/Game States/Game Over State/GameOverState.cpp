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
		if (resp[0] != 'L')
			this->parseResponseData(resp);
		else
		{
			resp = this->_data->messaging.GetStringResponse();
			this->parseResponseData(resp);
		}
		this->placeLabelsWithVals();
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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				this->_data->machine.AddState((ArktisEngine::StateRef) new HomeScreenState(this->_data), true);
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

		this->drawLabels(this->_data->window, this->scoreLabel, this->p1Score, this->p2Score);

		this->drawLabels(this->_data->window, this->linesLabel, this->p1Lines, this->p2Lines);

		this->drawLabels(this->_data->window, this->eloLabel, this->p1Elo, this->p2Elo);

		this->drawLabels(this->_data->window, this->unrankedWinsLabel, this->p1UnrWins, this->p2UnrWins);

		this->drawLabels(this->_data->window, this->rankedWinsLabel, this->p1RanWins, this->p2RanWins);

		this->_data->window.display();
	}

	////////////////////////////////////////////////////////////
	void GameOverState::assignDataByIterator(int &iterator, const std::string &val, ArktisEngine::UserData &data)
	{
		switch (iterator)
		{
		case 3:
			data.elo = std::stoi(val);
			break;
		case 4:
			data.unrankedWins = std::stoi(val);
			break;
		case 5:
			data.unrankedLosses = std::stoi(val);
			break;
		case 6:
			data.rankedWins = std::stoi(val);
			break;
		case 7:
			data.rankedLosses = std::stoi(val);
			break;
		case 8:
			data.tetrominoPoints = std::stoi(val);
			break;
		case 9:
			data.timePlayed = std::stol(val);
			break;
		}
	}

	////////////////////////////////////////////////////////////
	void GameOverState::parseResponseData(const std::string &data)
	{
		ArktisEngine::StringTokenizer tokenizer{data};
		int iterator = 0;
		bool p1Data = true;
		for (const auto &t : tokenizer)
		{
			if (iterator < 3)
				iterator++;
			else if (p1Data)
			{
				if (iterator < 10)
					this->assignDataByIterator(iterator, t, this->_data->userData);
				else if (iterator == 10)
					this->p1Pts = std::stof(t);
				else if (iterator == 11)
					this->p1Time = std::stol(t);
				p1Data = false;
			}
			else
			{
				if (iterator < 10)
					this->assignDataByIterator(iterator, t, this->opponentData);
				else if (iterator == 10)
					this->p2Pts = std::stof(t);
				else if (iterator == 11)
					this->p2Time = std::stol(t);
				iterator++;
				p1Data = true;
			}
		}
	}
	
	////////////////////////////////////////////////////////////
	void GameOverState::placeLabelsWithVals()
	{
		this->timeSpentLabel.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
		this->timeSpentLabel.setCharacterSize(72.f);
		this->timeSpentLabel.setString("Time");
		this->timeSpentLabel.setFillColor(sf::Color::Black);

		ArktisEngine::CenterHorizontally(this->timeSpentLabel, this->_data->settings, 10.f);

		this->positionRow(this->scoreLabel, this->p1Score, this->p2Score, "Final Score", std::to_string(p1Pts), std::to_string(p2Pts), 72.f, 20.f);

		this->positionRow(this->linesLabel, this->p1Lines, this->p2Lines, "Lines", std::to_string(playerLines), std::to_string(enemyLines), 72.f, 30.f);
		
		this->positionRow(this->eloLabel, this->p1Elo, this->p2Elo, "ELO", std::to_string(this->_data->userData.elo), std::to_string(this->opponentData.elo), 72.f, 40.f);

		this->positionRow(this->unrankedWinsLabel, this->p1UnrWins, this->p2UnrWins, "Unranked Wins", std::to_string(this->_data->userData.unrankedWins), std::to_string(this->opponentData.unrankedWins), 72.f, 50.f);

		this->positionRow(this->rankedWinsLabel, this->p1RanWins, this->p2RanWins, "Ranked Wins", std::to_string(this->_data->userData.rankedWins), std::to_string(this->opponentData.rankedWins), 72.f, 60.f);
	}

	////////////////////////////////////////////////////////////
	void GameOverState::drawLabels(sf::RenderWindow &rw, sf::Text &rowHeader, sf::Text &p1Val, sf::Text &p2Val)
	{
		rw.draw(rowHeader);
		rw.draw(p1Val);
		rw.draw(p2Val);
	}

	////////////////////////////////////////////////////////////
	void GameOverState::positionRow(sf::Text &rowHeader, sf::Text &p1Val, sf::Text &p2Val, const std::string hStr, const std::string p1Str, const std::string p2Str, const float hCharSize, const float percHeight)
	{
		this->labelDataInit(rowHeader, this->_data->assets.GetFont(UI_FONT_NAME), hStr, hCharSize, percHeight);
		p1Val.setCharacterSize(rowHeader.getCharacterSize());
		p2Val.setCharacterSize(rowHeader.getCharacterSize());
		
		p1Val.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
		p2Val.setFont(this->_data->assets.GetFont(UI_FONT_NAME));

		p1Val.setString(p1Str);
		p2Val.setString(p2Str);

		p1Val.setFillColor(sf::Color::Black);
		p2Val.setFillColor(sf::Color::Black);
		
		ArktisEngine::CenterHorizontallyInArea(p1Val, this->_data->settings.width/2.f, percHeight);
		ArktisEngine::CenterHorizontallyInArea(p2Val, this->_data->settings.width / 2.f, percHeight);
	
		p1Val.move(0.f, this->_data->settings.height * percHeight / 100.f);
		p2Val.move(this->_data->settings.width/2.f, this->_data->settings.height * percHeight / 100.f);
		rowHeader.move(0.f, this->_data->settings.height * percHeight / 100.f);
	}

	////////////////////////////////////////////////////////////
	void GameOverState::labelDataInit(sf::Text &label, const sf::Font &font, const std::string str, const float charSize, const float percHeight)
	{
		label.setFont(font);
		label.setString(str);
		label.setCharacterSize(charSize);
		label.setFillColor(sf::Color::Black);
		ArktisEngine::CenterHorizontally(label, this->_data->settings, percHeight);
	}

}
