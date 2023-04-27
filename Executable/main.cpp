#include "stdafx.hpp"
#include "Engine.hpp"

int main(int argc, char * argv[])
{
    std::shared_ptr<Engine> Game  = std::make_shared<Engine>(800,600,"SideScroller");
    Game->run();

}