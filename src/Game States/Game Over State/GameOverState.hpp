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
#include "../../Game Engine/Misc Utils/MiscUtils.hpp"
#include "../State/State.hpp"
#include "../../Game States/Home Screen State/HomeScreenState.hpp"
#include "../../Game Engine/GameData/GameData.hpp"
#include "../../Definitions/FONT_DEFINITIONS.h"

namespace States
{
	////////////////////////////////////////////////////////////
	/// \brief Loading Screen State
	///
	////////////////////////////////////////////////////////////
	class GameOverState : public State
	{
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// \param opponentData data of the opponent
		///
		/// \param data pointer to the game's crucial data
		///
		////////////////////////////////////////////////////////////
		GameOverState(ArktisEngine::UserData opponentData, ArktisEngine::GameDataRef data);

		////////////////////////////////////////////////////////////
		/// \brief Initialization of the state
		///
		////////////////////////////////////////////////////////////
		void Init();

		////////////////////////////////////////////////////////////
		/// \brief Handles scene-specific user input
		///
		////////////////////////////////////////////////////////////
		void HandleInput();

		////////////////////////////////////////////////////////////
		/// \brief Updates the scene (call the animation or physics
		///         methods here)
		///
		////////////////////////////////////////////////////////////
		void Update(float dt);

		////////////////////////////////////////////////////////////
		/// \brief Draws to the screen
		///
		////////////////////////////////////////////////////////////
		void Draw(float dt);

	private:
		void assignDataByIterator(int &iterator, const std::string &val, ArktisEngine::UserData &data);

		void parseResponseData(const std::string &data);

		void placeLabelsWithVals();

		void drawLabels(sf::RenderWindow &rw, sf::Text &rowHeader, sf::Text &p1Val, sf::Text &p2Val);

		void positionRow(sf::Text &rowHeader, sf::Text &p1Val, sf::Text &p2Val, std::string hStr, std::string p1Str, std::string p2Str, float hCharSize, float percHeight);

		void labelDataInit(sf::Text &label, sf::Font &font, std::string str, float charSize, float percHeight);

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		int p1Pts, p2Pts;

		int playerLines, enemyLines;

		sf::Text timeSpentLabel;

		sf::Text scoreLabel;

		sf::Text linesLabel;

		sf::Text eloLabel;

		sf::Text unrankedWinsLabel;

		sf::Text rankedWinsLabel;

		sf::Text p1Score, p2Score;

		sf::Text p1Lines, p2Lines;

		sf::Text p1Elo, p2Elo;

		sf::Text p1UnrWins, p2UnrWins;

		sf::Text p1RanWins, p2RanWins;

		long p1Time, p2Time;

		ArktisEngine::UserData opponentData;

		ArktisEngine::GameDataRef _data; ///< Pointer to game's crucial data
	};
}
