#pragma once

#include <concepts>
#include <iostream>
#include <memory>
#include <functional>

class Object;
template <typename T>
concept copyable = std::is_copy_constructible<T>::value == true && !(std::is_same<T, Object>::value);

class Object
{
private:

	void* container = nullptr;
	size_t size = 0;
	std::function<void(void*)> destructor = nullptr;
	

protected:
	
	int typeIdentifier;
	const char* _typeName;


	template <copyable T>
	void setContainerValue(const T& value) {
		if (sizeof(T) == size) {
			memcpy(container, &value, size);
		}
		else {
			if(destructor != nullptr) destructor(container);
			container = new T(value);
			size = sizeof(T);
		}
		destructor = [](void* ptr) -> void { delete (T*)ptr; };
	}

public:

	Object();

	Object(Object&& other);

	Object(const Object& other);

	Object& operator=(const Object& other);

	Object& operator=(Object&& other);

	void* getValue();

	int identifier();

	const char* typeName();

	virtual ~Object();

	template <copyable T>
	Object(const T& value) {
		container = new T(value);
		destructor = [](void* ptr) -> void { delete (T*)ptr; };
		size = sizeof(T);
	}

	virtual void initialize() = 0;

	virtual void serialize(char*) = 0;

	virtual void deserialize(const char*) = 0;

	virtual void writeBinary(std::ofstream) = 0;

	virtual void readBinary(std::ifstream) = 0;

	virtual Object* getCopy() = 0;

	virtual std::partial_ordering operator<=>(Object& other) = 0;
	
	virtual bool operator==(Object& other) = 0;

};