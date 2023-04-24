#include "Engine.hpp"


Engine::Engine(int size_x, int size_y,std::string name_window): m_window{new sf::Window(sf::VideoMode(size_x,size_y),name_window, sf::Style::Close)}
{
}

void Engine::run()
{
}

Engine::~Engine()
{
    delete m_window;
}
