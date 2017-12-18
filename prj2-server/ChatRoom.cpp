#include "ChatRoom.h"

void ChatRoom::AddChat(Message msg)
{
	msgList.Add(msg);
}

// 채팅방 아이디 반환
string ChatRoom::GetRoomID()
{
	return roomID;
}

// 채팅방 이름 반환
string ChatRoom::GetRoomName()
{
	return roomName;
}

// 채팅방 이름 설정
void ChatRoom::SetRoomName()
{
	string name;

	cout << "\t채팅방 이름 입력: " << endl;
	cin >> name;

	roomName = name;
}

// 채팅방 설정
void ChatRoom::SetChatRoom(string id, string name)
{
	roomID = id;
	roomName = name;
}

// 두 채팅방을 채팅방의 고유 변수로 비교
bool ChatRoom::operator<(ChatRoom item)
{
	return (this->GetRoomID() < item.GetRoomID());
}

// 두 채팅방을 채팅방의 고유 변수로 비교
bool ChatRoom::operator==(ChatRoom item)
{
	return (this->GetRoomID() == item.GetRoomID());
}