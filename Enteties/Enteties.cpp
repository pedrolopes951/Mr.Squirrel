#include "Enteties.hpp"

constexpr float MAINWINDOWWIDHT = 800.f;
constexpr float MAINWINDOWHEIGHT = 600.f;
constexpr float FLOORWIDHT = 800.f;
constexpr float FLOORHEIGHT = 50.f;

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

    void Floor::DrawFloor(FloorType floor, sf::RenderWindow *window)
    {

        window->draw(*m_floor_sprite.at(floor));
    }

    std::vector<sf::Sprite> Floor::getGrid(Floor &floor_struct)
    {
        // Grid of sprites for the floor
        const float l_title_width{floor_struct.m_sprite_dim_x};
        const float l_title_height{floor_struct.m_sprite_dim_y};
        int l_numTilesX{};
        int l_numTilesY{};
        std::vector<sf::Sprite> m_tiles{};

        for (auto &i : floor_struct.m_floor_sprite)
        {
            // Look at type of floor
            switch (i.first)
            {
            case FloorType::GRASS:
                /*TODO*/
                break;
            case FloorType::LAVA:
                /*TODO*/
            case FloorType::DIRT:
                /*TODO*/
            case FloorType::GRASSDIRT:
                l_numTilesX = std::ceil(static_cast<int>(FLOORWIDHT / l_title_width));
                l_numTilesY = std::ceil(static_cast<int>(FLOORHEIGHT / l_title_height));
                for (int j = 0; j < l_numTilesY; j++)
                {
                    for (int k = 0; k < l_numTilesX; k++)
                    {
                        sf::Sprite tile(*i.second);
                        tile.setPosition(k * l_title_width, (MAINWINDOWHEIGHT) - l_title_height - j * l_title_height);
                        m_tiles.push_back(tile);
                    }
                }
            default:
                break;
            }
        }
        return m_tiles;
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