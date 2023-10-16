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
#include <conio.h>


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
	clist<Object*>::iterator iter;

	Menu navigationMenu([&]() {
		std::cout << " Текущее содержимое циклического списка: ";
	list.foreach([&iter](Object* ptr) {
		std::cout << " ";
		
			//*iter;
		if (*iter == ptr) std::cout << "\033[1;37;42m";
		if (ptr->identifier() == Float::identifier) std::cout << *((Float*)(ptr));
		if (ptr->identifier() == Int::identifier) std::cout << *((Int*)(ptr));
		if (ptr->identifier() == Char::identifier) std::cout << *((Char*)(ptr));
		std::cout << "\033[0m";
	});
	});
	navigationMenu.addKeyListener(75, [&iter]() {
		try {
			iter--;
		}catch (std::exception ex) {
			std::cout << "\n\n Поймано исключение: " << ex.what();
			_getch();
		}
	}, true);
	navigationMenu.addKeyListener(77, [&iter]() {
		try {
			iter++;
		}catch (std::exception ex) {
			std::cout << "\n\n Поймано исключение: " << ex.what();
			_getch();
		}
	}, true);

	enum INSERT_TYPE{
		FLOAT, CHAR, INT
	};
	enum INSERT_METHOD {
		PUSH_BACK, PUSH_FRONT, ITERATOR
	};
	INSERT_TYPE insertType;
	INSERT_METHOD insertMethod;
	iter = list.begin();

	Menu InputPage([&]() {
		
		std::cout << "Введите значение для элемента: ";
		if (insertType == INSERT_TYPE::CHAR) {
			char inputBuffer;
			safeInput(inputBuffer);
			if(insertMethod == INSERT_METHOD::PUSH_BACK)
				list.push_back((new Char(inputBuffer)));
			if(insertMethod == INSERT_METHOD::PUSH_FRONT)
				list.push_front((new Char(inputBuffer)));
			if (insertMethod == INSERT_METHOD::ITERATOR)
				list.insert(iter, new Char(inputBuffer));
		}
		if (insertType == INSERT_TYPE::INT) {
			int inputBuffer;
			safeInput(inputBuffer);
			if (insertMethod == INSERT_METHOD::PUSH_BACK)
				list.push_back((new Int(inputBuffer)));
			if (insertMethod == INSERT_METHOD::PUSH_FRONT)
				list.push_front((new Int(inputBuffer)));
			if (insertMethod == INSERT_METHOD::ITERATOR)
				list.insert(iter, new Int(inputBuffer));
		}
		if (insertType == INSERT_TYPE::FLOAT) {
			float inputBuffer;
			safeInput(inputBuffer);
			if (insertMethod == INSERT_METHOD::PUSH_BACK)
				list.push_back((new Float(inputBuffer)));
			if (insertMethod == INSERT_METHOD::PUSH_FRONT)
				list.push_front((new Float(inputBuffer)));
			if (insertMethod == INSERT_METHOD::ITERATOR)
				list.insert(iter, new Float(inputBuffer));
		}
		Menu::console.setMenu(&navigationMenu);

		if (list.size() == 1) iter = list.begin();

	}, true);
	std::list<Object*> allocatedObjects;
	Menu readFilePage([&]() {
		std::cout << " Введите имя файла или break для отмены:";
		std::string fileNameUserInput;
		std::ifstream inputStream;
		while (true) {
			std::cout << "\n input > ";
			std::cin >> fileNameUserInput;
			if (fileNameUserInput == "break") return;
			inputStream.open(fileNameUserInput);
			if (inputStream.is_open()) {
				break;
			}
			else {
				std::cout << "\033[01;38;05;15;48;05;196m\nНекорректное имя файла или файл не может быть открыт для чтения. Повторите попытку или введите break для прекращения операции\n\033[0m";
				continue;
			}
		}
		bool wasListEmpty = !list.size();
		while (true) {
			int type;
			inputStream.read((char*)&type, sizeof(int));
			if (inputStream.eof()) break;
			if (type == Float::identifier) {
				Float* obj = new Float;
				(*obj).readBinary(inputStream);
				list.push_back(obj);
			}
			if (type == Int::identifier) {
				Int* obj = new Int;
				(*obj).readBinary(inputStream);
				list.push_back(obj);
			}
			if (type == Char::identifier) {
				Char* obj = new Char;
				(*obj).readBinary(inputStream);
				list.push_back(obj);
			}
		}
		if (wasListEmpty) iter = list.begin();
		
	}, true);

	Menu writeFilePage([&]() {
		std::cout << " Введите имя файла или break для отмены:";
		std::string fileNameUserInput;
		std::ofstream outputStream;
		while (true) {
			std::cout << "\n input > ";
			std::cin >> fileNameUserInput;
			if (fileNameUserInput == "break") return;
			outputStream.open(fileNameUserInput);
			if (outputStream.is_open()) {
				break;
			}
			else {
				std::cout << "\033[01;38;05;15;48;05;196m\nНекорректное имя файла или файл не может быть открыт для записи. Повторите попытку или введите break для прекращения операции\n\033[0m";
				continue;
			}
		}
		list.foreach([&](Object* obj) {
			int identifier = obj->identifier();
			outputStream.write((char*)&identifier, sizeof(int));
			obj->writeBinary(outputStream);
		});
	}, true);

	Menu insertingPage("Выберите тип вставляемого элемента");

	MenuItem insertingPage_i1("Float", [&]() {
		insertType = INSERT_TYPE::FLOAT;
		Menu::console.setMenu(&InputPage);
	});
	MenuItem insertingPage_i2("Char", [&]() {
		insertType = INSERT_TYPE::CHAR;
		Menu::console.setMenu(&InputPage);
	});
	MenuItem insertingPage_i3("Int", [&]() {
		insertType = INSERT_TYPE::INT;
		Menu::console.setMenu(&InputPage);
	});
	insertingPage.addItem(insertingPage_i1);
	insertingPage.addItem(insertingPage_i2);
	insertingPage.addItem(insertingPage_i3);


	MenuItem nav_i1("insert", [&]() {
		insertMethod = INSERT_METHOD::ITERATOR;
		Menu::console.setMenu(&insertingPage);
	});
	MenuItem nav_i2("erase", [&]() {
		try {
			list.erase(iter);
		}
		catch (std::exception ex) {
			std::cout << "\n\n Поймано исключение: " << ex.what();
			_getch();
		}
		iter = list.begin();
	});
	MenuItem nav_i3("push_front", [&]() {
		insertMethod = INSERT_METHOD::PUSH_FRONT;
		Menu::console.setMenu(&insertingPage);
	});
	MenuItem nav_i4("push_back", [&]() {
		insertMethod = INSERT_METHOD::PUSH_BACK;
		Menu::console.setMenu(&insertingPage);
	});
	MenuItem nav_i5("readFromBinaryFile", readFilePage);
	MenuItem nav_i6("writeToBinaryFile", writeFilePage);
	navigationMenu.addItem(nav_i1);
	navigationMenu.addItem(nav_i2);
	navigationMenu.addItem(nav_i3);
	navigationMenu.addItem(nav_i4);
	navigationMenu.addItem(nav_i5);
	navigationMenu.addItem(nav_i6);



	Menu::console.setMenu(&navigationMenu);
	Menu::console.show();
	
}