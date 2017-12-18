#pragma once
#define _WINSOCK_DEPRECATED_NOWARNINGS

// 서버 프로그램
#pragma comment(lib, "ws2_32.lib")
#include "User.h"
#include "FTData.h"
#include <WinSock2.h>
#include <string>
#include <iostream>

// 다양한 종류의 패킷을 구분
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

	Connection connections[100];	///< 100개의 클라이언트 연결 허용
	SOCKET sListen;				///< 새로운 연결을 위한 소켓
	SOCKADDR_IN addr;			///< 수신 소켓에 바인딩 시킬 주소
	
	int ConnectionCounter;		///< 연결 횟수 카운터
	int addrlen = sizeof(addr); ///< 승인을 위한 주소의 크기

	User loginedUser;

	SortedLL<User> userList;	///< 
	SortedLL<User> friendList;
	SortedLL<ChatRoom> chatList;///<
};

static Server* serverptr;