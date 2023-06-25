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
    updateCollitionBox();
}

void Player::ParsePlayerSprite(int xaxis, int yaxis, PlayerDir dir)
{
    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setTextureRect(sf::IntRect(xaxis * PLAYEDIM, yaxis * PLAYEDIM, PLAYEDIM, PLAYEDIM));
    std::cout << " Width : " << sprite.getGlobalBounds().width << " Height : " << sprite.getGlobalBounds().height << std::endl;
    sprite.setScale(3.f, 3.f); // Scale the sprite to the desired size

    sprite.setPosition(m_position);

    m_sprites.insert(std::make_pair(dir, sprite));
}

void Player::UpdateForwardMovement(sf::Time &elapsed_time, sf::Event &event)
{
    m_horizontalaccelaration = m_speed * elapsed_time.asSeconds(); // Dsitance based on the elapsed time of each frame
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_on_ground)
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
        }
        else
        {
            m_sprites.at(PlayerDir::JUMPRIGHT).setPosition(m_position);
            m_drawn_sprite = m_sprites.at(PlayerDir::JUMPRIGHT);
        }
    }
    UpdatePhysics(elapsed_time);
    if (m_collition_box.top + m_collition_box.height >= m_ground_level.y)
    {
        m_on_ground = true;
        m_is_jumping = false;
    }
}

void Player::updateCollitionBox()
{
    m_collition_box.left = m_drawn_sprite.getGlobalBounds().left + PLAYEDIM; // OFFSET to collition;
    m_collition_box.top = m_drawn_sprite.getGlobalBounds().top;              // OFFSET to collition;
    m_collition_box.height = m_drawn_sprite.getGlobalBounds().height;
    m_collition_box.width = m_drawn_sprite.getGlobalBounds().width - 2 * PLAYEDIM;
}

void Player::UpdatePhysics(sf::Time &elapsed_time)
{
    m_verticalaccelaration += m_gravity * elapsed_time.asSeconds();
    if (m_verticalaccelaration > m_maxfallspeed)
        m_verticalaccelaration = m_maxfallspeed;
    m_position.y += m_verticalaccelaration * elapsed_time.asSeconds();
}

void Player::render(sf::RenderWindow *window)
{
    window->draw(m_drawn_sprite);

    // Create a red circle shape with a center in sprite
    // sf::CircleShape center_sprite(5.f);
    // center_sprite.setFillColor(sf::Color::Red);

    // // Position the center_sprite at coordinates
    // center_sprite.setPosition(m_drawn_sprite.getPosition());

    // window->draw(center_sprite);

    sf::RectangleShape rectShape(sf::Vector2f(m_collition_box.width, m_collition_box.height));
    rectShape.setPosition(m_collition_box.left, m_collition_box.top);
    rectShape.setFillColor(sf::Color::Transparent);
    rectShape.setOutlineThickness(2);
    rectShape.setOutlineColor(sf::Color::Red);
    window->draw(rectShape);
    // Create a blue circle shape with a center in collition box
    sf::CircleShape center_box(5.f);
    center_box.setFillColor(sf::Color::Cyan);

    // Position the center_box at coordinates
    center_box.setPosition(m_collition_box.left, m_collition_box.top);
    window->draw(center_box);
}

void Player::update(sf::Time &elapsed_time, sf::Event &events)
{
    UpdateForwardMovement(elapsed_time, events);
    updateCollitionBox();
}

void Player::checkCollitionsTiles(const sf::Sprite &sprite)
{
    if (m_collition_box.intersects(sprite.getGlobalBounds()))
    {
        std::cout << "Floor tile Positionx: " << sprite.getPosition().x << std::endl;
        std::cout << "Floor tile Positiony: " << sprite.getPosition().y << std::endl;
        // Check for bottom of player in tile
        this->ResetVelocityVertical();
        this->SetPosition(sf::Vector2f( this->GetPosition().x,sprite.getGlobalBounds().top - m_collition_box.height)); 
        this->SetGroundLevel(sf::Vector2f(0, sprite.getPosition().y));
    }
}

void Player::checkCollitionsWindow(const sf::View &view)
{
    // Make Player Colide with the left wall everytime it moves
    if (this->GetGlobalBounds().left <= view.getCenter().x - view.getSize().x / 2)
    {
        this->SetPosition(sf::Vector2f(view.getCenter().x - view.getSize().x / 2, this->GetPosition().y));
    }
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
