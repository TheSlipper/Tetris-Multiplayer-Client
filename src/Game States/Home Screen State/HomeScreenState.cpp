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
#include "HomeScreenState.hpp"

namespace States
{
    ////////////////////////////////////////////////////////////
    HomeScreenState::HomeScreenState(ArktisEngine::GameDataRef data) : _data(data)
    {
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::Init()
    {
        this->setUserData();
        this->loadAvatarTextures();
        this->setUpNewsSection();
        this->setUpAccHUD();
        this->setUpPlayButtons();
        this->loadArticles();
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->messaging.DisconnectSocket();
                this->_data->window.close();
            }
            else if (sf::Event::MouseButtonPressed == event.type)
            {
                if (this->_data->input.IsButtonClicked(*this->_playNormal, sf::Mouse::Left, this->_data->window))
                    this->_data->machine.AddState((ArktisEngine::StateRef)new LoadingScreenState(this->_data), true);
            }
        }
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::Update(float dt)
    {
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);

        this->_data->window.draw(this->bgStylizedImage);

        this->_data->window.draw(*this->_playNormal);

        this->_data->window.draw(*this->_playRanked);

        this->_data->window.draw(*this->_nicknameBox);

        this->_data->window.draw(*this->_tetrominoPtsBlock);

        this->_data->window.draw(this->avatar);

        this->_data->window.draw(this->gameLogo);

        for (const sf::Text &txt : this->articleHeaders)
            this->_data->window.draw(txt);

        for (const sf::Text &txt : this->articleContents)
            this->_data->window.draw(txt);
        
        for (const sf::Text &txt : this->articleAuthors)
            this->_data->window.draw(txt);
        
        for (const sf::Text &txt : this->articleDates)
            this->_data->window.draw(txt);

        this->_data->window.display();
    }
    
    ////////////////////////////////////////////////////////////
    void HomeScreenState::setUserData()
    {
        this->_data->messaging.SendStringData("GET_USER_DATA " + this->_data->userData.username);
        std::string response = this->_data->messaging.GetStringResponse();
        ArktisEngine::StringTokenizer tokenizer{response};
        int i = 0;
        for (const auto &t : tokenizer)
        {
            switch(i)
            {
                case 5:
                    this->_data->userData.elo = std::stoi(t);
                    break;
                case 6:
                    this->_data->userData.privilegeGroup = std::stoi(t);
                    break;
                case 7:
                    this->_data->userData.unrankedWins = std::stoi(t);
                    break;
                case 8:
                    this->_data->userData.unrankedLosses = std::stoi(t);
                    break;
                case 9:
                    this->_data->userData.rankedWins = std::stoi(t);
                    break;
                case 10:
                    this->_data->userData.rankedLosses = std::stoi(t);
                    break;
                case 11:
                    this->_data->userData.tetrominoPoints = std::stoll(t);
                    break;
                case 12:
                    this->_data->userData.timePlayed = std::stoll(t);
                    break;
                default:
                    break;
            }
            i++;
        }
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::setUpPlayButtons()
    {
        this->_playNormal = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), "Play");
        this->_playRanked = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), "Play Ranked");
        
        sf::Vector2f dims(600.f * this->_data->settings.width / 3840.f, 200.f * this->_data->settings.height / 2160.f);
        this->_playNormal->SetSize(dims);
        this->_playRanked->SetSize(dims);
        this->_playRanked->SetPosition(this->_data->settings.width * 30.f / 100.f, this->_data->settings.height * 4.f / 100.f);
        this->_playNormal->SetPosition(this->_data->settings.width * 50.f / 100.f, this->_data->settings.height * 4.f / 100.f);
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::setUpAccHUD()
    {
        this->_data->assets.LoadTexture(TETRISMP_BARE_LOGO_NAME, TETRISMP_BARE_LOGO_PATH);
        this->gameLogo.setTexture(this->_data->assets.GetTexture(TETRISMP_BARE_LOGO_NAME));
        float logoWidth = this->_data->settings.width * 500.f / 3840.f, logoHeight = this->_data->settings.height * 442.30f / 2160.f;
        ArktisEngine::ScaleSprToDims(this->gameLogo, logoWidth, logoHeight);
        this->gameLogo.move(50.f, 2.5f);
        this->_nicknameBox = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), this->_data->userData.username);
        this->_tetrominoPtsBlock = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME),
                                                                std::to_string(this->_data->userData.tetrominoPoints) + " Tetromino Points");

		this->_nicknameBox->SetPosition(this->_data->settings.width * 2985.f / 3820.f, this->_data->settings.height * 4.f / 100.f);
		this->_nicknameBox->SetSize(this->_data->settings.width * 597.f / 3820.f, this->_data->settings.height * 100.f / 2160.f);
		this->_nicknameBox->SetCharacterSize(this->_data->settings.width * 32.f / 2160.f);

        this->_tetrominoPtsBlock->SetPosition(sf::Vector2f(this->_nicknameBox->GetPosition().x, this->_nicknameBox->GetPosition().y + this->_nicknameBox->GetGlobalBounds().height));
		this->_tetrominoPtsBlock->SetSize(this->_data->settings.width * 597.f / 3820.f, this->_data->settings.height * 100.f / 2160.f);
		this->_tetrominoPtsBlock->SetCharacterSize(this->_data->settings.width * 32.f / 2160.f);
        this->_nicknameBox->SetRrsFillColor(sf::Color(0, 0, 0, 50));
        this->avatar.setTexture(this->_data->assets.GetTexture(AVATAR_1_NAME));
        auto nicknameBounds = this->_nicknameBox->GetGlobalBounds();
        // height = nicknameBounds.height * 2;
        float height = nicknameBounds.height * 2;
        ArktisEngine::ScaleSprToDims(this->avatar, height, height);
        this->avatar.setPosition(nicknameBounds.left - this->avatar.getGlobalBounds().width, nicknameBounds.top);
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::setUpNewsSection()
    {
        this->_data->assets.LoadTexture(HOME_BG_NAME, HOME_BG_PATH);
        this->bgStylizedImage.setTexture(this->_data->assets.GetTexture(HOME_BG_NAME));
        ArktisEngine::ScaleSprToDims(this->bgStylizedImage, this->_data->settings.width, this->_data->settings.height);
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::loadAvatarTextures()
    {
        this->_data->assets.LoadTexture(AVATAR_1_NAME, AVATAR_1_PATH);
        this->_data->assets.LoadTexture(AVATAR_2_NAME, AVATAR_2_PATH);
        this->_data->assets.LoadTexture(AVATAR_3_NAME, AVATAR_3_PATH);
    }

    ////////////////////////////////////////////////////////////
    void HomeScreenState::loadArticles()
    {
        this->_data->messaging.SendStringData("GET_UPDATE_LOGS");
        std::string response = this->_data->messaging.GetStringResponse();
        boost::char_separator<char> sep{"\r\n"};
        ArktisEngine::StringTokenizer tokenizer{response, sep};
        int i = -1;
        for (const std::string &token : tokenizer)
        {
            switch (i)
            {
                case 0:
                    this->addArticleHeader(token);
                    break;
                case 1:
                    this->addArticleContent(token);
                    break;
                case 2:
                    this->addArticleAuthor(token);
                    break;
                case 3:
                    this->addArticleDate(token);
                    break;
                case -1:
                    const std::string codename = "SEND_UPDATE_LOGS";
                    if (codename.compare(token) != 0)
                        return;
                    break;
            }
            i = (i == 3) ? 0 : i + 1;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void HomeScreenState::addArticleHeader(std::string header)
    {
        sf::Text txt;
        txt.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        txt.setString(header);
        txt.setCharacterSize(this->_nicknameBox->GetGlobalBounds().height);
        if (this->articleHeaders.empty())
            txt.setPosition(20.f, this->_data->settings.height * 457.f / 2160.f);
        else
        {
            const auto prevGlobalBounds = this->articleDates[this->articleDates.size() - 1].getGlobalBounds();
            txt.setPosition(prevGlobalBounds.left, prevGlobalBounds.top + prevGlobalBounds.height + 30.f); // SCALE THIS
        }
        txt.setFillColor(sf::Color(0, 0, 0));
        this->articleHeaders.push_back(txt);
    }
    
    ////////////////////////////////////////////////////////////
    void HomeScreenState::addArticleContent(std::string content)
    {
        sf::Text txt;
        const auto prevGlobalBounds = this->articleHeaders[this->articleHeaders.size() - 1].getGlobalBounds();
        std::string copiedContent = content;
        for (int i = 0; i < copiedContent.length(); i++)
        {
            if (i % 135 == 0)
                copiedContent.insert(i, "\r\n");
        }
        txt.setString(copiedContent);
        txt.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        txt.setCharacterSize(this->_nicknameBox->GetGlobalBounds().height / 2.0f);
        txt.setFillColor(sf::Color::Black);
        txt.setPosition(prevGlobalBounds.left, prevGlobalBounds.top + prevGlobalBounds.height + 3.f); // SCALE THIS (.5f)
        this->articleContents.push_back(txt);
    }
    
    ////////////////////////////////////////////////////////////
    void HomeScreenState::addArticleAuthor(std::string author)
    {
        sf::Text txt;
        const auto prevGlobalBounds = this->articleContents[this->articleContents.size() - 1].getGlobalBounds();
        txt.setString("Made by: " + author);
        txt.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        txt.setCharacterSize(this->_nicknameBox->GetGlobalBounds().height / 2.25f); // SCALE THIS or maybe even change 2.25f to something else
        txt.setFillColor(sf::Color::Black);
        txt.setPosition(prevGlobalBounds.left, prevGlobalBounds.top + prevGlobalBounds.height + 5.f);
        this->articleAuthors.push_back(txt);
    }
    
    ////////////////////////////////////////////////////////////
    void HomeScreenState::addArticleDate(std::string date)
    {
        sf::Text txt;
        const auto prevGlobalBounds = this->articleAuthors[this->articleAuthors.size() - 1].getGlobalBounds();
        txt.setString(date);
        txt.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        txt.setCharacterSize(this->_nicknameBox->GetGlobalBounds().height / 2.25f); // SCALE THIS or maybe even change 2.25f to something else
        txt.setFillColor(sf::Color::Black);
        txt.setPosition(prevGlobalBounds.left, prevGlobalBounds.top + prevGlobalBounds.height + 3.f);
        this->articleDates.push_back(txt);
    }
}
