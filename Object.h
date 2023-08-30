#pragma once

#include <concepts>
#include <iostream>
#include <memory>
#include <functional>

/*
	Abstract class, having the certain definitions to save any copyable type value in it.
	Declarates several pure virtual functions to use Object as the interface to manipulate subclasses.

	[Derived classes rules]: 
	* typeIdentifier and _typeName fields must be initialized 
	by inserting correct defined initialize() function in every constructor.
	* use Object constructors instead of creating derived class own value-saving logic
		example: Int(int value) : Object(value){initialize()};
				 Int(const Int& other) : Object((Object&)other){initialize()};

*/

// Following templates specification: 
// " template members of Object can be used only if T - isn't an Object and can be copyied using constructor "
class Object;
template <typename T>
concept copyable = std::is_copy_constructible<T>::value == true && !(std::is_same<T, Object>::value);

class Object
{
private:

	void* container = nullptr;
	size_t size = 0; //container memory size
	std::function<void(void*)> destructor = nullptr; //container destructor
	

protected:
	
	int typeIdentifier;
	const char* _typeName;

	// setter function template uses to copy any copyable value other then Object into container memory
	template <copyable T>
	void setContainerValue(const T& value) {
		if(destructor != nullptr) destructor(container); // container memory release
		container = new T(value); // new memory allocation
		size = sizeof(T);
		destructor = [](void* ptr) -> void { delete (T*)ptr; }; //correct container memory release lamda-function
	}

public:

	Object(); // No-args constructor

	Object(Object&& other); //Move constructor

	Object(const Object& other); //Copy constructor

	Object& operator=(const Object& other); //Copy assigment operator

	Object& operator=(Object&& other); //Move assigment operator

	void* getValue() const; //container getter

	int identifier() const; //returns the class (subclass) typeIdentifier

	const char* typeName() const; //returns the class (subclass) _typeName

	virtual ~Object();

	// Constructor template 
	template <copyable T>
	explicit Object(const T& value) {
		container = new T(value);
		destructor = [](void* ptr) -> void { delete (T*)ptr; }; //correct container memory release lamda-function
		size = sizeof(T);
	}

	/*
		PURE VIRTUAL FUNCTIONS:
	*/

	virtual void initialize() = 0; // May be used to inicialize type identification fields 

	virtual char* to_cstring() const = 0; // Uses to represent value as a char string

	virtual void from_cstring(const char*) = 0; // Uses to scan value from a char string

	virtual void writeBinary(std::ofstream&) const = 0; // Uses to convert value into a byte set.

	virtual void readBinary(std::ifstream&) = 0; // Uses to take value from a binary stream

	virtual Object* getCopy() const = 0; // Uses to return pointer to a new derived class examplar - copy of initial.

	virtual std::partial_ordering operator<=>(const Object& other) const = 0; // "Space ship" operator - basic operator uses to comparing Objects (C++20)

	virtual Object& operator+(const Object& other) const = 0; // Objects combination(addition)

	virtual void operator+=(const Object& other) = 0; 
	
	virtual bool operator==(Object& other) const = 0; // Another basic comparing operator


};