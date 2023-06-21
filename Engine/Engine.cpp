#include "Engine.hpp"

Engine::Engine(int size_x, int size_y, std::string name_window) : m_size_window_x{size_x}, m_size_window_y{size_y}, m_name_window{name_window}
{
    this->InitWindow();
    this->InitMap();
    this->InitTiles();
    this->InitPlayer();
}

void Engine::InitMap()
{
    std::vector<std::string> path_text{TexturesPATH + std::string("building3.png"), TexturesPATH + std::string("building1.png"), TexturesPATH + std::string("building2.png")};
    m_map_game = new Map::MapBackground(path_text);
}

void Engine::InitTiles()
{
    // Load the image using OpenCV
    cv::Mat image_floor = cv::imread(TexturesPATH + std::string("Tiles/Grass/Grass_13-128x128.png"),cv::IMREAD_COLOR);

    if (image_floor.empty())
    {
        std::cerr << "Failed to load the image." << std::endl;
        throw(std::string("Failed to load the image."));
    }

    // Floor
    m_tiles[Map::FloorType::FLOOR] = Map::TileFactory::createTile(image_floor, Map::FloorType::FLOOR);
}

void Engine::InitPlayer()
{
    m_main_player = new Player(std::string(TexturesPATH + std::string("Main_Player.png")), sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().x / 2));
    m_pos_player_update = m_main_player->GetPosition().x;
    m_main_player->SetGroundLevel(sf::Vector2f(0, m_tiles[Map::FloorType::FLOOR]->getSprite().front().getGlobalBounds().top));
}

void Engine::InitWindow()
{
    m_window = new sf::RenderWindow(sf::VideoMode(m_size_window_x, m_size_window_y), m_name_window, sf::Style::Close);
    m_window->setFramerateLimit(60);
}

void Engine::run()
{
    sf::Clock clock;
    m_window->setVerticalSyncEnabled(true);
    while (m_window->isOpen())
    {
        sf::Time elapsed = clock.restart();
        this->updatePollEvents();
        this->update(elapsed);
        std::cout << "Player Positionx: "<< m_main_player->GetPosition().x << std::endl;
        std::cout << "Player Positiony: "<< m_main_player->GetPosition().y << std::endl;
        this->render();
    }
}
void Engine::updatePollEvents()
{
    while (m_window->pollEvent(m_events))
    {
        //  "Close" Button of the window
        if (m_events.type == sf::Event::Closed)
            m_window->close();
    }
}

void Engine::render()
{
    
    m_window->clear(sf::Color::Cyan);
    m_map_game->DrawMap(m_window);
    for (auto &i : m_tiles)
    {
        i.second->draw(m_window);
    }
    m_main_player->render(m_window);

    m_window->display();
}

void Engine::update(sf::Time &elapsed_time)
{
    m_main_player->update(elapsed_time, m_events);
    float curr_pos_player = m_main_player->GetPosition().x;
    updateScrolling(curr_pos_player);
    updateColision();
}

void Engine::updateScrolling(float curr_pos_player)
{
    m_view = m_window->getView();

    // sf::Vector2f playePosition = m_main_player->GetPosition();
    sf::Vector2f viewCenter = m_view.getCenter();

    if (m_pos_player_update == m_main_player->GetPosition().x)
    {
        // Update the views's center to follow the players position
        m_view.setCenter(viewCenter);
        m_window->setView(m_view);
    }
    if (viewCenter.x < m_main_player->GetPosition().x)
    {
        // Follow the view right
        m_view.setCenter(m_main_player->GetPosition().x, viewCenter.y);
        m_window->setView(m_view);
        m_pos_player_update = m_main_player->GetPosition().x;
    }
}

void Engine::updateColision()
{
    // Check if Player bound are colidding with tile the tiles vector
    for (const auto &[tile_type,tile] : m_tiles)
    {
        if(tile_type == Map::FloorType::FLOOR)
        {
            for(const auto & floor_tile : tile->getSprite())
            {
                if (m_main_player->GetGlobalBounds().intersects(floor_tile.getGlobalBounds()))
                {
                    std::cout << "Floor tile Positionx: "<< floor_tile.getPosition().x << std::endl;
                    std::cout << "Floor tile Positiony: "<< floor_tile.getPosition().y << std::endl;
                    // Check for bottom of player in tile
                    m_main_player->ResetVelocityVertical();
                    m_main_player->SetPosition(sf::Vector2f(m_main_player->GetPosition().x, floor_tile.getPosition().y)); // TODO: SOLVE THIS PROBLEM HERE
                    m_main_player->SetGroundLevel(sf::Vector2f(0, floor_tile.getGlobalBounds().top));
                }
            }
        }

    }

    // Make Player Colide with the left wall everytime it moves
    if (m_main_player->GetGlobalBounds().left <= m_view.getCenter().x - m_view.getSize().x / 2)
    {
        m_main_player->SetPosition(sf::Vector2f(m_view.getCenter().x - m_view.getSize().x / 2, m_main_player->GetPosition().y));
    }
}

Engine::~Engine()
{
    delete m_map_game;
    delete m_main_player;
    delete m_window;
}
