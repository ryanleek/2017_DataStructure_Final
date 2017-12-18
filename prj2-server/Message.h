#pragma once

#include <iostream>
#include <string>
using namespace std;

class Message
{
public:
	Message()
	{
		userName = "";
		content = "";
	}
	~Message() {}

	void PrintMessage();

	string GetUserName();
	string GetContent();

	void SetMessage(string userName, string content);

private:
	string userName;
	string content;
};