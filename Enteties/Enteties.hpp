#include "stdafx.hpp"
#include "SFML/Graphics.hpp"


namespace Map{
    struct MapTextures
    {
        /// @brief Build the Map Enteties with the texture and sprites for ther background of the game 
        /// @param maps_text_paths 
        MapTextures(std::vector<std::string>& maps_text_paths);
        ~MapTextures();
        std::vector<sf::Texture*> m_map_texture;
        std::vector<sf::Sprite*> m_map_sprite;
        void DrawMap(sf::RenderWindow* window);

    private:
        void createSprite(); 

         
    };
    
    
}