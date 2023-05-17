#include "Player.hpp"

Player::Player(const std::string &textures_path, sf::Vector2f position) : m_position(position)
{
    this->InitVariables();
    this->InitTextureSprite(textures_path);
}

void Player::InitVariables()
{
    // TODO
    m_health_max = 10;
    m_health = m_health_max;
    m_speed = 100.0f;
    m_move_left_stepr = false;
    m_move_right_stepr = false;
    m_look_left = false;
}

void Player::InitTextureSprite(const std::string &textures_path)
{
    if (m_texture.loadFromFile(textures_path))
    {
        ParsePlayerSprite(0, 0, PlayerDir::STILLLEFT);
        ParsePlayerSprite(0, 1, PlayerDir::JUMPLEFT);
        ParsePlayerSprite(0, 2, PlayerDir::WALKRIGHTLEFT);
        ParsePlayerSprite(0, 3, PlayerDir::LANDRIGHT);
        ParsePlayerSprite(1, 0, PlayerDir::WALKLEFTRIGHT);
        ParsePlayerSprite(1, 1, PlayerDir::LANDLEFT);
        ParsePlayerSprite(1, 2, PlayerDir::WALKRIGHTRIGHT);
        ParsePlayerSprite(2, 0, PlayerDir::WALKLEFTLEFT);
        ParsePlayerSprite(2, 1, PlayerDir::STILLRIGHT);
        ParsePlayerSprite(2, 2, PlayerDir::JUMPRIGHT);
    }
    m_drawn_sprite = m_sprites.at(PlayerDir::STILLRIGHT);
}

void Player::ParsePlayerSprite(int xaxis, int yaxis, PlayerDir dir)
{
    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setTextureRect(sf::IntRect(xaxis * PLAYEDIM, yaxis * PLAYEDIM, PLAYEDIM, PLAYEDIM));
    sprite.scale(3, 3);
    sprite.setPosition(m_position);
    m_sprites.insert(std::make_pair(dir, sprite));
}

void Player::render(sf::RenderWindow *window)
{
    window->draw(m_drawn_sprite);
}

void Player::update(sf::Time &elapsed_time)
{
    m_distance = m_speed * elapsed_time.asSeconds(); // Dsitance based on the elapsed time of each frame
    sf::Vector2f position = m_drawn_sprite.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (m_move_right_stepr)
        {
            position.x += m_distance;
            m_sprites.at(PlayerDir::WALKRIGHTLEFT).setPosition(position);
            m_drawn_sprite = m_sprites.at(PlayerDir::WALKRIGHTLEFT);
            m_move_right_stepr = false;
        }
        else
        {
            position.x += m_distance;
            m_sprites.at(PlayerDir::WALKRIGHTLEFT).setPosition(position);
            m_drawn_sprite = m_sprites.at(PlayerDir::WALKRIGHTRIGHT);
            m_move_right_stepr = true;
        }
        m_look_left = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (m_move_left_stepr)
        {
            position.x -= m_distance;
            m_sprites.at(PlayerDir::WALKLEFTLEFT).setPosition(position);
            m_drawn_sprite = m_sprites.at(PlayerDir::WALKLEFTLEFT);
            m_move_left_stepr = false;
        }
        else
        {
            position.x -= m_distance;
            m_sprites.at(PlayerDir::WALKLEFTRIGHT).setPosition(position);
            m_drawn_sprite = m_sprites.at(PlayerDir::WALKLEFTRIGHT);
            m_move_left_stepr = true;
        }
        m_look_left = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        position.y -= m_distance;
        m_sprites.at(PlayerDir::JUMPRIGHT).setPosition(position);
        m_drawn_sprite = m_sprites.at(PlayerDir::JUMPRIGHT);
    }
    else
    {

        if (m_look_left)
        {
            m_sprites.at(PlayerDir::STILLLEFT).setPosition(position);
            m_drawn_sprite = m_sprites.at(PlayerDir::STILLLEFT);
        }
        else
        {
            m_sprites.at(PlayerDir::STILLRIGHT).setPosition(position);
            m_drawn_sprite = m_sprites.at(PlayerDir::STILLRIGHT);
        }
    }
    for (auto &i : m_sprites)
    {
        i.second.setPosition(position);
    }
}

Player::~Player()
{
}
