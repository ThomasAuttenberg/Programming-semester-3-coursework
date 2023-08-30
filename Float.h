#pragma once
#include "Object.h"


class Float : private Object
{
private:

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

	std::partial_ordering operator<=>(const Object& other) const override;
	bool operator==(Object& other) const override;

	std::partial_ordering operator<=>(const Float& other) const;
	bool operator==(Float& other) const;

	void operator+=(const Object& other) override;
	void operator+=(const Float& other);
	Float& operator=(const float& value);
	Float operator+(const Float& other) const;
	Object& operator+(const Object& other) const override;
	Float operator-(const Float& other) const;
	Float operator*(const Float& other) const;
	Float operator/(const Float& other) const;
	Float operator+() const;
	Float operator-() const;

	explicit operator Object&();
};

std::ostream& operator<<(std::ostream& os, const Float& obj);
