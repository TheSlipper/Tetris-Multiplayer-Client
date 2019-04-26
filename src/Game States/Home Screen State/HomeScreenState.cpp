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
        //        this->_data->socket.connect("192.168.1.101", 6911); TODO: Enter server IP in the login screen maybe
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
                {
                    this->_data->machine.AddState((ArktisEngine::StateRef)new GameState(this->_data));
                }
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
        
        this->_data->window.draw(*this->_blocksBox);
        
        this->_data->window.draw(this->avatar);
        
        this->_data->window.draw(this->gameLogo);
        
        for (sf::Text txt : this->articleHeaders)
            this->_data->window.draw(txt);
        
        for (sf::Text txt : this->articleContent)
            this->_data->window.draw(txt);
        
        this->_data->window.display();
    }
    
    ////////////////////////////////////////////////////////////
    void HomeScreenState::setUpPlayButtons()
    {
        this->_playNormal = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), "Play");
        this->_playRanked = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), "Play Ranked");
        this->_playNormal->SetSize(sf::Vector2f(300.f, 100.f));
        this->_playRanked->SetSize(sf::Vector2f(300.f, 100.f));
        this->_playRanked->SetPosition(sf::Vector2f(this->avatar.getPosition().x - this->_playNormal->GetGlobalBounds().width -
                                                    (this->_data->settings.width * 5.f / 100.f), this->avatar.getPosition().y));
        this->_playNormal->SetPosition(sf::Vector2f(this->_playRanked->GetPosition().x - this->_playRanked->GetGlobalBounds().width -
                                                    (this->_data->settings.width * 2.5f / 100.f), this->avatar.getPosition().y));
        this->_playRanked->SetSize(sf::Vector2f(300.f, 100.f)); // TODO: Scalable
    }
    
    ////////////////////////////////////////////////////////////
    void HomeScreenState::setUpAccHUD()
    {
        // TODO: Get the nickname by a request to the server
        this->_data->assets.LoadTexture(TETRISMP_BARE_LOGO_NAME, TETRISMP_BARE_LOGO_PATH);
        this->gameLogo.setTexture(this->_data->assets.GetTexture(TETRISMP_BARE_LOGO_NAME));
        // TODO:
//        float width = (this->_data->settings.width * 20.f)/100.f, height = ;
//        ArktisEngine::ScaleSprToDims(this->gameLogo, width, <#float &height#>)
        this->_nicknameBox = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), "Slipper");
        this->_blocksBox = std::make_unique<GameObjects::Button>(this->_data->assets.GetFont(UI_FONT_NAME), "13500 Blocks");
        this->_nicknameBox->SetPosition(sf::Vector2f(1500.f, 50.f));
        this->_blocksBox->SetPosition(sf::Vector2f(this->_nicknameBox->GetPosition().x, this->_nicknameBox->GetPosition().y + this->_nicknameBox->GetGlobalBounds().height));
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
        sf::Text txt;
        txt.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        txt.setString("Hello world! - Welcome to the indev version 0.0.1");
        txt.setCharacterSize(this->_nicknameBox->GetGlobalBounds().height);
        txt.setPosition(20.f, this->_data->settings.height * 457.f / 2160.f);
        txt.setFillColor(sf::Color(0,0,0));
        this->articleHeaders.push_back(txt);
        
        sf::Text txt2;
        txt2.setFont(this->_data->assets.GetFont(UI_FONT_NAME));
        std::string content = "    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut odio nulla, tincidunt non pulvinar ac, consectetur et odio. Praesent viverra varius tortor ut fermentum. Fusce sollicitudin nisi augue, id suscipit ipsum facilisis non. Praesent nec laoreet tellus. Proin suscipit eros sit amet dui sodales, et tempor mauris tempus. Curabitur auctor cursus erat nec egestas. Aenean at quam eros. Integer vitae nisl sapien. Proin non arcu at nulla iaculis bibendum. Etiam tincidunt, orci a semper faucibus, justo neque pretium lorem, ut egestas purus risus vel lectus. Integer lacinia enim interdum, laoreet nisi non, tristique ante.\r\nVivamus euismod velit eros. Etiam lacinia urna nec libero condimentum mattis. Aliquam interdum purus eget orci ultrices, in tempor libero varius. Vestibulum lacus orci, scelerisque in euismod eget, tempor eu risus. Nulla facilisi. Vivamus blandit faucibus imperdiet. Nunc nec tellus imperdiet, volutpat velit eu, suscipit nunc. Nullam porta, tortor at fermentum ornare, ligula dui ornare leo, ultrices venenatis lectus ipsum nec nisi. Cras neque mi, elementum non risus et, dictum laoreet felis. Aenean eget risus semper, pellentesque nunc id, sollicitudin lorem. Fusce nec placerat ex. Ut vitae massa leo. Etiam quis est ut lectus ornare posuere. Pellentesque aliquam elementum diam, a vehicula augue hendrerit sit amet. Proin id turpis ut elit suscipit pretium. Aliquam iaculis sit amet turpis sit amet convallis.";
        for (int i = 0; i < content.length(); i++)
        {
            if (i % 174 == 0)
                content.insert(i, "\r\n");
        }
        
        txt2.setString(content);
        txt2.setCharacterSize(this->_nicknameBox->GetGlobalBounds().height/2.0);
        txt2.setFillColor(sf::Color::Black);
        txt2.setPosition(txt.getPosition().x, txt.getPosition().y + txt.getCharacterSize() + 5.f);
        this->articleContent.push_back(txt2);
    }
}
