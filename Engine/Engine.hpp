#include "stdafx.hpp"
#include "Enteties.hpp"
#include "SFML/Graphics.hpp" 
#include "SFML/Window.hpp"

class Engine
{

public:
    Engine(int size_x, int size_y,std::string name_window);
    void updatePollEvents();
    void run();
    ~Engine();
private:
    // Main window of the Game
    sf::RenderWindow* m_window;
    int m_size_window_x;
    int m_size_window_y;
    std::string m_name_window;
    void InitWindow();

    //Map  
    Map::MapBackground *m_map_game;
    void InitMap();   

    //Floor
    Map::Floor *m_floor_game;
    void InitFloor();
        
    // Main Events of the game
    sf::Event m_events;

    // Render Function
    void render(); 

    // Update Function
    void update();
};
