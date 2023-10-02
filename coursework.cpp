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

int main()
{
	system("chcp 1251");
	system("cls");

	float ca = 0;
	ca++;
	std::ifstream is;
	void* n;
	int sss = 0;
	std::list<float> lis;
	//lis.pop_back();
	clist<float> list = { 13,12,5,3,5 };
	list.foreach([](float s) {
		
		
		
	});

	Menu a("How are you today?");
	Menu b([&]()-> void {
		
		list.foreach([](float s) {
			std::cout << s << " ";
			});
		std::cout << "\n";
	});
	MenuItem a1("How's it",b);
	a.addItem(a1);
	MenuItem b1("Delete the last", [&]() {
		list.pop_back();
	});
	b.addItem(b1);
	a.show();
	
	/* 
	//clist<int>::iterator k;
	//is.open("meow");
	//Float c(12.5);
	//Float* s = new Float[25];
	//char* str = c.to_cstring();
	//str[3] = '2';
	//Float k;
	//Int csd;
	//k.from_cstring(str);
	//std::string sss;;
	//std::cout << typeid(c).hash_code() << " " << typeid(csd).hash_code();
	//*/
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
