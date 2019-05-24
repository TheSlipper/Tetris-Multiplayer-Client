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
#include "GameState.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    GameState::GameState(ArktisEngine::GameDataRef data)
	: _data(data),
	networkingThread(&GameState::handleNetworking, this)
    {
    }

	////////////////////////////////////////////////////////////
	GameState::GameState(ArktisEngine::UserData opponentData, ArktisEngine::GameDataRef data)
	: _data(data),
	networkingThread(&GameState::handleNetworking, this)
	{
		this->opponentData = opponentData;
	}
    
    ////////////////////////////////////////////////////////////
    void GameState::Init()
    {
        srand(time(0));
        const std::string test = GAME_SONG_PATH;
		if (!this->backgroundMusic.openFromFile(test))
			exit(0);
        this->backgroundMusic.play();
        this->backgroundMusic.setVolume(100);
        this->backgroundMusic.setLoop(true);
        this->_data->assets.LoadTexture(TILES_NAME, TILES_PATH);
        this->_data->assets.LoadTexture(GAME_BG_NAME, GAME_BG_PATH);
        this->_data->assets.LoadTexture(FRAME_NAME, FRAME_PATH);
        this->setUpLabels();
        this->frame.setTexture(this->_data->assets.GetTexture(FRAME_NAME));
        ArktisEngine::ScaleSprToDims(this->frame, this->_data->settings.width, this->_data->settings.height);
        this->s.setTexture(this->_data->assets.GetTexture(TILES_NAME));
        float tileSetWidth = this->_data->settings.width * 1100.f / 3840.f, tileSetHeight = this->_data->settings.height * 138.f / 2160.f;
        this->tileWidth = tileSetWidth / 8.0f;
        this->tileHeight = tileSetHeight;
        ArktisEngine::ScaleSprToDims(this->s, tileSetWidth, tileSetHeight);
        this->background.setTexture(this->_data->assets.GetTexture(GAME_BG_NAME));
        ArktisEngine::ScaleSprToDims(this->background, this->_data->settings.width, this->_data->settings.height);
		this->networkingThread.launch();
	}
    
    ////////////////////////////////////////////////////////////
    void GameState::HandleInput()
    {
        if (!this->_data->window.hasFocus())
            return;
        sf::Event event;
        float time = this->gameClock.getElapsedTime().asSeconds();
        gameClock.restart();
        this->timer += time;
        
        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->messaging.DisconnectSocket();
                this->_data->window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Up:
                        this->rotate = true;
                        break;
                    case sf::Keyboard::Left:
                        this->directionX = -1;
                        break;
                    case sf::Keyboard::Right:
                        this->directionX = 1;
                        break;
                    default:
                        break;
                }
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            this->delay = 0.05f;
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::Update(float dt)
    {
        this->timeText.setString("Time Spent\r\n" + this->timeSpent());
		if (this->p1LostGame && p2LostGame)
		{
			this->backgroundMusic.stop();
			this->_data->machine.AddState((ArktisEngine::StateRef) new HomeScreenState(this->_data), true);
		}
		else if (this->p1LostGame)
			return;
		else if (p1LostGame == false)
        {
            //// <- Move -> ///
            this->move();
            
            //////Rotate//////
            if (this->rotate)
                this->rotation();
            
            ///////Tick//////
            this->tick();
            
            ///////check lines//////////
            this->checkLines();
            
            this->directionX = 0; this->rotate = 0; this->delay = baseDelay;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::White);

        this->_data->window.draw(background);
        
		this->drawFields();
        
        this->_data->window.draw(this->frame);
        
        this->drawLabels();
        
        this->_data->window.display();
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::drawLabels()
    {
        this->_data->window.draw(this->p1UserName);
        this->_data->window.draw(this->p2UserName);
        
        this->_data->window.draw(this->eloText);
        this->_data->window.draw(this->p1Elo);
        this->_data->window.draw(this->p2Elo);
        
        this->_data->window.draw(this->ptsText);
        this->_data->window.draw(this->p1Pts);
        this->_data->window.draw(this->p2Pts);
        
        this->_data->window.draw(this->linesText);
        this->_data->window.draw(this->p1Lines);
        this->_data->window.draw(this->p2Lines);
        
        this->_data->window.draw(this->delayText);
        this->_data->window.draw(this->p1Delay);
        this->_data->window.draw(this->p2Delay);
        
        this->_data->window.draw(this->timeText);

		this->_data->window.draw(p1GameOver);
		this->_data->window.draw(p2GameOver);
    }

	////////////////////////////////////////////////////////////
	void GameState::drawFields()
	{
		const float horizontalPadding = this->_data->settings.width * 11.25f / 100.f; // -25.f
		const float oppHorizontalPadding = this->_data->settings.width * 67.5f / 100.f;

		const float verticalPadding = this->_data->settings.height * 14.25f / 100.f;
		const float tileSizeWPaddingVer = this->tileWidth - (this->_data->settings.width * 50.f / 3840.f);
		const float tileSizeWPaddingHor = this->tileWidth - (this->_data->settings.width * 54.f / 3840.f);

		const sf::Vector2f tileScaleVec(1.25, 1.25);

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (this->field[i][j] != 0)
				{
					this->s.setTextureRect(sf::IntRect(this->field[i][j] * this->tileWidth, 0, this->tileWidth, this->tileHeight));
					this->s.setPosition(j * tileSizeWPaddingHor + horizontalPadding, i * tileSizeWPaddingVer + verticalPadding);
					this->_data->window.draw(s);
				}

				if (this->opponentField[i][j] != 0)
				{
					this->s.setTextureRect(sf::IntRect(this->opponentField[i][j] * this->tileWidth, 0, this->tileWidth, this->tileHeight));
					this->s.setPosition(j * tileSizeWPaddingHor + oppHorizontalPadding, i * tileSizeWPaddingVer + verticalPadding);
					this->_data->window.draw(s);
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (!this->p1LostGame)
			{
				this->s.setTextureRect(sf::IntRect(colorNum * tileWidth, 0, tileWidth, tileHeight));
				this->s.setPosition(a[i].x * tileSizeWPaddingHor + horizontalPadding, a[i].y * tileSizeWPaddingVer + verticalPadding);
				this->_data->window.draw(s);
			}

			this->s.setTextureRect(sf::IntRect(colorNum * tileWidth, 0, tileWidth, tileHeight));
			this->s.setPosition(opponentA[i].x * tileSizeWPaddingHor + oppHorizontalPadding, opponentA[i].y * tileSizeWPaddingVer + verticalPadding);
			this->_data->window.draw(s);
		}
	}
    
    ////////////////////////////////////////////////////////////
    void GameState::positionRowOfLabels(sf::Text &rowName, sf::Text &p1, sf::Text &p2, float heightPrct, std::string rowStr, std::string p1String, std::string p2String)
    {
        rowName.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        p1.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        p2.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        
        rowName.setString(rowStr);
        p1.setString(p1String);
        p2.setString(p2String);
        
        rowName.setFillColor(sf::Color::Black);
        p1.setFillColor(sf::Color::Black);
        p2.setFillColor(sf::Color::Black);

		rowName.setCharacterSize(this->_data->settings.height * 60.f / 2160.f);
		p1.setCharacterSize(this->_data->settings.height * 60.f / 2160.f);
		p2.setCharacterSize(this->_data->settings.height * 60.f / 2160.f);

        
        ArktisEngine::CenterHorizontally(rowName, this->_data->settings, ArktisEngine::GetYPosRelToScreenByPrct(heightPrct, this->_data->settings));
        ArktisEngine::CenterHorizontally(p1, this->_data->settings, ArktisEngine::GetYPosRelToScreenByPrct(heightPrct, this->_data->settings));
        ArktisEngine::CenterHorizontally(p2, this->_data->settings, ArktisEngine::GetYPosRelToScreenByPrct(heightPrct, this->_data->settings));
        
        p1.move(-1 * ArktisEngine::GetXPosRelToScreenByPrct(10.f, this->_data->settings), 0.f);
        p2.move(ArktisEngine::GetXPosRelToScreenByPrct(10.f, this->_data->settings), 0.f);
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::setUpLabels()
    {
        this->p1UserName.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        this->p1UserName.setString(this->_data->userData.username);
		this->p1UserName.setCharacterSize(this->_data->settings.height * 60.f / 2160.f);
        this->p1UserName.setPosition(ArktisEngine::GetPosRelToScreenByPrct(19.5f, 15.f, this->_data->settings));
        this->p1UserName.setFillColor(sf::Color::White);

        this->p2UserName.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        this->p2UserName.setString(this->opponentData.username);
		this->p2UserName.setCharacterSize(this->_data->settings.height * 60.f / 2160.f);
        this->p2UserName.setPosition(ArktisEngine::GetPosRelToScreenByPrct(71.625f, 15.f, this->_data->settings));
        this->p2UserName.setFillColor(sf::Color::White);
        
        this->positionRowOfLabels(this->eloText, this->p1Elo, this->p2Elo, 40.f, "ELO", 
			std::to_string(this->_data->userData.elo), std::to_string(this->opponentData.elo));
        this->positionRowOfLabels(this->ptsText, this->p1Pts, this->p2Pts, 50.f, "Points", "0", "0");
        this->positionRowOfLabels(this->linesText, this->p1Lines, this->p2Lines, 60.f, "Lines", "0", "0");
        this->positionRowOfLabels(this->delayText, this->p1Delay, this->p2Delay, 70.f, "Delay", ArktisEngine::to_string_with_precision<float>(this->delay, 3), ArktisEngine::to_string_with_precision<float>(this->delay, 3));
        
        this->timeText.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        this->timeText.setString("Time Spent\r\n" + this->timeSpent());
        this->timeText.setFillColor(sf::Color::Black);
        ArktisEngine::CenterHorizontally(this->timeText, this->_data->settings, ArktisEngine::GetYPosRelToScreenByPrct(80.f, this->_data->settings));

		this->p1GameOver.setCharacterSize(this->_data->settings.height * 60.f / 2160.f);
		this->p1GameOver.setFillColor(sf::Color(0, 0, 0, 0));
		this->p1GameOver.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
		this->p1GameOver.setString("[GAME OVER]");
		this->p1GameOver.setPosition(this->_data->settings.height * 35.f / 100.f, this->_data->settings.width * 20.f / 100.f);

		this->p2GameOver.setCharacterSize(this->_data->settings.height * 60.f / 2160.f);
		this->p2GameOver.setFillColor(sf::Color(0, 0, 0, 0));
		this->p2GameOver.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
		this->p2GameOver.setString("[GAME OVER]");
		this->p2GameOver.setPosition(this->_data->settings.height * 40.f / 100.f, this->_data->settings.width * 60.f / 100.f);
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::move()
    {
        for (int i = 0; i < 4; i++)
        {
            this->b[i] = this->a[i];
            this->a[i].x += this->directionX;
        }
        
        if (!this->check())
        {
            for (int i = 0; i < 4; i++)
                this->a[i] = b[i];
        }
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::rotation()
    {
        Point p = this->a[1];     //center of rotation
        for (int i = 0; i < 4; i++)
        {
            int x = this->a[i].y - p.y;
            int y = this->a[i].x - p.x;
            this->a[i].x = p.x - x;
            this->a[i].y = p.y + y;
        }
        if (!check())
        {
            for (int i = 0; i < 4; i++)
                this->a[i]= this->b[i];
        }
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::tick()
    {
		if (this->p1LostGame)
			return;
        if (this->timer > this->delay)
        {
            for (int i = 0; i < 4; i++)
            {
                this->b[i] = this->a[i];
                this->a[i].y += 1;
            }
            
            if (!this->check())
            {
                if (this->isItGameOver() && !p1LostGame)
                {
                    this->p1LostGame = true;
					this->p1GameOver.setFillColor(sf::Color::Red);
                    return;
                }
                for (int i = 0; i < 4; i++)
                    this->field[this->b[i].y][this->b[i].x] = colorNum;
                this->colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0; i < 4; i++)
                {
                    this->a[i].x = figures[n][i] % 2;
                    this->a[i].y = figures[n][i] / 2;
                }
            }
            
			// this->sendFieldData();
			// this->receiveFieldData();
			this->timer = 0;
        }
    }
    
    ////////////////////////////////////////////////////////////
    bool GameState::check()
    {
        for (int i = 0; i < 4; i++)
        {
            if (this->a[i].x < 0 || a[i].x >= N || a[i].y >= M)
                return 0;
            else if (this->field[this->a[i].y][this->a[i].x])
                return 0;
        }
        
        return 1;
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::checkLines()
    {
        int k = M - 1;
        for (int i = M - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < N; j++)
            {
                if (this->field[i][j])
                    count++;
                this->field[k][j] = this->field[i][j];
            }
            if (count < N)
                k--;
            if (count == N)
            {
                int ptCount = std::stoi(this->p1Pts.getString().toAnsiString());
                int lineCount = std::stoi(this->p1Lines.getString().toAnsiString());
                ptCount += 1000 + 0.7f / this->baseDelay * 100;
                lineCount++;
                this->baseDelay -= 0.0125;
                this->delay = this->baseDelay;
                this->p1Pts.setString(std::to_string(ptCount));
                this->p1Lines.setString(std::to_string(lineCount));
                this->p1Delay.setString(ArktisEngine::to_string_with_precision<float>(this->baseDelay, 3));
            }
        }
    }
    
    ////////////////////////////////////////////////////////////
    bool GameState::isItGameOver()
    {
        for (int i = 0; i < N; i++)
        {
            if (this->field[0][i] != 0 || this->field[0][i])
                return true;
        }
        return false;
    }
    
    ////////////////////////////////////////////////////////////
    std::string GameState::timeSpent()
    {
        int minutes = (int)this->timeSpentClock.getElapsedTime().asSeconds() / 60;
        int seconds = (int)this->timeSpentClock.getElapsedTime().asSeconds() % 60;
        int milliseconds = (int)this->timeSpentClock.getElapsedTime().asMilliseconds() - ((int)this->timeSpentClock.getElapsedTime().asMilliseconds() / 1000) * 1000;
        
        return std::to_string(minutes) + " : " + std::to_string(seconds) + " : " + std::to_string(milliseconds);
    }

	////////////////////////////////////////////////////////////
	void GameState::handleNetworking()
	{
		const static sf::Time time = sf::seconds(1.f);
		while (true)
		{
			if (this->p1LostGame && this->p2LostGame)
			{
				return;
			}
			sf::sleep(time);
			this->sendFieldData();
			this->receiveFieldData();
		}
	}

	////////////////////////////////////////////////////////////
	void GameState::sendFieldData()
	{
		std::stringstream ss;
		ss << "P_F_DATA " << std::to_string(this->_data->userData.matchId) << " ";

		if (this->p1LostGame)
			ss << "L ";
		else
		{
			for (int i = 0; i < GRID_HEIGHT; i++)
			{
				for (int j = 0; j < GRID_WIDTH; j++)
					ss << std::to_string(this->field[i][j]);
				ss << 'N';
			}

			for (int i = 0; i < 4; i++)
			{
				ss << a[i].x << a[i].y;
				ss << b[i].x << b[i].y;
			}
		}

		ss << this->p1Pts.getString().toAnsiString() << " " << this->p1Lines.getString().toAnsiString() << " " << this->p1Delay.getString().toAnsiString();

		this->_data->messaging.SendStringData(ss.str());
	}

	////////////////////////////////////////////////////////////
	void GameState::receiveFieldData()
	{
		const std::string response = this->_data->messaging.GetStringResponse();
		int charCount = 0;

		if (response[0] == 'L')
		{
			this->p2LostGame = true;
			this->p2GameOver.setFillColor(sf::Color::Red);
			charCount += 2;
		}
		else
		{
			for (int i = 0; i < GRID_HEIGHT; i++)
			{
				for (int j = 0; j <= GRID_WIDTH; j++, charCount++)
				{
					if (response[charCount] != 'N')
						this->opponentField[i][j] = (int)response[charCount] - 48;
				}
			}

			for (int i = 0; i < 4; i++, charCount++)
			{
				opponentA[i].x = (int)response[charCount] - 48;
				charCount++;
				opponentA[i].y = (int)response[charCount] - 48;
				charCount++;
				opponentB[i].x = (int)response[charCount] - 48;
				charCount++;
				opponentB[i].y = (int)response[charCount] - 48;
			}
		}

		std::string p2Data = response.substr(charCount);
		ArktisEngine::StringTokenizer tokenizer{p2Data};
		
		int i = 0;
		for (const std::string &t : tokenizer)
		{
			switch (i)
			{
			case 0:
				this->p2Pts.setString(t);
				break;
			case 1:
				this->p2Lines.setString(t);
				break;
			case 2:
				this->p2Delay.setString(t);
				break;
			}
		}
	}
}
