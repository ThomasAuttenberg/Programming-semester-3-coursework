#pragma once
#include <initializer_list>
#include <functional>

struct MenuItem {
	const char* text;
	Menu* ref;
	MenuItem(const char* text, Menu& menu);
};
// меняем меню ластреф на меню в котором расположен менюайтем

// экшн можно унаследовать от меню, метод шоу сделать виртуальным и выполнять внутри метода шоу
// экшна переданную ф-цию

class Action {


};

class Menu
{
	Menu* lastRef;
	const char* menuText;

public:

	Menu(const char* text, std::initializer_list<MenuItem>);
	Menu(const char* text, std::function<void(void)>);
	void show();

};

/*

Menu("Meow meow", add_b, remove);
MenuItem add_b("add b", new InputWindow("Meow", "%d", )

*/