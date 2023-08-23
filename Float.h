#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Object.h"
#include <iostream>

class Float : private Object
{
private:

	float convertContainer(void* value);

public:

	Float();
	Float(float value);
	Float(const Float& value);
	Float(Float&& value);
	Float& operator=(const Float& other);
	Float& operator=(Float&& other);
	float getValue();

	void initialize() override;
	void serialize(char*) override;
	void deserialize(const char*) override;
	void writeBinary(std::ofstream) override;
	void readBinary(std::ifstream) override;
	Object* getCopy() override;

	std::partial_ordering operator<=>(Object& other) override;
	bool operator==(Object& other) override;

	std::partial_ordering operator<=>(Float& other);
	bool operator==(Float& other);

	Float& operator=(const float& value);
};
