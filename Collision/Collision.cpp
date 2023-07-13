#include "Collision.hpp"

Collider::Collider(sf::FloatRect &body) : m_body{body}
{


}

bool Collider::CheckCollision(Collider &other, float push)
{

    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfPosition = other.GetHalfPosition();
    sf::Vector2f thisPosition = this->GetPosition();
    sf::Vector2f thisHalfPosition= this->GetHalfPosition();

    // Check if collision is detected
    float delta_x = otherPosition.x - thisPosition.x;
    float delta_y = otherPosition.y - thisPosition.y;
    float intersect_x  = abs(delta_x) - (otherHalfPosition.x + thisHalfPosition.x);
    float intersect_y  = abs(delta_y) - (otherHalfPosition.y + thisPosition.y);

    if(intersect_x <= 0.0f && intersect_y <= 0.0f)
    {
        push = std::min(std::max(push, 0.f),1.f); // Clamp the push value 

        if( intersect_x > intersect_y)
        {
            if (delta_x > 0.f)
            {
                this->Move(intersect_x * (1.0f - push), 0.0f);
                other.Move(-intersect_x*push, 0.0f);
            }
            else {
                this->Move(-intersect_x * (1.0f - push), 0.0f);
                other.Move(intersect_x*push, 0.0f);
            }
        }
        else{
              if (delta_y > 0.f)
            {
                this->Move(intersect_y * (1.0f - push), 0.0f);
                other.Move(-intersect_y*push, 0.0f);
            }
            else {
                this->Move(-intersect_y * (1.0f - push), 0.0f);
                other.Move(intersect_y*push, 0.0f);
            }
        }
        return true;
    }

    return false;
}
