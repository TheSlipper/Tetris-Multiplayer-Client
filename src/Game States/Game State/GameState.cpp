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

// TODO: DELET THIS
#include <iostream>

namespace States
{
    ////////////////////////////////////////////////////////////
    GameState::GameState(ArktisEngine::GameDataRef data) : _data(data)
    {
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::Init()
    {
        srand(time(0));
        this->_data->assets.LoadTexture(TILES_NAME, TILES_PATH);
        this->_data->assets.LoadTexture(GAME_BG_NAME, GAME_BG_PATH);
        this->_data->assets.LoadTexture(FRAME_NAME, FRAME_PATH);
        this->frame.setTexture(this->_data->assets.GetTexture(FRAME_NAME));
        ArktisEngine::ScaleSprToDims(this->frame, this->_data->settings.width, this->_data->settings.height);
        this->s.setTexture(this->_data->assets.GetTexture(TILES_NAME));
        float tileSetWidth = this->_data->settings.width * 970.f / 3840.f, tileSetHeight = this->_data->settings.height * 121.f / 2160.f;
        this->tileWidth = tileSetWidth / 8.0f;
        this->tileHeight = tileSetHeight;
        ArktisEngine::ScaleSprToDims(this->s, tileSetWidth, tileSetHeight);
        this->background.setTexture(this->_data->assets.GetTexture(GAME_BG_NAME));
        ArktisEngine::ScaleSprToDims(this->background, this->_data->settings.width, this->_data->settings.height);
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::HandleInput()
    {
        sf::Event event;
        float time = this->gameClock.getElapsedTime().asSeconds();
        gameClock.restart();
        this->timer += time;
        
        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
                this->_data->window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Up:
                        this->rotate = true;
                        break;
                    case sf::Keyboard::Left:
                        this->dx = -1;
                        break;
                    case sf::Keyboard::Right:
                        this->dx = 1;
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
        if (lostGame == false)
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
            
            this->dx = 0; this->rotate = 0; this->delay = BASE_DELAY;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::White);
        this->_data->window.draw(background);
        
        float horizontal_padding = -1 * (this->_data->settings.height * 36.f / 2160.f); // -25.f
        float vertical_padding = -1 * (this->_data->settings.height * 35.f / 2160.f);
        
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (this->field[i][j] == 0)
                    continue;
                this->s.setTextureRect(sf::IntRect(this->field[i][j] * this->tileWidth, 0, this->tileWidth, this->tileHeight)); // maybe delete -1
                this->s.setPosition(j * (this->tileWidth + horizontal_padding), i * (this->tileHeight + vertical_padding));
                this->s.move(X_OFFSET, Y_OFFSET);
                
                this->_data->window.draw(s);
            }
        }
        
        for (int i = 0; i < 4; i++)
        {
            this->s.setTextureRect(sf::IntRect(colorNum * tileWidth, 0, tileWidth, tileHeight));
            this->s.setPosition(a[i].x * (tileHeight + horizontal_padding), a[i].y * (tileHeight + vertical_padding));
            this->s.move(X_OFFSET, Y_OFFSET);
            this->_data->window.draw(s);
        }
        
        this->_data->window.draw(this->frame);
        
        this->_data->window.display();
    }
    
    ////////////////////////////////////////////////////////////
    void GameState::move()
    {
        for (int i = 0; i < 4; i++)
        {
            this->b[i] = this->a[i];
            this->a[i].x += this->dx;
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
        if (this->timer > this->delay)
        {
            for (int i = 0; i < 4; i++)
            {
                this->b[i] = this->a[i];
                this->a[i].y += 1;
            }
            
            if (!this->check())
            {
                if (this->isItGameOver() && !lostGame)
                {
                    this->lostGame = true;
                    std::cout << "Game over" << std::endl;
                    this->_data->machine.AddState((ArktisEngine::StateRef)new HomeScreenState(this->_data), true);
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
        }
    }
    
    bool GameState::isItGameOver()
    {
        for (int i = 0; i < N; i++)
        {
            if (this->field[0][i] != 0 || this->field[0][i])
                return true;
        }
        return false;
    }
}
