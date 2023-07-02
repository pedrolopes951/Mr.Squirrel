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
    };
    void Platform::updateTiles(const sf::View &window_view)
    {
        // Get View Position and place the tiles only on the view is passed the first window size
        if (window_view.getCenter().x - window_view.getSize().x / 2 > m_scene_iter * WINDOWX)
        {
            std::cout << "Window Left Side X" << window_view.getCenter().x - window_view.getSize().x/2 << std::endl;
            // Get platform tiles
            std::vector<std::vector<sf::Sprite>> scene_vector = VectorUtils::RandomTilesVec<sf::Sprite>(MAXNUMBEROFTILES, MAXNUMBEROFVEC);
            // Lambda function to count the total number of elements
            auto countElements = [](const std::vector<std::vector<sf::Sprite>> &vectorOfVectors)
            {
                return std::accumulate(vectorOfVectors.begin(), vectorOfVectors.end(), 0,
                                       [](int sum, const std::vector<sf::Sprite> &vector) 
                                       {
                                           return sum + vector.size();
                                       });
            };
            std::cout << "Total size of vector : " << countElements(scene_vector) << std::endl;
            int total_element_size = countElements(scene_vector) * m_sprite.getGlobalBounds().width; 
            // Define region to build each platform int randNum = rand()%(max-min + 1) + min;
            float x_limit = static_cast<float>(rand() % ((int)(window_view.getCenter().x + WINDOWX) -  (int)(window_view.getCenter().x + WINDOWX/2)) + (int)(window_view.getCenter().x + WINDOWX/2));
            float y_limit = static_cast<float>(rand() % (MAXPLATFORMHEIGHT - (PLAYEDIM - PLAYEDIMYOFFSET)) + (PLAYEDIM - PLAYEDIMYOFFSET));
            float get_pos_last_tile_x{x_limit};
            float get_pos_last_tile_y{y_limit};
            float dx{0};
            float dy{0};
            for (auto &vec : scene_vector)
            {
                // Iterate over scene vector and implement the logic for the placement of each vector inside the Window size
                int tile_of_vec{0};
                m_sprite.setPosition(get_pos_last_tile_x+dx,get_pos_last_tile_y+dy);
                for (auto &sprites_vec : vec)
                {
                    sprites_vec = m_sprite;
                    // Put the vecs on the correct limits. 
                    sprites_vec.setPosition(x_limit + tile_of_vec * m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width, y_limit + tile_of_vec * m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height);
                    tile_of_vec++;
                }
                get_pos_last_tile_x = vec.back().getPosition().x + m_sprite.getGlobalBounds().width;
                get_pos_last_tile_y = vec.back().getPosition().y;
                // create ramdon dx and dy for each vector of tiles in a way that they are contained inside the window scene in y and x
                dx = static_cast<float>(rand() % (int)(((WINDOWX - OFFSETSCENEX)- total_element_size)/scene_vector.size() + get_pos_last_tile_x));
                dy = static_cast<float>(rand() % (int)(-get_pos_last_tile_y-(PLAYEDIM+OFFSETSCENEY) + WINDOWY-PLAYEDIM-m_sprite.getGlobalBounds().width));
            m_sprites_vec = vec;
            }
            m_scene_iter++;
        }
    }
    void Platform::draw(sf::RenderWindow *window)
    {
        for(auto& i : m_sprites_vec)
        {
            window->draw(i);
        }
        
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