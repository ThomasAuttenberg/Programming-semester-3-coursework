#pragma once
#include "Menu.h"
#include <functional>
class InputWindow :
    public Menu
{
    InputWindow(std::function<void(void)>)
};

