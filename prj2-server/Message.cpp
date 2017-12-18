#include "Message.h"

// 메세지 출력
void Message::PrintMessage()
{
	cout << userName << ": " << content << endl;
}

// 메세지를 보낸 사람 이름 반환
string Message::GetUserName()
{
	return userName;
}

// 메세지 내용 반환
string Message::GetContent()
{
	return content;
}

// 받은 정보에 따라 메세지 설정
void Message::SetMessage(string userName, string content)
{
	this->userName = userName;
	this->content = content;
}