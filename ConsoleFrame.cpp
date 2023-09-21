#include "ConsoleFrame.h"

ConsoleFrame::ConsoleFrame(const char* text)
{
	this->text = text;
}

ConsoleFrame::ConsoleFrame(std::function<void(void)> printingFunction)
{
	this->printingFunction = printingFunction;
}

ConsoleFrame::ConsoleFrame(const char* text, std::function<void(void)> frameAction)
{
	this->text = text;
	this->frameAction = frameAction;
}

void ConsoleFrame::show()
{
	system("cls");
	
	if(text != nullptr)
		printf(text);

	if (printingFunction != nullptr)
		printingFunction();
	
	if (frameAction != nullptr)
		frameAction();
}
