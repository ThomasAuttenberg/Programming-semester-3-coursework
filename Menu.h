#pragma once
#include "ConsoleFrame.h"
#include "clist.h"

const char BACKWARD_BUTTON_TEXT[] = "BACK";

// экшн можно унаследовать от меню, метод шоу сделать виртуальным и выполнять внутри метода шоу
// экшна переданную ф-цию

class Action {


};

class Menu
{
private:
    friend struct Item;
    clist<MenuItem> items;
    const char* text  = nullptr;
    std::function<void(void)> printingFunction = nullptr;
    Menu* where_called_from = nullptr;
    bool isInputMenu = false;

public:

    struct Item {
   
        friend class Menu;
        Menu* goToRef = nullptr;
        Menu* location = nullptr;
        std::function<void()> action = nullptr;
        const char* label;
    
        Item(const char* label , Menu& goToRef);
        Item(const char* label, std::function<void(void)> action);
        void go();
    };
    
    Menu(const char* text);
    Menu(std::function<void(void)> printingFunction, bool isInputMenu = false);
    void addItem(Item item);
    void show();
};

typedef Menu::Item MenuItem;

*/