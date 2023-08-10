#include "stdafx.hpp"
#include "Enteties.hpp"
#include "Player.hpp"
#include "SFML/Graphics.hpp" 
#include "SFML/Window.hpp"
// #include <opencv4/opencv2/opencv.hpp>


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

    // View for side Scrolling
    sf::View m_view;

    //Map  
    Map::MapBackground *m_map_game;
    void InitMap();   

    //TIles
    Map::TileFactory m_tilefactory;
    std::map<Map::FloorType, Map::ITiles*> m_tiles;
    void InitTiles(); 

    // Player
    Player* m_main_player;
    float m_pos_player_update; 
    void InitPlayer();
        
    // Main Events of the game
    sf::Event m_events;

    // Render Function
    void render(); 

    // Update Function
    void update(sf::Time& elapsed_time);
    void updateScrolling(float curr_position);
    void updateColision();
};

 
