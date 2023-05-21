#include "Engine.hpp"

Engine::Engine(int size_x, int size_y, std::string name_window) : m_size_window_x{size_x}, m_size_window_y{size_y}, m_name_window{name_window}
{
    this->InitWindow();
    this->InitMap();
    this->InitFloor();
    this->InitPlayer();
}

void Engine::InitMap()
{
    std::vector<std::string> path_text{TexturesPATH + std::string("building no. 1.png"),TexturesPATH + std::string("building no. 2.png"),TexturesPATH + std::string("building 3.png")};
    m_map_game = new Map::MapBackground(path_text);
}

void Engine::InitFloor()
{
    std::map<Map::FloorType,const std::string> floor_text;
    floor_text.insert(std::pair<Map::FloorType,std::string>(Map::FloorType::GRASSDIRT,std::string(TexturesPATH + std::string("grass-dirt.png"))));
    m_floor_game = new Map::Floor(floor_text,50.f,50.f);
    m_floor_game->getGrid(Map::FloorType::GRASSDIRT);
}

void Engine::InitPlayer()
{
    m_main_player = new Player(std::string(TexturesPATH + std::string("Main_Player.png")),sf::Vector2f(m_window->getSize().x/2,m_window->getSize().x/2));
}

void Engine::InitWindow()
{
    m_window = new sf::RenderWindow(sf::VideoMode(m_size_window_x,m_size_window_y),m_name_window, sf::Style::Close);
    m_window->setFramerateLimit(60);
}

void Engine::run()
{
    sf::Clock clock;
    while (m_window->isOpen())
    {
        sf::Time elapsed = clock.restart();
        this->updatePollEvents();
        this->update(elapsed);
        this->render();    
    }
    
}
void Engine::updatePollEvents()
{
    while (m_window->pollEvent(m_events))
    {
        //  "Close" Button of the window
        if(m_events.type == sf::Event::Closed)
            m_window->close();
    }

    
}

void Engine::render()
{
    m_window->clear(sf::Color::Cyan);

    m_map_game->DrawMap(m_window);
    m_floor_game->DrawFloor(m_window);
    m_main_player->render(m_window);
    m_window->display();
}

void Engine::update(sf::Time& elapsed_time)
{
    m_main_player->update(elapsed_time);
    updateScrolling();
    updateColision();
}

void Engine::updateScrolling()
{

    // Update the views's center to follow the players position
    m_view = m_window->getView();
    m_view.setCenter(m_main_player->GetPosition().x,m_view.getCenter().y);
    m_window->setView(m_view);
        
}


void Engine::updateColision()
{
    // Check if Player bound are colidding with tile the tiles vector
    for (const auto &i : m_floor_game->m_tiles)
    {
        if(m_main_player->GetGlobalBounds().top +m_main_player->GetGlobalBounds().height >= i.getGlobalBounds().top)
        {
            // Check for bottom of player in tile
            m_main_player->ResetVelocityVertical();
            m_main_player->SetPosition(sf::Vector2f(m_main_player->GetGlobalBounds().left,i.getGlobalBounds().top - m_main_player->GetGlobalBounds().height));
        }
        // Check if player is going behind the left size of the window size 
        if(m_main_player->GetGlobalBounds().left <= 0)
        {
            m_main_player->SetPosition(sf::Vector2f(0,m_main_player->GetPosition().y));
        }
    }


}

Engine::~Engine()
{
    delete m_floor_game;
    delete m_map_game;
    delete m_main_player;
    delete m_window;
}
