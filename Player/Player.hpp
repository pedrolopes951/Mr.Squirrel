#pragma once
#include "stdafx.hpp"
#include "SFML/Graphics.hpp"



enum class PlayerDir
{
    STILLRIGHT,
    WALKRIGHTRIGHT,
    WALKRIGHTLEFT,
    JUMPRIGHTRIGHT,
    LANDRIGHT,
    STILLLEFT,
    WALKLEFTRIGHT,
    WALKLEFTLEFT,
    JUMPLEFTRIGHT,
    LANDLEFT
};

class Player
{
public:
    Player(const std::array<std::string,10>& textures_array,sf::Vector2f position);
    ~Player();

private:
    int m_health;
    int m_health_max;
    float m_speed;
    float m_movement; // Distance by player
    void InitVariables();

    // Vector which will hold the position of the player texture
    std::map<PlayerDir,sf::Texture> m_texture;
    void InitTexture(const std::array<std::string,10>& textures_array);

    sf::Sprite m_sprite; // JUst one Sprite to 

    // Position PLayer
    sf::Vector2f m_position;

};