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
        // Create copies of the sprites
        sf::Sprite copy;
        for (auto sprite : m_map_sprite)
        {
            copy = (*sprite);
            m_map_sprite_copy.push_back(copy);
        }
        m_rightmostPosition = m_map_sprite.back()->getGlobalBounds().width;
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
        // Draw the original sprites
        for (auto it = m_map_sprite.rbegin(); it != m_map_sprite.rend(); ++it)
        {
            window->draw(**it);
        }


        // Position and draw the copied sprites
        for (auto it = m_map_sprite_copy.rbegin(); it != m_map_sprite_copy.rend(); ++it)
        {
            it->setPosition(m_rightmostPosition, 0.0f);
            window->draw(*it);
        }

        
    }
    Floor::Floor(std::map<FloorType, const std::string> &floor_textures, float sprite_dim_x, float sprite_dim_y) : m_sprite_dim_x{sprite_dim_x}, m_sprite_dim_y{sprite_dim_y}
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

            // Set Sprite with already current rectangle dimentions
            sprite->setScale(sf::Vector2f(m_sprite_dim_x / sprite->getTextureRect().width, m_sprite_dim_y / sprite->getTextureRect().height));
            m_floor_sprite.insert(std::pair<FloorType, sf::Sprite *>(i.first, sprite));
        }
    }

    void Floor::draw(sf::RenderWindow *window)
    {
        for (const auto &i : m_tiles)
        {
            window->draw(i);
        }
    }

    void Floor::getGrid(FloorType type)
    {
        // // Grid of sprites for the floor
        // const float l_title_width{m_sprite_dim_x};
        // const float l_title_height{m_sprite_dim_y};
        // int l_numTilesX{};
        // int l_numTilesY{};
        sf::Vector2i tile_range_start;
        sf::Vector2i tile_range_end;

        // Look at type of floor
        switch (type)
        {
        case FloorType::GRASS:
            /*TODO*/
            break;
        case FloorType::LAVA:
            /*TODO*/
            break;

        case FloorType::DIRT:
            /*TODO*/
            break;

        case FloorType::GRASSDIRT:
            // Calculate the range of tiles within the visible area
            tile_range_start = sf::Vector2i(static_cast<int>(0), static_cast<int>(0 / m_sprite_dim_y));
            tile_range_end = sf::Vector2i(static_cast<int>((NUMBEROFTILESFLOOR * MAINWINDOWWIDHT) / m_sprite_dim_x), 1);
            for (int j = tile_range_start.y; j < tile_range_end.y; j++)
            {
                for (int k = tile_range_start.x; k < tile_range_end.x; k++)
                {
                    sf::Sprite tile(*m_floor_sprite.at(FloorType::GRASSDIRT));
                    tile.setPosition(k * m_sprite_dim_x, MAINWINDOWHEIGHT - m_sprite_dim_y - j * m_sprite_dim_y);
                    m_tiles.push_back(tile);
                }
            }
            break;
        default:
            std::cerr << "Error, not valid Grid";
            break;
        }
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