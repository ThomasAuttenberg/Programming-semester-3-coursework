#include "Menu.h"

Menu::Item::Item(const char* label, Menu& goToRef)
{
	this->label = label;
	this->goToRef = &goToRef;
}

Menu::Item::Item(const char* label, std::function<void(void)> action)
{
	this->label = label;
	this->action = action;
}

Menu::Item::Item(const char* label, Menu& goToRef)
{
	this->label = label;
	this->goToRef = &goToRef;
	this->action = action;
}

void Menu::Item::go() {
	if (goToRef != nullptr) {
		if (location != nullptr) {
			this->goToRef->where_called_from = location;
		}
		this->goToRef->show();
	}
	if (action != nullptr) {
		action();
	}
}

Menu::Menu(const char* text) : Menu(text)
{
	this->text = text;
	if (where_called_from != nullptr)
		items.push_back( new Item(BACKWARD_BUTTON_TEXT, *where_called_from) );
}

Menu::Menu(std::function<void(void)> printingFunction, bool isInputMenu) : Menu(printingFunction)
{
	this->printingFunction = printingFunction;
	this->isInputMenu = isInputMenu;
}

void Menu::addItem(Item item) {
	if(where_called_from != nullptr) items.shift_forward();
	item.location = this;
	items.push_back(item);
	if(where_called_from != nullptr) items.shif_backward();
}

void Menu::show()
{

	do {
		system("cls");

		if (text != nullptr)
			printf(text);

		if (printingFunction != nullptr)
			printingFunction();

		if (isInputMenu == true)
			where_called_from->show();
		else {

			items.foreach([](Item& menu) {

				std::cout <<

				});

		}
	}while(!isInputMenu )
	
	
}
