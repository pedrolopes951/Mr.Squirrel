#include "stdafx.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Engine
{
private:
    sf::Window* m_window;
public:
    Engine(int size_x, int size_y,std::string name_window);
    void run();
    ~Engine();
};
