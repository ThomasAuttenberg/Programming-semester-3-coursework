#include "Float.h"
#include <fstream>
#include <stdio.h>

void Float::initialize()
{
	_typeName = "Float";
	typeIdentifier = 0;
}

char* Float::to_cstring() const
{
	float value = getValue();
	auto length = _scprintf("%f", value);

	char* str = new char[length + 1];
	sprintf_s(str, length+1,"%f", value);
	return str;
}

void Float::from_cstring(const char* str)
{
	float value;
	if (sscanf_s(str, "%f", &value) != 0) {
		setContainerValue(value);
	}
	else {
		throw "Error while reading the value";
	}

}

void Float::writeBinary(std::ofstream& os) const
{
	float s = getValue();
	os.write((char*)&s, sizeof(float));
	os.flush();
}

void Float::readBinary(std::ifstream& is)
{
	float readingValue = 0;
	is.read((char*)&readingValue, sizeof(float));
	setContainerValue(readingValue);
}

Object* Float::getCopy() const
{
	return new Float(*this);
}

bool Float::operator==(Object& other) const
{
	return ((*this <=> other) == 0);
}


bool Float::operator==(Float& other) const
{
	return ((*this <=> other) == 0);
}

void Float::operator+=(const Object& other)
{
	if (other.identifier() == identifier()) {
		setContainerValue(convertContainer(other.getValue()) + getValue());
	}
}

Float& Float::operator=(const float& value)
{
	setContainerValue(value);
	return *this;
}

Float Float::operator+(const Float& other) const
{
	return Float(other.getValue() + getValue());
}
 
Float Float::operator-(const Float& other) const
{
	return Float(getValue() - other.getValue());
}

Float Float::operator*(const Float& other) const
{
	return Float(other.getValue()*getValue());
}

Float Float::operator/(const Float& other) const
{
	return Float(getValue() / other.getValue());
}

Float Float::operator+() const
{
	return *this;
}

Float Float::operator-() const
{
	return Float(-getValue());
}


std::partial_ordering Float::operator<=>(Float& other) const
{
	return (getValue() <=> other.getValue());
}

std::partial_ordering Float::operator<=>(Object& other) const
{

	if (typeIdentifier != other.identifier()) return std::partial_ordering::unordered;
	float otherValue = convertContainer(other.getValue());
	return (getValue() <=> otherValue);

}


float Float::convertContainer(void* value) const
{
	return *static_cast<float*>(value);
}

Float::Float(){ 
	setContainerValue(0);
	initialize(); 
}

Float::Float(float value) : Object(value){ initialize(); }

Float::Float(const Float& value) : Object((Object&)value){ initialize(); }

Float::Float(Float&& value) : Object((Object&&)(value)) { initialize(); }

Float& Float::operator=(const Float& other)
{
	Object::operator=((Object&)other);
	return *this;
}

Float& Float::operator=(Float&& other)
{
	Object::operator=((Object&&)(other));
	return *this;
}

float Float::getValue() const
{
	return convertContainer(Object::getValue());
}

std::ostream& operator<<(std::ostream& os, const Float& obj)
{
		return os << obj.getValue();
}

std::istream& operator>>(std::istream& is, Float& obj)
{
	float value;
	is >> value;
	if (std::cin.good()) obj.setContainerValue(value);
	return is;
}
