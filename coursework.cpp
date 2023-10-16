// coursework.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <vector>
#include "Primitive.h"
#include <fstream>
#include <string>
#include <typeinfo>
#include <sstream>
#include <list>
#include "clist.h"
#include "Menu.h"


template <class T>
void safeInput(T& value) {
	
	while (!(std::cin >> value)) {
			std::cout << "\033[01;38;05;15;48;05;196mНекорректный ввод. Повторите попытку\033[0m\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
;		}

}


int main()
{
	system("chcp 1251");
	system("cls");

	clist<Object*> list;
	
	Menu navigationMenu([&]() {
		list.foreach([](Object* ptr) {

			

			});
		});

	Menu intInseringPage([&]() {
		
		std::cout << "Введите значение для элемента:\n";
		Int k;
		safeInput(k);
		std::cout << k;
		Menu::console.setMenu(&navigationMenu);

	}, true);
	MenuItem nav_i1("push_front", intInseringPage);
	navigationMenu.addItem(nav_i1);

	Menu::console.setMenu(&intInseringPage);
	Menu::console.show();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
