#include "stdafx.hpp"
#include "SFML/Graphics.hpp"


namespace Map{
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
        MapBackground(std::vector<std::string>& maps_text_paths);
        ~MapBackground();
        std::vector<sf::Texture*> m_map_texture;
        std::vector<sf::Sprite*> m_map_sprite;
        void DrawMap(sf::RenderWindow* window);

    private:
        void createSprite(); 
         
    };
    

    struct Floor
    {
        // @brief BUIld the FLoor enteties with the textures and sprites for the floor of the game depented of the type of floor I want
        // @param map of std::vector of string to hold which type of floor to load on the map
        Floor(std::map<FloorType,const std::string>& floor_textures);
        ~Floor();
        std::map<FloorType,sf::Texture*> m_floor_texture;
        std::map<FloorType,sf::Sprite*> m_floor_sprite;
        void DrawFloor(FloorType floor,sf::RenderWindow* window);

    private:
        void createSprite();

    };
    
}