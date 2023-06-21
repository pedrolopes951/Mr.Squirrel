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
        this->loadTextures(maps_text_paths);
        this->createSprite();
    }
    void MapBackground::loadTextures(const std::vector<std::string> &maps_text_paths)
    {
        for (const auto &path : maps_text_paths)
        {
            sf::Texture texture;

            if (!texture.loadFromFile(path))
            {
                std::cerr << "Error Loading the texture"
                          << "\n";
            }
            m_map_texture.push_back(texture);
            ;
        }

        m_rightmostPosition = m_map_texture.back().getSize().x;
    }
    void MapBackground::createSprite()
    {
        m_map_sprite.reserve(m_map_texture.size() * NUMBERMAPS);

        for (auto &texture : m_map_texture)
        {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            m_map_sprite.push_back(sprite);
        }
        std::cout << typeid(m_map_sprite[1]).name() << std::endl;

        m_total_map_size.x = m_map_sprite.back().getPosition().x;
        for (size_t i = 0; i < NUMBERMAPS; i++)
        {
            sf::Sprite copy;
            auto it_end = m_map_sprite.end();
            for (auto it = m_map_sprite.begin() + i * m_map_texture.size(); it != it_end; ++it)
            {
                copy = (*it);
                copy.setPosition(m_rightmostPosition, 0.0f);
                m_map_sprite.push_back(copy);
            }
            m_rightmostPosition = m_map_sprite.back().getPosition().x + m_map_sprite.back().getGlobalBounds().width;
        }
        m_total_map_size.x = m_map_sprite.back().getPosition().x;
    }
    MapBackground::~MapBackground()
    {
    }
    void MapBackground::DrawMap(sf::RenderWindow *window)
    {
        // Draw the original sprites
        for (auto it = m_map_sprite.begin(); it != m_map_sprite.end(); ++it)
        {
            window->draw(*it);
        }
    }
    Floor::Floor(const cv::Mat &tile)
    {
        sf::Image sfml_image; // Create a sfml image with the dimention of the pixels matrix of the cv object
        sfml_image.create(tile.cols, tile.rows);

        // Iterate over each pixel in the tile matrix
        for (int y = 0; y < tile.rows; y++)
        {
            for (int x = 0; x < tile.cols; x++)
            {
                // Retrieve the color value of the current pixel
                cv::Vec3b color = tile.at<cv::Vec3b>(y, x);

                // Create an SFML color using the RGB values from the OpenCV color channels
                sf::Color sfml_color(color[2], color[1], color[0]);

                // Set the pixel at (x, y) in the SFML image with the corresponding SFML color
                sfml_image.setPixel(x, y, sfml_color);
            }
        }

        m_texture.loadFromImage(sfml_image);
        m_sprite.setTexture(m_texture);

        m_sprite.setScale(FLOORSIZESQUARE / m_texture.getSize().x, FLOORSIZESQUARE / m_texture.getSize().y);
        m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width/2,m_sprite.getGlobalBounds().height/2));
        // Build the vector of floor tiles 
        int numberTiles = WINDOWX/FLOORSIZESQUARE;
        for(int i = 0; i < numberTiles; i++)
        {
            sf::Sprite sprite;
            sprite = m_sprite;
            sprite.setPosition(sf::Vector2f(i*FLOORSIZESQUARE, WINDOWY - m_sprite.getGlobalBounds().height));
            m_sprites_vec.push_back(sprite);
        }
    }

    void Floor::draw(sf::RenderWindow *window)
    {
        for(auto &sprite: m_sprites_vec)
        {
            window->draw(sprite);
        }
    }

    const std::vector<sf::Sprite> &Floor::getSprite() const
    {
        return m_sprites_vec;
    }

    Floor::~Floor()
    {
    }

    Platform::Platform(const cv::Mat &tile)
    {
        sf::Image sfml_imag;
        sfml_imag.create(tile.cols, tile.rows, tile.ptr());

        m_texture.loadFromImage(sfml_imag);
        m_sprite.setTexture(m_texture);
        
    };
    void Platform::draw(sf::RenderWindow *window)
    {
        window->draw(m_sprite);
    }
    const std::vector<sf::Sprite> &Platform::getSprite() const
    {
        return m_sprites_vec;
    }

    Wall::Wall(const cv::Mat &tile)
    {
        sf::Image sfml_imag;
        sfml_imag.create(tile.cols, tile.rows, tile.ptr());

        m_texture.loadFromImage(sfml_imag);
        m_sprite.setTexture(m_texture);
        
    }

    void Wall::draw(sf::RenderWindow *window)
    {
        window->draw(m_sprite);
    }
    const std::vector<sf::Sprite> &Wall::getSprite() const
    {
        return m_sprites_vec;
    }

}