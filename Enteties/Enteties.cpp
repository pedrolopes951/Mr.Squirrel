#include "Enteties.hpp"

namespace Map
{
    MapBackground::MapBackground(std::vector<std::string> &maps_text_paths)
    {
        if (maps_text_paths.size() != 3)
        {
            std::cerr << "Error Not Enough Textures paths for the background"
                      << "\n";
        }
        for (auto i : maps_text_paths)
        {
            sf::Texture *texture = new sf::Texture();
            if (!texture->loadFromFile(i))
            {
                std::cerr << "Error Loading the texture"
                          << "\n";
            }
            m_map_texture.push_back(texture);
        }

        this->createSprite();
    }
    void MapBackground::createSprite()
    {
        for (auto i : m_map_texture)
        {
            sf::Sprite *sprite = new sf::Sprite(*i);
            m_map_sprite.push_back(sprite);
        }
    }
    MapBackground::~MapBackground()
    {
        for (auto i : m_map_sprite)
        {
            delete i;
        }

        for (auto i : m_map_texture)
        {
            delete i;
        }
    }
    void MapBackground::DrawMap(sf::RenderWindow *window)
    {
        for (int i = m_map_sprite.size() - 1; i >= 0; i--)
        {
            window->draw(*m_map_sprite[i]);
        }
    }
    Floor::Floor(std::map<FloorType, const std::string> &floor_textures)
    {
        for (auto i : floor_textures)
        {

            sf::Texture *texture = new sf::Texture();
            if (!texture->loadFromFile(i.second))
            {
                std::cerr << "Error Loading the texture"
                          << "\n";
            }
            m_floor_texture.insert(std::pair<FloorType, sf::Texture *>(i.first, texture));
        }

        this->createSprite();
    }
    void Floor::createSprite()
    {
        for (auto &i : m_floor_texture)
        {

            sf::Sprite *sprite = new sf::Sprite();

            sprite->setTexture(*i.second);

            m_floor_sprite.insert(std::pair<FloorType, sf::Sprite *>(i.first, sprite));
        }
    }

    void Floor::DrawFloor(FloorType floor, sf::RenderWindow *window)
    {
        
        window->draw(*m_floor_sprite.at(floor));
    }
    Floor::~Floor()
    {
        for (auto i : m_floor_texture)
        {
            delete i.second;
        }

        for (auto i : m_floor_sprite)
        {

            delete i.second;
        }
    }
}