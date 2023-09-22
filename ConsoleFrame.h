#pragma once
#include <functional>
class ConsoleFrame
{
private:
	const char* text = nullptr;
	std::function<void(void)> frameAction = nullptr;
	std::function<void(void)> printingFunction = nullptr;
public:
	ConsoleFrame(const char* text);
	ConsoleFrame(std::function<void(void)> printingFunction);
	ConsoleFrame(const char* text, std::function<void(void)> frameAction);
	virtual void show();
};

