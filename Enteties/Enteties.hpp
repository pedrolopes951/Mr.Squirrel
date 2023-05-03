#include "stdafx.hpp"
#include "SFML/Graphics.hpp"

namespace Map
{
    
    enum class FloorType
    {
        GRASS,
        LAVA,
        DIRT,
        GRASSDIRT
    };

    struct MapBackground
    {
        /// @brief Build the Map Enteties with the texture and sprites for ther background of the game
        /// @param maps_text_paths
        MapBackground(std::vector<std::string> &maps_text_paths);
        ~MapBackground();
        void DrawMap(sf::RenderWindow *window);
       
        std::vector<sf::Sprite *> m_map_sprite;
        std::vector<sf::Texture *> m_map_texture;
        void createSprite();
    };

    struct Floor
    {
        // @brief BUIld the FLoor enteties with the textures and sprites for the floor of the game depented of the type of floor I want
        // @param map of std::vector of string to hold which type of floor to load on the map
        Floor(std::map<FloorType, const std::string> &floor_textures, float sprite_dim_x, float sprite_dim_y);
        ~Floor();
        void DrawFloor(FloorType floor, sf::RenderWindow *window);
        static std::vector<sf::Sprite> getGrid(Floor& floor_struct);
        float m_sprite_dim_x{};
        float m_sprite_dim_y{};
        
        // Texture and Sprite
        std::map<FloorType, sf::Texture *> m_floor_texture;
        std::map<FloorType, sf::Sprite *> m_floor_sprite;
        void createSprite();
    };

}