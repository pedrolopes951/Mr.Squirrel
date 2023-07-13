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
        // Build the vector of floor tiles
        int numberTiles = WINDOWX / FLOORSIZESQUARE;
        for (int i = 0; i < numberTiles + 1; i++)
        {
            sf::Sprite sprite;
            sprite = m_sprite;
            sprite.setPosition(sf::Vector2f(i * FLOORSIZESQUARE, WINDOWY - m_sprite.getGlobalBounds().height));
            m_sprites_vec.push_back(sprite);
        }
    }

    void Floor::draw(sf::RenderWindow *window)
    {
        for (auto &sprite : m_sprites_vec)
        {
            window->draw(sprite);
        }
    }

    void Floor::updateTiles(const sf::View &window_view)
    {

        if (!m_sprites_vec.empty())
        {

            // Check pre last tile that the view has passed the last tile then add another after the end
            if (window_view.getCenter().x + window_view.getSize().x / 2 > m_sprites_vec[m_sprites_vec.size() - 1].getGlobalBounds().left + m_sprites_vec[m_sprites_vec.size() - 1].getGlobalBounds().width)
            {
                // Make the tile in the begginging go the end with a new position (circula way)
                m_sprites_vec.begin()->setPosition(sf::Vector2f(m_sprites_vec[m_sprites_vec.size() - 1].getGlobalBounds().left + m_sprites_vec[m_sprites_vec.size() - 1].getGlobalBounds().width, m_sprites_vec.begin()->getPosition().y));
                // Add new one to the vector after the
                m_sprites_vec.push_back(std::move(*m_sprites_vec.begin()));
                m_sprites_vec.erase(m_sprites_vec.begin());
            }
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
        // First location for drawing tiles is last place of the tile
        m_last_tile_pos_x = WINDOWX;
    };
    void Platform::updateTiles(const sf::View &window_view)
    {
        // Get View Position and place the tiles only on the view is passed the first window size
        if (window_view.getCenter().x - window_view.getSize().x / 2 > m_last_tile_pos_x)
        {
            this->createScenes(&window_view);
            m_last_tile_pos_x = m_sprites_vec.back().getGlobalBounds().left + m_sprites_vec.back().getGlobalBounds().width;
        }
    }
    void Platform::draw(sf::RenderWindow *window)
    {
        for (auto &i : m_sprites_vec)
        {
            window->draw(i);
        }
    }
    const std::vector<sf::Sprite> &Platform::getSprite() const
    {
        return m_sprites_vec;
    }

    void Platform::createScenes(const sf::View *window)
    {
        int get_scene = rand() % (int)(Scenes::NUMBERSCENES);
        switch (static_cast<Scenes>(get_scene))
        {
        case Scenes::SCENE1:
            /* This scene will have 3 tiles in the middle of the window range  */
            m_sprites_vec.clear();
            for (int i = 0; i < 2; i++)
            {
                sf::Sprite sprite;
                sprite = m_sprite;
                float x = m_last_tile_pos_x + (window->getSize().x) + (i + 1) * sprite.getGlobalBounds().width;
                float y = 400.f;
                sprite.setPosition(x, y);
                m_sprites_vec.push_back(sprite);
            }
            break;
        case Scenes::SCENE2:
            m_sprites_vec.clear();
            for (int i = 0; i < 2; i++)
            {
                sf::Sprite sprite;
                sprite = m_sprite;
                float x = m_last_tile_pos_x + (window->getSize().x ) + (i + 1) * sprite.getGlobalBounds().width;
                float y = 400.f;
                sprite.setPosition(x, y);
                m_sprites_vec.push_back(sprite);
            }
            /* code */
            break;
        case Scenes::SCENE3:
            m_sprites_vec.clear();
            for (int i = 0; i < 2; i++)
            {
                sf::Sprite sprite;
                sprite = m_sprite;
                float x = m_last_tile_pos_x + (window->getSize().x ) + (i + 1) * sprite.getGlobalBounds().width;
                float y = 400.f;
                sprite.setPosition(x, y);
                m_sprites_vec.push_back(sprite);
            }
            break;
        default:
            break;
        }
    }

    Wall::Wall(const cv::Mat &tile)
    {
        sf::Image sfml_imag;
        sfml_imag.create(tile.cols, tile.rows, tile.ptr());

        m_texture.loadFromImage(sfml_imag);
        m_sprite.setTexture(m_texture);
    }
    void Wall::updateTiles(const sf::View &window_view)
    {
        // Get View Position and place the tiles only on the view of it
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
