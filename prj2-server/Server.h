#pragma once
#define _WINSOCK_DEPRECATED_NOWARNINGS

// ���� ���α׷�
#pragma comment(lib, "ws2_32.lib")
#include "User.h"
#include "FTData.h"
#include <WinSock2.h>
#include <string>
#include <iostream>

// �پ��� ������ ��Ŷ�� ����
enum Packet
{
	P_ChatMessage, P_ID, P_PW,
	P_Friend, P_ChatRoom, P_NID,
	P_NPW, P_NName, P_CurChat, P_FTRFile,
	P_FTeof, P_FTBBuffer, P_FTRNBuffer
};

struct Connection
{
	SOCKET socket;
	FTData file;
	string curChat = "";
};

class Server
{
public:
	Server();
	bool ListenForNewConnection();
	void run();

private:
	bool ProcessPacket(int id, Packet _packettype);
	static void ClientHandlerThread(int id);
	bool HandleSendFile(int id);

	bool recvall(int ID, char* data, int totalbytes);
	bool sendall(int ID, char* data, int totalbytes);

	bool SendInt(int index, int _int);
	bool SendPacket(int index, Packet _packettype);
	bool SendMsg(int index, string &_string);
	bool SendID(int index, string &_string);
	bool SendPW(int index, string &_string);
	bool SendFriend(int index, string &_string);
	bool SendRoomID(int index, string &_string);

	bool GetInt(int index, int &_int);
	bool GetPacket(int index, Packet &_packettype);
	bool GetString(int index, string &_string);

	void ReadFile();
	void ReadUserFile();
	void ReadChatFile();
	void WriteFile();

	void StartServer();
	void searchUser();
	int searchByName(User &_user);
	void manageUser(User _user);

	void updateUser(User _user);
	void deleteUser(User _user);

	void mainInterface();
	void manageInterface();
	void searchInterface();

	Connection connections[100];	///< 100���� Ŭ���̾�Ʈ ���� ���
	SOCKET sListen;				///< ���ο� ������ ���� ����
	SOCKADDR_IN addr;			///< ���� ���Ͽ� ���ε� ��ų �ּ�
	
	int ConnectionCounter;		///< ���� Ƚ�� ī����
	int addrlen = sizeof(addr); ///< ������ ���� �ּ��� ũ��

	User loginedUser;

	SortedLL<User> userList;	///< 
	SortedLL<User> friendList;
	SortedLL<ChatRoom> chatList;///<
};

static Server* serverptr;