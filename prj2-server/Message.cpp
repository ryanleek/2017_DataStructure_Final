#include "Message.h"

// �޼��� ���
void Message::PrintMessage()
{
	cout << userName << ": " << content << endl;
}

// �޼����� ���� ��� �̸� ��ȯ
string Message::GetUserName()
{
	return userName;
}

// �޼��� ���� ��ȯ
string Message::GetContent()
{
	return content;
}

// ���� ������ ���� �޼��� ����
void Message::SetMessage(string userName, string content)
{
	this->userName = userName;
	this->content = content;
}