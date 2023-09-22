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

int main()
{

	//menu: 

	float ca = 0;
	ca++;
	std::ifstream is;
	void* n;
	int sss = 0;
	clist<float> s = { 12,3,4,5 };
	clist<float>::iterator a = s.begin();
	auto dd = a;
	dd++;
	dd++;
	s.erase(a, dd);
	
	const std::list<int> sssss;

	s.foreach([&](clist<float>::elem value){
		
		value++;
		sss += 1;

	});
	s.foreach([&](clist<float>::elem value) {

		std::cout << value;

	});
	clist<float>::iterator z = s.begin();
	clist<float>::iterator v = s.begin();
	s.erase(s.begin() , s.begin());
	std::function<void(const clist<int>::iterator)> h;
	
	/*//clist<int>::iterator k;
	is.open("meow");
	//Float c(12.5);
	//Float* s = new Float[25];
	//char* str = c.to_cstring();
	str[3] = '2';
	Float k;
	Int csd;
	k.from_cstring(str);
	std::string sss;;
	std::cout << typeid(c).hash_code() << " " << typeid(csd).hash_code();
	*/
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
