#include "Enteties.hpp"

namespace Map{
    MapTextures::MapTextures(std::vector<std::string>& maps_text_paths)
    {
        if(maps_text_paths.size() != 3)
        {
            std::cerr << "Error Not Enough Textures paths for the back ground" << "\n";
        }
        for (auto i : maps_text_paths)
        {
            sf::Texture * texture = new sf::Texture();
            if(!texture->loadFromFile(i))
            {
                std::cerr << "Error Loading the texture" << "\n";
            }
            m_map_texture.push_back(texture);
        }

        this->createSprite();
    }
    void MapTextures::createSprite()
    {
        for (auto i : m_map_texture)
        {
            sf::Sprite * sprite = new sf::Sprite(*i);
            m_map_sprite.push_back(sprite);
        }
    }
    MapTextures::~MapTextures()
    {
        for(auto i: m_map_sprite)
        {
            delete i;
        }

        for(auto i: m_map_texture)
        {
            delete i;
        }
    }
    void MapTextures::DrawMap(sf::RenderWindow *window)
    {
        for (int i = m_map_sprite.size() - 1 ; i >= 0; i--)
        {
            window->draw(*m_map_sprite[i]); 
        }
        
    }
}