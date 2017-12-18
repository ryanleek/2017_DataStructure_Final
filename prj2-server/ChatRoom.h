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
	*	@brief	두 멤버를 멤버의 아이디로 비교.
	*	@pre	두 멤버가 초기화 되었어야함.
	*	@param	item	비교 되는 대상 멤버.
	*	@return	this.id < data.id라면 1 반환, 그 외엔 0 반환.
	*/
	bool operator<(ChatRoom item);

	/**
	*	@brief	두 멤버를 멤버의 아이디로 비교.
	*	@pre	두 멤버가 초기화 되었어야함.
	*	@param	item	비교 되는 대상 멤버.
	*	@return	this.id == data.id라면 1 반환, 그 외엔 0 반환.
	*/
	bool operator==(ChatRoom item);

private:
	string roomID;		///< 채팅방 아이디
	string roomName;	///< 채팅방 이름
	UnsortedLL<Message> msgList; ///< 메세지 리스트
};