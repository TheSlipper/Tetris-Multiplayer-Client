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
        ////////////////////////////////////////////////////////////
        /// \brief Assigns data to a UserData structure to the specific
        ///          struct member based on the given iterator
        ///
        ////////////////////////////////////////////////////////////
		void assignDataByIterator(int &iterator, const std::string &val, ArktisEngine::UserData &data);

        ////////////////////////////////////////////////////////////
        /// \brief Parses end game data
        ///
        ////////////////////////////////////////////////////////////
		void parseResponseData(const std::string &data);

        ////////////////////////////////////////////////////////////
        /// \brief Positions all of the labels with its values
        ///
        ////////////////////////////////////////////////////////////
		void placeLabelsWithVals();

        ////////////////////////////////////////////////////////////
        /// \brief Draws all of the labels to the screen
        ///
        ////////////////////////////////////////////////////////////
		void drawLabels(sf::RenderWindow &rw, sf::Text &rowHeader, sf::Text &p1Val, sf::Text &p2Val);

        ////////////////////////////////////////////////////////////
        /// \brief Positions all of the label contents in a given order
        ///         specified by the implementation of this function
        ///
        /// \param rowHeader header/name of the row
        ///
        /// \param p1Val content of first player's label
        ///
        /// \param p2Val content of second player's label
        ///
        /// \param hStr std::string content of the row header
        ///
        /// \param p1Str std::string content of the p1 label
        ///
        /// \param p2Str std::string content of the p2 label
        ///
        /// \param hCharSize specifies the header character size
        ///
        /// \param topMrgnPrct specifies top margin of the row in percents
        ///
        ////////////////////////////////////////////////////////////
		void positionRow(sf::Text &rowHeader, sf::Text &p1Val, sf::Text &p2Val, const std::string hStr, const std::string p1Str, const std::string p2Str, const float hCharSize, const float percHeight);

        ////////////////////////////////////////////////////////////
        /// \brief Initializes single label's data (used in positionRow function)
        ///
        ////////////////////////////////////////////////////////////
		void labelDataInit(sf::Text &label, const sf::Font &font, const std::string str, const float charSize, const float percHeight);

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
