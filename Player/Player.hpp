#pragma once
#include "stdafx.hpp"
#include "SFML/Graphics.hpp"



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
    void update(sf::Time& elapsed_time, sf::Event& events);

    //Check for collitions
    void checkCollitionsPlatTiles(const sf::Sprite& sprite);
    void checkCollitionsFloorTiles(const sf::Sprite& sprite);
    void checkCollitionsWindow(const sf::View& view);

    // Getter
    const sf::FloatRect GetGlobalBounds() const;  
    const sf::Vector2f GetPosition() const;
    const float GetHorizontalVelocity() const;

    // Setter
    void SetPosition(sf::Vector2f position);
    void ResetVelocityVertical();
    void SetGroundLevel(sf::Vector2f ground_level);

private:

    // Variables to move sprite
    bool m_move_right_stepr;
    bool m_move_left_stepr;
    bool m_look_left;
    bool m_on_ground;
    bool m_is_jumping;

    float m_verticalaccelaration;
    float m_speed;
    float m_horizontalaccelaration; // Distance by player
    float m_gravity;
    float m_maxfallspeed;
    float m_jump_height;
    sf::Vector2f m_ground_level;


    void InitVariables();

    // Vector which will hold the position of the player texture
    sf::Texture m_texture;
    std::map<PlayerDir,sf::Sprite> m_sprites;
    sf::Sprite m_drawn_sprite;
    // Collition box to track the drawn_sprite
    sf::FloatRect m_collition_box{}; 
    sf::Vector2f m_position;
    
    // Functions
    void updateCollitionBox();
    void UpdatePhysics(sf::Time &elapsed_time);
    void UpdateForwardMovement(sf::Time &elapsed_time, sf::Event& event);
    void UpdateJumpingMechanics(sf::Time& elapsed_time, sf::Event& event);
    void InitTextureSprite(const std::string& textures_path);
    void ParsePlayerSprite(int xaxis, int yaxis, PlayerDir dir);


};

