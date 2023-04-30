#include "Engine.hpp"

Engine::Engine(int size_x, int size_y, std::string name_window) : m_size_window_x{size_x}, m_size_window_y{size_y}, m_name_window{name_window}
{
    this->InitWindow();
    this->InitMap();
    this->InitFloor();
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
    m_floor_game = new Map::Floor(floor_text);
}

void Engine::InitWindow()
{
    m_window = new sf::RenderWindow(sf::VideoMode(m_size_window_x,m_size_window_y),m_name_window, sf::Style::Close);
    m_window->setFramerateLimit(60);
}

void Engine::run()
{
    while (m_window->isOpen())
    {
        this->updatePollEvents();
        this->update();
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
    m_floor_game->DrawFloor(Map::FloorType::GRASSDIRT,m_window);
    m_window->display();
}

void Engine::update()
{
}


Engine::~Engine()
{
    delete m_floor_game;
    delete m_map_game;
    delete m_window;
}
