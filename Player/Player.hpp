#pragma once
#include "stdafx.hpp"
#include "SFML/Graphics.hpp"

constexpr int PLAYEDIM = 32;


enum class PlayerDir
{
    STILLRIGHT,
    WALKRIGHTRIGHT,
    WALKRIGHTLEFT,
    JUMPRIGHT,
    LANDRIGHT,
    STILLLEFT,
    WALKLEFTRIGHT,
    WALKLEFTLEFT,
    JUMPLEFT,
    LANDLEFT
};


class Player
{
public:
    Player(const std::string& textures_path,sf::Vector2f position);
    ~Player();

    void render(sf::RenderWindow* window);
    void update(sf::Time& elapsed_time);

private:

    // Variables to move sprite
    bool m_move_right_stepr;
    bool m_move_left_stepr;
    bool m_look_left;

    int m_health;
    int m_health_max;
    float m_speed;
    float m_distance; // Distance by player
    void InitVariables();

    // Vector which will hold the position of the player texture
    sf::Texture m_texture;
    std::map<PlayerDir,sf::Sprite> m_sprites;
    sf::Sprite m_drawn_sprite;
    void InitTextureSprite(const std::string& textures_path);
    void ParsePlayerSprite(int xaxis, int yaxis, PlayerDir dir);

    // Position PLayer
    sf::Vector2f m_position;

};