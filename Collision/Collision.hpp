#include "stdafx.hpp"
#include "SFML/Graphics.hpp"

class Collider
{
public:
    Collider(sf::FloatRect &body);
    ~Collider(){};

    void Move(float dx, float dy){
        m_body.left = m_body.left + dx;
        m_body.top  = m_body.top + dy; 
    }
    bool CheckCollision(Collider &other, float push);
    sf::Vector2f GetPosition() { return sf::Vector2f((m_body.left+m_body.width/2.0),m_body.top+m_body.height/2);}
    sf::Vector2f GetHalfPosition() { return sf::Vector2f((m_body.width)/2.0,(m_body.height)/2.0);};
private:
    sf::FloatRect& m_body;
};