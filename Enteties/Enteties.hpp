#include "stdafx.hpp"

#include "SFML/Graphics.hpp"

namespace Map
{
    struct MapBackground
    {
        /// @brief Build the Map Enteties with the texture and sprites for ther background of the game
        /// @param maps_text_paths
        MapBackground(std::vector<std::string> &maps_text_paths);
        ~MapBackground();
        void DrawMap(sf::RenderWindow *window);

        std::vector<sf::Sprite *> m_map_sprite;
        std::vector<sf::Sprite> m_map_sprite_copy;
        std::vector<sf::Texture *> m_map_texture;
        void createSprite();
        // Save righ most position
        float m_rightmostPosition;
    };

    enum class FloorType
    {
        FLOOR,
        PLATFORM,
        WALL,
        GRASSDIRT
    };

    struct TileData
    {
        // Save the contents to get the image form the png with all the textures needed
        int posX;
        int posY;
        int sizeX;
        int sizeY;
    };

    struct ITiles
    {
    public:
        virtual ~ITiles(){};
        virtual void draw(sf::RenderWindow *window) = 0;
    };

    struct Floor : public ITiles
    {
        // @brief BUIld the FLoor enteties with the textures and sprites for the floor of the game depented of the type of floor I want
        // @param map of std::vector of string to hold which type of floor to load on the map
        Floor(std::map<FloorType, const std::string> &floor_textures, float sprite_dim_x, float sprite_dim_y);
        Floor(const std::string &texturePath, const TileData &tileData) : m_tile_data{tileData}
        {
            m_texture.loadFromFile(texturePath);
            m_sprite.setTexture(m_texture);
            m_sprite.setTextureRect(sf::IntRect(tileData.posX, tileData.posY, tileData.sizeX, tileData.sizeY)); // set the global bounds of the sprite
            // TODO: resize the texture to the 50,50
        };
        ~Floor();
        void draw(sf::RenderWindow *window);
        void getGrid(FloorType type);
        float m_sprite_dim_x{};
        float m_sprite_dim_y{};

        // Texture and Sprite
        std::map<FloorType, sf::Texture *> m_floor_texture;
        std::map<FloorType, sf::Sprite *> m_floor_sprite;
        void createSprite();
        std::vector<sf::Sprite> m_tiles{};

    private:
        TileData m_tile_data;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    };

    struct Platform : public ITiles
    {
        Platform();
        Platform(const std::string &texturePath, const TileData &tileData) : m_tile_data{tileData}
        {
            m_texture.loadFromFile(texturePath);
            m_sprite.setTexture(m_texture);
            m_sprite.setTextureRect(sf::IntRect(tileData.posX, tileData.posY, tileData.sizeX, tileData.sizeY)); // set the global bounds of the sprite
            // TODO: resize the texture to the 50,50
        };
        void draw(sf::RenderWindow *window) override;
        ~Platform(){};

    private:
        TileData m_tile_data;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    };
    struct Wall : public ITiles
    {
        Wall();
        Wall(const std::string &texturePath, const TileData &tileData) : m_tile_data{tileData}
        {
            m_texture.loadFromFile(texturePath);
            m_sprite.setTexture(m_texture);
            m_sprite.setTextureRect(sf::IntRect(tileData.posX, tileData.posY, tileData.sizeX, tileData.sizeY)); // set the global bounds of the sprite
            // TODO: resize the texture to the 50,50
        };
        void draw(sf::RenderWindow *window) override;

        ~Wall(){};

    private:
        TileData m_tile_data;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    };

    struct TileFactory
    {
    public:
        static ITiles *createTile(FloorType type, const std::string &texturePath, const TileData &tileData)
        {
            // Look at type of floor
            switch (type)
            {
            case FloorType::FLOOR:
                return new Floor(texturePath, tileData);
                break;
            case FloorType::PLATFORM:
                /*TODO*/
                return new Platform(texturePath, tileData);
                break;

            case FloorType::WALL:
                return new Wall(texturePath, tileData);
            default:
                std::cerr << "Error, not valid Grid";
                return nullptr;
            }
        }
    }
};