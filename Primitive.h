#pragma once
#include "Object.h"
#include <typeinfo>
#include <string>
#include <sstream>
#include <fstream>



template <typename T>
concept primitive = std::is_fundamental<T>::value;

template <primitive T>
class Primitive :
    private Object
{
private:

	T convertContainer(void* value) const;
	friend std::istream& operator>>(std::istream& is, Primitive& obj);

public:

	Primitive();
	Primitive(T value);
	Primitive(const Primitive<T>& value);
	Primitive(Primitive<T>&& value);
	Primitive<T>& operator=(const Primitive<T>& other);
	Primitive<T>& operator=(Primitive<T>&& other);
	T getValue() const;

	void initialize() override;
	char* to_cstring() const override;
	void from_cstring(const char*) override;
	void writeBinary(std::ofstream&) const override;
	void readBinary(std::ifstream&) override;
	Object* getCopy() const override;

	std::partial_ordering operator<=>(const Object& other) const override;
	bool operator==(Object& other) const override;

	std::partial_ordering operator<=>(const Primitive<T>& other) const;
	bool operator==(Primitive<T>& other) const;

	void operator+=(const Object& other) override;
	Object& operator+(const Object& other) const override;
	void operator+=(const Primitive<T>& other);
	void operator-=(const Primitive<T>& other);
	Primitive<T>& operator=(const T& value);
	Primitive<T> operator+(const Primitive<T>& other) const;
	Primitive<T> operator-(const Primitive<T>& other) const;
	Primitive<T> operator*(const Primitive<T>& other) const;
	Primitive<T> operator/(const Primitive<T>& other) const;
	Primitive<T> operator+() const;
	Primitive<T> operator-() const;

};

template<primitive T>
inline T Primitive<T>::convertContainer(void* value) const
{
	return *((T*)value);
};

template<primitive T>
inline Primitive<T>::Primitive() : Object()
{
	initialize();
};

template<primitive T>
inline Primitive<T>::Primitive(T value) : Object(value)
{
	initialize();
};

template<primitive T>
inline Primitive<T>::Primitive(const Primitive<T>& value) : Object((Object&)value)
{
	initialize();
};

template<primitive T>
inline Primitive<T>::Primitive(Primitive<T>&& value) : Object((Object&&)value)
{
	initialize();
};

template<primitive T>
inline Primitive<T>& Primitive<T>::operator=(const Primitive<T>& other)
{
	Object::operator=(other);
	return *this;
};

template<primitive T>
inline Primitive<T>& Primitive<T>::operator=(Primitive<T>&& other)
{
	Object::operator=(std::move(other));
	return *this;
};

template<primitive T>
inline T Primitive<T>::getValue() const
{
	return *((T*)Object::getValue());
};

template<primitive T>
inline void Primitive<T>::initialize()
{
	_typeName = typeid(T).name();
	typeIdentifier = typeid(T).hash_code();
};

template<primitive T>
inline char* Primitive<T>::to_cstring() const
{
	std::string value = std::to_string(getValue());
	const char* str = value.c_str();
	char* nonConstStr = new char[strlen(str) + 1];
	strcpy_s(nonConstStr, strlen(str)+1, str);
	return nonConstStr;

};

template<primitive T>
inline void Primitive<T>::from_cstring(const char* str)
{
	T value = 0;
	std::istringstream(std::string(str)) >> value;
	setContainerValue(value);

};

template<primitive T>
inline void Primitive<T>::writeBinary(std::ofstream& os) const
{
	T value = getValue();
	os.write((char*)&value, sizeof(T));
	os.flush();

};

template<primitive T>
inline void Primitive<T>::readBinary(std::ifstream& is)
{
	T value = 0;
	is.read((char*)&value, sizeof(T));
	setContainerValue(value);
};

template<primitive T>
inline Object* Primitive<T>::getCopy() const
{
	return new Primitive<T>(*this);
};

template<primitive T>
inline bool Primitive<T>::operator==(Object& other) const
{
	if (typeIdentifier != other.identifier()) return false;
	T otherValue = convertContainer(other.getValue());
	return (getValue() <=> otherValue) == 0;
};

template<primitive T>
inline bool Primitive<T>::operator==(Primitive<T>& other) const
{
	return getValue() <=> other.getValue() == 0;
};

template<primitive T>
inline void Primitive<T>::operator+=(const Object& other)
{
	if (typeIdentifier != other.identifier()) return;
	setContainerValue(getValue() + convertContainer(other.getValue()));
};


template<primitive T>
inline Object& Primitive<T>::operator+(const Object& other) const
{
	if (typeIdentifier != other.identifier()) return *((Object*)this);
	Primitive<T> newObject(convertContainer(other.getValue()) + getValue());
	return newObject;
};

template<primitive T>
inline Primitive<T>& Primitive<T>::operator=(const T& value)
{
	setContainerValue(value);
	return *this;
};

template<primitive T>
inline Primitive<T> Primitive<T>::operator+(const Primitive<T>& other) const
{
	return Primitive<T>(other.getValue() + getValue());
};

template<primitive T>
inline Primitive<T> Primitive<T>::operator-(const Primitive<T>& other) const
{
	return Primitive<T>(getValue() - other.getValue());
};

template<primitive T>
inline Primitive<T> Primitive<T>::operator*(const Primitive<T>& other) const
{
	return Primitive<T>(getValue() * other.getValue());
};

template<primitive T>
inline Primitive<T> Primitive<T>::operator/(const Primitive<T>& other) const
{
	return Primitive<T>(getValue() / other.getValue());
};

template<primitive T>
inline void Primitive<T>::operator+=(const Primitive<T>& other)
{
	*this = *this + other;
};

template<primitive T>
inline void Primitive<T>::operator-=(const Primitive<T>& other)
{
	*this = *this - other;
};

template<primitive T>
inline Primitive<T> Primitive<T>::operator+() const
{
	return *this;
};

template<primitive T>
inline Primitive<T> Primitive<T>::operator-() const
{
	return Primitive<T>(-getValue());
}

template<primitive T>
inline std::partial_ordering Primitive<T>::operator<=>(const Primitive<T>& other) const
{
	return getValue() <=> other.getValue();
};

template<primitive T>
inline std::partial_ordering Primitive<T>::operator<=>(const Object& other) const
{
	if (typeIdentifier != other.identifier()) return std::partial_ordering::unordered;
	T otherValue = convertContainer(other.getValue());
	return (getValue() <=> otherValue);
};

template <primitive T>
std::ostream& operator<<(std::ostream& os, const Primitive<T>& obj) {
	os << obj.getValue();
	return os;
};

template <primitive T>
std::istream& operator>>(std::istream& is, Primitive<T>& obj) {
	T value;
	is >> value;
	obj.setContainerValue(value);
	return is;
};

typedef Primitive<float> Float;
typedef Primitive<int> Int;
typedef Primitive<char> Char;
typedef Primitive<double> Double;