#pragma once
#include <vector>
#include <cstdlib>


namespace VectorUtils{
template<typename T>
std::vector<std::vector<T>> RandomTilesVec(int max_tiles, int max_vec)
{
    
    std::vector<std::vector<T>> results;
    int number_vec = rand()%max_vec + 1;
    int number_tiles = rand()%max_tiles + 1;

    for (int i = 0; i < number_vec ; i++)
    {
        
        results.push_back(std::vector<T>(number_tiles));
        
        
    }
    
    return results;

}
}
