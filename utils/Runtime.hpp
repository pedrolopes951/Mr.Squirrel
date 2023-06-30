#pragma once
#include <vector>
#include <cstdlib>


namespace VectorUtils{
template<typename T>
std::vector<std::vector<T>> RandomTilesVec(int random_key, int max_tiles, int max_vec)
{
    int number_of_tiles{};
    int random_of_vec{};
    std::vector<std::vector<T>> results;
    for (size_t i = 0; i < random_key%max_vec; i++)
    {
        
        results.push_back(std::vector<T>(random_key%max_tiles));
        
        
    }
    
    return results;

}
}
