#include "Player.hpp"

Player::Player(const std::string& textures_path,sf::Vector2f position) : m_position(position)
{
    this->InitVariables();
    this->InitTextureSprite(textures_path);

}

void Player::InitVariables()
{
    //TODO
}

void Player::InitTextureSprite(const std::string& textures_path)
{
    if(m_texture.loadFromFile(textures_path))
    {
        ParsePlayerSprite(0,0, PlayerDir::STILLLEFT);
        ParsePlayerSprite(0,1, PlayerDir::JUMPLEFT);
        ParsePlayerSprite(0,2, PlayerDir::WALKRIGHTLEFT);
        ParsePlayerSprite(0,3, PlayerDir::LANDRIGHT);
        ParsePlayerSprite(1,0, PlayerDir::WALKLEFTRIGHT);
        ParsePlayerSprite(1,1, PlayerDir::LANDLEFT);
        ParsePlayerSprite(1,2, PlayerDir::WALKRIGHTRIGHT);
        ParsePlayerSprite(2,0, PlayerDir::WALKLEFTLEFT);
        ParsePlayerSprite(2,1, PlayerDir::STILLRIGHT);
        ParsePlayerSprite(2,2, PlayerDir::JUMPRIGHT);
        
    }
    

}

void Player::ParsePlayerSprite(int xaxis, int yaxis, PlayerDir dir)
{
        sf::Sprite sprite;
        sprite.setTexture(m_texture);
        sprite.setTextureRect(sf::IntRect(xaxis*PLAYEDIM,yaxis*PLAYEDIM,PLAYEDIM,PLAYEDIM));
        sprite.scale(3,3);
        sprite.setPosition(m_position);
        m_sprites.insert(std::make_pair(dir,sprite));

}

void Player::render(sf::RenderWindow* window)
{
    window->draw(m_sprites.at(PlayerDir::JUMPLEFT));
}

void Player::update(sf::Time& elapsed_time)
{

}

Player::~Player()
{

}

