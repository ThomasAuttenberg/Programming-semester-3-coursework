#pragma once
#include "Object.h"
class String :
    private Object
{
private:
    std::string* value;
public:
    String();
    String(const String& other);
    String(String&& other);
    String& operator=(const String& other);
    String& operator=(String&& other);
    String(std::string value);
    String& operator=(const std::string& other);

    void initialize() override;
    char* to_cstring() const override;
    void from_cstring(const char*) override;
    void writeBinary(std::ofstream&) const override;
    void readBinary(std::ifstream&) override;
    Object* getCopy() const override;
    std::string& ref();

    std::partial_ordering operator<=>(const Object& other) const override;
    bool operator==(Object& other) const override;

    void operator+=(const Object& other) override;
    Object& operator+(const Object& other) const override;

    operator std::string();

};

