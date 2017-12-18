#pragma once

#include "Message.h"
#include "UnsortedLL.h"

class ChatRoom
{
public:

	ChatRoom()
	{
		roomID = "";
		roomName = "";
	}
	~ChatRoom() {}

	void AddChat(Message msg);

	string GetRoomID();
	string GetRoomName();

	void SetRoomName();
	void SetChatRoom(string id, string name);

	/**
	*	@brief	�� ����� ����� ���̵�� ��.
	*	@pre	�� ����� �ʱ�ȭ �Ǿ������.
	*	@param	item	�� �Ǵ� ��� ���.
	*	@return	this.id < data.id��� 1 ��ȯ, �� �ܿ� 0 ��ȯ.
	*/
	bool operator<(ChatRoom item);

	/**
	*	@brief	�� ����� ����� ���̵�� ��.
	*	@pre	�� ����� �ʱ�ȭ �Ǿ������.
	*	@param	item	�� �Ǵ� ��� ���.
	*	@return	this.id == data.id��� 1 ��ȯ, �� �ܿ� 0 ��ȯ.
	*/
	bool operator==(ChatRoom item);

private:
	string roomID;		///< ä�ù� ���̵�
	string roomName;	///< ä�ù� �̸�
	UnsortedLL<Message> msgList; ///< �޼��� ����Ʈ
};