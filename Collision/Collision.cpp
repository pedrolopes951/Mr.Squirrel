#include "Collision.hpp"

Collider::Collider(sf::FloatRect &body) : m_body{body}
{
}

Collision Collider::CheckCollision(Collider &other)
{

    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfPosition = other.GetHalfPosition();
    sf::Vector2f thisPosition = this->GetPosition();
    sf::Vector2f thisHalfPosition = this->GetHalfPosition();

    // Check if collision is detected
    float delta_x = otherPosition.x - thisPosition.x;
    float delta_y = otherPosition.y - thisPosition.y;
    float intersect_x = abs(delta_x) - (otherHalfPosition.x + thisHalfPosition.x);
    float intersect_y = abs(delta_y) - (otherHalfPosition.y + thisHalfPosition.y);

    std::cout << "Collision delta x : " << delta_x << "\n";
    std::cout << "Collision delta y : " << delta_y << "\n";
    std::cout << "Collision intersect x : " << intersect_x << "\n";
    std::cout << "Collision intersect y  : " << intersect_y << "\n";

    if (intersect_x <= 0.0f && intersect_y <= 0.0f)
    {
        if (intersect_x > intersect_y)
        {
            if (delta_x > 0.f)
            {

                return Collision::SIDERIGHT;
            }
            else
            {
                return Collision::SIDELEFT;
            }
        }
        else
        {
            if (delta_y > 0.f)
            {
                return Collision::TOP;
            }
            else
            {
                return Collision::BOTTOM;
            }
        }
    }

    return Collision::NOCOLLISION;
}
