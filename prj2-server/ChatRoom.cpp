#include "ChatRoom.h"

void ChatRoom::AddChat(Message msg)
{
	msgList.Add(msg);
}

// ä�ù� ���̵� ��ȯ
string ChatRoom::GetRoomID()
{
	return roomID;
}

// ä�ù� �̸� ��ȯ
string ChatRoom::GetRoomName()
{
	return roomName;
}

// ä�ù� �̸� ����
void ChatRoom::SetRoomName()
{
	string name;

	cout << "\tä�ù� �̸� �Է�: " << endl;
	cin >> name;

	roomName = name;
}

// ä�ù� ����
void ChatRoom::SetChatRoom(string id, string name)
{
	roomID = id;
	roomName = name;
}

// �� ä�ù��� ä�ù��� ���� ������ ��
bool ChatRoom::operator<(ChatRoom item)
{
	return (this->GetRoomID() < item.GetRoomID());
}

// �� ä�ù��� ä�ù��� ���� ������ ��
bool ChatRoom::operator==(ChatRoom item)
{
	return (this->GetRoomID() == item.GetRoomID());
}