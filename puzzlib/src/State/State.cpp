#include "State.h"

namespace puzz
{
    void StateManager::startUp()
    {
    }

    void StateManager::shutDown()
    {
    }

    void StateManager::Tick()
    {
        // int input = 0,cnt = 1;
        // std::cout << "[Current State]: " << CurState->getName() << std::endl;
        // auto list = CurState->getTransList();
        // for(auto [E,S]:list)
        // {
        //     std::cout << "[" << cnt++ << "] ";
        //     std::cout << "[" << E->getName() << "]: " << S->getName() << std::endl;
        // }
        // std::cout << "[Please input your choice]: ";
        // std::cin >> input;
        // if(input > 0 && input <= list.size())
        // {
        //     auto Choose = list.at(input - 1);
        //     if(Choose.first -> Handle())
        //     {
        //         Update(Choose.second);
        //     }
        //     else
        //     {
        //         std::cout << "[Invalid handle]" << std::endl;
        //     }
        // }
        // else
        // {
        //     std::cout << "[Invalid input]" << std::endl;
        // }
    }
}