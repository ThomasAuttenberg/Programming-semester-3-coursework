#pragma once
#include "ConsoleFrame.h"
#include "clist.h"

const char BACKWARD_BUTTON_TEXT[] = "<- Back";
const int ITEM_LABEL_MAX_LENGTH = 50;

class Menu
{
public:
    struct Item;
private:
    friend struct Item;
    clist<Menu::Item> items;
    bool backButtonSetted = false;
    const char* text  = nullptr;
    std::function<void(void)> printingFunction = nullptr;
    Menu* where_called_from = nullptr;
    bool isInputMenu = false;
    void printButtons(clist<Menu::Item>::iterator&);
    char getch();
public:

    struct Item {
   
        friend class Menu;
        Menu* goToRef = nullptr;
        Menu* location = nullptr;
        std::function<void()> action = nullptr;
        const char* label;
    
        Item() = default;
        Item(const char* label , Menu& goToRef);
        Item(const char* label, std::function<void(void)> action);
        Item(const Item& other);
        void go();
    };
    
    Menu(const char* text);
    Menu(std::function<void(void)> printingFunction, bool isInputMenu = false);
    void addItem(Item item);
    void show();
};

typedef Menu::Item MenuItem;

