#pragma once
#include "Object.h"


class Float : private Object
{
private:

	static const int STRING_REPRESENTATION_SYMBOLS_NUMBER = 20;

	float convertContainer(void* value) const;
	friend std::istream& operator>>(std::istream& is, Float& obj);

public:

	Float();
	Float(float value);
	Float(const Float& value);
	Float(Float&& value);
	Float& operator=(const Float& other);
	Float& operator=(Float&& other);
	float getValue() const;

	void initialize() override;
	char* to_cstring() const override;
	void from_cstring(const char*) override;
	void writeBinary(std::ofstream&) const override;
	void readBinary(std::ifstream&) override;
	Object* getCopy() const override;

	std::partial_ordering operator<=>(Object& other) const override;
	bool operator==(Object& other) const override;

	std::partial_ordering operator<=>(Float& other) const;
	bool operator==(Float& other) const;

	Float& operator=(const float& value);
};

std::ostream& operator<<(std::ostream& os, const Float& obj);
