#pragma once
#include <stdlib.h>
#include <iostream>

class Object_basic
{
private:
	void* value;
	size_t size;
public:

	Object_basic(const Object_basic& obj) {
		void* valueBuffer = malloc(sizeof(obj.size));
		if (valueBuffer == NULL) {
			std::cerr << "Out of memory. Object hasn't been copied";
		}
		else {
			this->size = obj.size;
			value = valueBuffer;
			memcpy(this->value, obj.value, size);
		}
	}

	Object_basic(Object_basic&& obj) {
		void* valueBuffer = malloc(sizeof(obj.size));
		if (valueBuffer == NULL) {
			std::cerr << "Out of memory. Object hasn't been moved";
		}
		else {
			this->size = obj.size;
			value = valueBuffer;
			memcpy(this->value, obj.value, size);
		}
	}

	Object_basic(void* value, size_t size) {
		this->size = size;
		this->value = malloc(size);
		if (this->value == NULL) {
			throw "Out of memory. Object hasn't been created";
		}
		else {
			memcpy(this->value, value, size);
		}
	}

	Object_basic& operator=(const Object_basic& obj) {
		if (this != &obj) {
			void* valueBuffer = malloc(sizeof(obj.size));
			if (valueBuffer == NULL) {
				std::cerr << "Out of memory. Object hasn't been copied";
			}
			else {
				this->size = obj.size;
				value = valueBuffer;
				memcpy(this->value, obj.value, size);
			}
			return *this;
		}
	}

	Object_basic& operator=(Object_basic&& obj) {
		if (this != &obj) {
			this->size = obj.size;
			value = obj.value;
			return *this;
		}
	}

	void* getValue() {
		return value;
	}
	~Object_basic() {
		free(value);
	}

};

