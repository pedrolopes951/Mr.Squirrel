#include "Player.hpp"

Player::Player(const std::array<std::string,2>& textures_array,sf::Vector2f position) : m_position(position)
{
    this->InitVariables();
    this->InitTextureSprite(textures_array);

}

void Player::InitVariables()
{
    //TODO
}

void Player::InitTextureSprite(const std::array<std::string, 2>& textures_array)
{
    sf::Texture texture_stop_right;
    sf::Sprite sprite_stop_right;
    // Coordinates of sprite, number of elementes
    int x_axis ; // 3 elemnts
    int y_axis ; // 4 elemnts
    //TODO MAKE REST OF ELEMENTS
    if(texture_stop_right.loadFromFile(std::string(TexturesPATH)+ std::string("Main_Player.png")))
    {
        x_axis = 2;
        y_axis = 1;
        m_texture.insert(std::make_pair(PlayerDir::STILLRIGHT,texture_stop_right));
        sprite_stop_right.setTexture(m_texture[PlayerDir::STILLRIGHT]);
        sprite_stop_right.setTextureRect(sf::IntRect(x_axis*PLAYEDIM,y_axis*PLAYEDIM,PLAYEDIM,PLAYEDIM));
        sprite_stop_right.scale(3,3);
        sprite_stop_right.setPosition(m_position);
        m_sprites.insert(std::make_pair(PlayerDir::STILLRIGHT,sprite_stop_right));


    }
    sf::Texture texture_stop_left;
    if(texture_stop_left.loadFromFile(textures_array[1]))
    {
        m_texture.insert(std::make_pair(PlayerDir::STILLLEFT,texture_stop_left));

    }
    

}

void Player::render(sf::RenderWindow* window)
{
    window->draw(m_sprites.at(PlayerDir::STILLRIGHT));
}

void Player::update(sf::Time& elapsed_time)
{

}

Player::~Player()
{

}

