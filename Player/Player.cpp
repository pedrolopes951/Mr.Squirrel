#include "Player.hpp"

Player::Player(const std::string &textures_path, sf::Vector2f m_position) : m_position(m_position)
{
    this->InitVariables();
    this->InitTextureSprite(textures_path);
}

void Player::InitVariables()
{
    // TODO
    m_speed = 200.0f;
    m_verticalaccelaration = 0.f;
    m_move_left_stepr = false;
    m_move_right_stepr = false;
    m_look_left = false;
    m_is_jumping = false;
    m_gravity = 400.0f;
    m_maxfallspeed = 200.f;
    m_jump_height = 400.f;
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

void Player::UpdateForwardMovement(sf::Time &elapsed_time, sf::Event &event)
{
    m_horizontalaccelaration = m_speed * elapsed_time.asSeconds(); // Dsitance based on the elapsed time of each frame
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (m_move_right_stepr)
        {
            m_position.x += m_horizontalaccelaration;
            m_move_right_stepr = false;
            m_sprites.at(PlayerDir::WALKRIGHTLEFT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::WALKRIGHTLEFT);
        }
        else
        {
            m_position.x += m_horizontalaccelaration;
            m_sprites.at(PlayerDir::WALKRIGHTRIGHT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::WALKRIGHTRIGHT);
            m_move_right_stepr = true;
        }
        m_look_left = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (m_move_left_stepr)
        {
            m_position.x -= m_horizontalaccelaration;
            m_sprites.at(PlayerDir::WALKLEFTLEFT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::WALKLEFTLEFT);
            m_move_left_stepr = false;
        }
        else
        {
            m_position.x -= m_horizontalaccelaration;
            m_sprites.at(PlayerDir::WALKLEFTRIGHT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::WALKLEFTRIGHT);
            m_move_left_stepr = true;
        }
        m_look_left = true;
    }
    else 
    {

        if (m_look_left)
        {
            m_sprites.at(PlayerDir::STILLLEFT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::STILLLEFT);
        }
        else
        {
            m_sprites.at(PlayerDir::STILLRIGHT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::STILLRIGHT);
        }
    }
    UpdateJumpingMechanics(elapsed_time, event);
    for (auto &i : m_sprites)
    {
        i.second.setPosition(m_position);
    }
}

void Player::UpdateJumpingMechanics(sf::Time &elapsed_time, sf::Event &event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&& m_on_ground)
    {
        m_verticalaccelaration = -m_jump_height; 
        m_on_ground = false;
        m_is_jumping = true;
    }

    if (m_is_jumping)
    {
        UpdatePhysics(elapsed_time);
        if (m_look_left)
        {
            m_sprites.at(PlayerDir::JUMPLEFT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::JUMPLEFT);
            std::cout << "Here Left" << std::endl;
        }
        else
        {
            m_sprites.at(PlayerDir::JUMPRIGHT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::JUMPRIGHT);
            std::cout << "Here Right" << std::endl;
        }
    }
    UpdatePhysics(elapsed_time);
    if (m_drawn_sprite.getGlobalBounds().top + m_drawn_sprite.getGlobalBounds().height >= m_ground_level.y)
    {
        std::cout << "Reached Ground Level" << std::endl; 
        m_on_ground = true;
        m_is_jumping = false;
    }
}

void Player::UpdatePhysics(sf::Time &elapsed_time)
{
    m_verticalaccelaration += m_gravity * elapsed_time.asSeconds();
    if (m_verticalaccelaration > m_maxfallspeed)
        m_verticalaccelaration = m_maxfallspeed;
    m_position.y += m_verticalaccelaration * elapsed_time.asSeconds();
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

void Player::update(sf::Time &elapsed_time, sf::Event &events)
{
    UpdateForwardMovement(elapsed_time, events);
}

const sf::FloatRect Player::GetGlobalBounds() const
{

    return m_drawn_sprite.getGlobalBounds();
}

const sf::Vector2f Player::GetPosition() const
{
    return m_position;
}

const float Player::GetHorizontalVelocity() const
{
    return m_horizontalaccelaration;
}

void Player::SetPosition(sf::Vector2f position)
{
    m_position = position;
}

void Player::ResetVelocityVertical()
{
    m_verticalaccelaration = 0.f;
}

void Player::SetGroundLevel(sf::Vector2f ground_level)
{
    m_ground_level = ground_level;
}

Player::~Player()
{
}
