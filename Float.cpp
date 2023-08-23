#include "Float.h"
#include <fstream>

void Float::initialize()
{
	_typeName = "Float";
	typeIdentifier = 0;
}

void Float::serialize(char* str)
{
	sprintf(str, "%f", getValue());
}

void Float::deserialize(const char* str)
{
	float value;
	if (sscanf(str, "%f", &value) != 0) {
		setContainerValue(value);
	}
	else {
		throw "Error while reading the value";
	}

}

void Float::writeBinary(std::ofstream os)
{
	char* buffer = (char*)malloc(sizeof(float));
	serialize(buffer);
	float s = getValue();
	os.write((char*)&s, sizeof(float));
	free(buffer);
}

void Float::readBinary(std::ifstream is)
{
	float readingValue;
	char* buffer = (char*)malloc(sizeof(float));
	if (buffer == nullptr) throw "Memory allocation error";
	is.read(buffer, sizeof(float));
	if (sscanf(buffer, "%f", &readingValue) != 0) {
		setContainerValue(readingValue);
	}
	else {
		throw "Error while reading the value";
	}
	free(buffer);
	
}

Object* Float::getCopy()
{
	return new Float(*this);
}

bool Float::operator==(Object& other)
{
	return ((*this <=> other) == 0);
}


bool Float::operator==(Float& other)
{
	return ((*this <=> other) == 0);
}

Float& Float::operator=(const float& value)
{
	setContainerValue(value);
	return *this;
}


std::partial_ordering Float::operator<=>(Float& other)
{
	return (getValue() <=> other.getValue());
}

std::partial_ordering Float::operator<=>(Object& other)
{

	if (typeIdentifier != other.identifier()) return std::partial_ordering::unordered;
	float otherValue = convertContainer(other.getValue());
	return (getValue() <=> otherValue);

}


float Float::convertContainer(void* value)
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

float Float::getValue()
{
	return convertContainer(Object::getValue());
}
