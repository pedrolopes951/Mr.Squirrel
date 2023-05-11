#pragma once
#include "stdafx.hpp"
#include "SFML/Graphics.hpp"

constexpr int PLAYEDIM = 32;


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
    Player(const std::array<std::string,2>& textures_array,sf::Vector2f position);
    ~Player();

    void render(sf::RenderWindow* window);
    void update(sf::Time& elapsed_time);

private:
    int m_health;
    int m_health_max;
    float m_speed;
    float m_movement; // Distance by player
    void InitVariables();

    // Vector which will hold the position of the player texture
    std::map<PlayerDir,sf::Texture> m_texture;
    std::map<PlayerDir,sf::Sprite> m_sprites;
    void InitTextureSprite(const std::array<std::string,2>& textures_array);

    // Position PLayer
    sf::Vector2f m_position;

};