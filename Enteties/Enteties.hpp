#include "stdafx.hpp"
#include "SFML/Graphics.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include "Runtime.hpp"


namespace Map
{

    struct MapBackground
    {
        /// @brief Build the Map Enteties with the texture and sprites for ther background of the game
        /// @param maps_text_paths
        MapBackground(std::vector<std::string> &maps_text_paths);
        ~MapBackground();
        void loadTextures(const std::vector<std::string> &maps_text_paths);

        void DrawMap(sf::RenderWindow *window);

        std::vector<sf::Texture> m_map_texture{};
        std::vector<sf::Sprite> m_map_sprite{};

        void createSprite();
        // Save righ most position
        float m_rightmostPosition;
        sf::Vector2f m_total_map_size;
    };

    enum class FloorType
    {
        FLOOR,
        PLATFORM,
        WALL,
        GRASSDIRT
    };

    struct ITiles
    {
    public:
        virtual ~ITiles(){};
        virtual void draw(sf::RenderWindow *window) = 0;
        virtual void updateTiles(const sf::View &window_view) = 0;
        virtual const std::vector<sf::Sprite> &getSprite() const = 0;
    };

    struct Floor : public ITiles
    {
        Floor(const cv::Mat &tile);
        ~Floor();
        void draw(sf::RenderWindow *window);
        void updateTiles(const sf::View &window_view) override;
        const std::vector<sf::Sprite> &getSprite() const override;

    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        std::vector<sf::Sprite> m_sprites_vec{};
    };

    struct Platform : public ITiles
    {
        Platform(const cv::Mat &tile);
        void draw(sf::RenderWindow *window) override;
        void updateTiles(const sf::View &window_view) override;

        const std::vector<sf::Sprite> &getSprite() const override;
        ~Platform(){};

    private:
        enum class Scenes{
            SCENE1,
            SCENE2,
            SCENE3,
            NUMBERSCENES
        };
        void createScenes(const sf::View  * window);
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        std::vector<sf::Sprite> m_sprites_vec{};
        int m_last_tile_pos_x{};
    };
    struct Wall : public ITiles
    {

        Wall(const cv::Mat &tile);
        void draw(sf::RenderWindow *window) override;
        void updateTiles(const sf::View &window_view) override;

        const std::vector<sf::Sprite> &getSprite() const override;
        ~Wall(){};

    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        std::vector<sf::Sprite> m_sprites_vec;
    };

    struct TileFactory
    {
    public:
        static ITiles *createTile(const cv::Mat &tile, FloorType type)
        {

            // Look at type of floor
            switch (type)
            {
            case FloorType::FLOOR:
                // Parse here the position to create the tiledata to build he floor
                return new Floor(tile);
                break;
            case FloorType::PLATFORM:
                /*TODO*/
                return new Platform(tile);
                break;
            case FloorType::WALL:
                return new Wall(tile);
            default:
                std::cerr << "Error, not valid Grid";
                return nullptr;
            }
        }
    };
}