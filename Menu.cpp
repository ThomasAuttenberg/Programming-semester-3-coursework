#include "Menu.h"
#include <conio.h>
#include <windows.h>



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

Menu::Item::Item(const Item& other)
{
	this->action = other.action;
	this->goToRef = other.goToRef;
	this->label = other.label;
	this->location = other.location;
}


void Menu::Item::go() {
	if (goToRef != nullptr) {
		if (location != nullptr) {
			if(this->goToRef != location->where_called_from)
				this->goToRef->where_called_from = location;
		}
		this->goToRef->show();
	}
	if (action != nullptr) {
		action();
	}
}

void Menu::printButtons(clist<Menu::Item>::iterator& selected)
{
		std::cout << "\n";
		items.foreach([&](Item& item) -> void {
			if (&(*selected) == &item) {
				int label_length = strlen(item.label);
				std::cout << "\n"<<"\033[0;30;47m" << item.label << std::string(ITEM_LABEL_MAX_LENGTH - label_length, ' ') << "\033[0m";
			}
			else {
				std::cout << "\n" << item.label;
			}
			});
		std::cout << "\n";
}

char Menu::getch()
{
	char n = _getch();
	if (n != 224 && n != -32) return n;
	return _getch();
}

Menu::Menu(const char* text)
{
	this->text = text;

}

Menu::Menu(std::function<void(void)> printingFunction, bool isInputMenu)
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
	if (isInputMenu == true) {
		if (text != nullptr)
			std::cout << text;
		if (printingFunction != nullptr)
			printingFunction();
		if (where_called_from != nullptr) where_called_from->show();
	}
	else {
		auto selectedButton = items.begin();
		int pressedKey = -1;
		if (where_called_from != nullptr && !backButtonSetted) {
			Item newItem(BACKWARD_BUTTON_TEXT, *where_called_from);
			items.push_back(newItem);
			backButtonSetted = true;
		}
		while (1) {
			do {
				switch (pressedKey) {
				case 80: selectedButton++; break;
				case 72: selectedButton--; break;
				}
				system("cls");

				if (text != nullptr)
					std::cout << text;

				if (printingFunction != nullptr)
					printingFunction();

				printButtons(selectedButton);

			} while ((pressedKey = getch()) != 13);

			if ((*selectedButton).action != nullptr) {
				(*selectedButton).action();
				system("cls");
				//show();
			}
			else {
				if ((*selectedButton).goToRef != nullptr) {
					break;
				}
			}

		}
		(*selectedButton).go();
	}
}
