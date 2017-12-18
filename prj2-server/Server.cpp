#include "Server.h"

Server::Server()
{
	ReadFile();

	//WinSock 시작
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock 시작 실패", "에러", MB_OK | MB_ICONERROR); // 에러창 표시
		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //로컬 송출을 위한 주소 설정
	addr.sin_port = htons(1111); // 서버가 확인을 할 포트
	addr.sin_family = AF_INET; // IPv4 소켓 사용

	sListen = socket(AF_INET, SOCK_STREAM, NULL); // 새로운 연결을 위한 소켓 생성
	bind(sListen, (SOCKADDR*)&addr, addrlen); // 주소를 소켓에 바인딩
	listen(sListen, SOMAXCONN); // 소켓이 수신을 기다림

	ConnectionCounter = 0;
	serverptr = this;
}

bool Server::ListenForNewConnection()
{
	SOCKET newConnection; // 클라이언트와의 연결을 유지할 소켓
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); // 새로운 연결을 허용

	if (newConnection == 0) // 클라이언트 연결 실패 시
	{
		cout << "클라이언트 연결 수락 실패." << endl;
		return false;
	}
	else // 클라이언트 연결 성공
	{
		cout << "클라이언트 연결 성공!" << endl;
		connections[ConnectionCounter].socket = newConnection; // 배열에 소켓을 설정

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(ConnectionCounter), NULL, NULL); // 서버의 Thread 생성, 인덱스는 i.
		ConnectionCounter++;

		return true;
	}
}

bool Server::ProcessPacket(int id, Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage:
	{
		string Message; // 메세지를 저장할 문자열
		if (!GetString(id, Message)) // Message를 변수에 저장
			return false; // 메세지를 받지 못했을 경우

		for (int i = 0; i < ConnectionCounter; i++)
		{
			if (i == id)
				continue; // 메세지를 전송한 클라이언트는 스킵

			if (!SendMsg(i, Message))
				cout << "클라이언트 \"" << i << "\"에게 \"" << id << "\"의 메세지 전송 실패" << endl;
		}
		cout << "클라이언트 \"" << id << "\"의 메세지 처리 완료" << endl;
		break;
	}
	case P_ID:
	{
		string ID;
		if (!GetString(id, ID)) // ID를 변수에 저장
			return false; // ID를 받지 못했을 경우

		loginedUser.SetId(ID);

		if (userList.Get(loginedUser))
		{
			if (!SendID(id, ID))
				cout << "클라이언트 \"" << id << "\"에게 \"" << "아이디 승인 전송 실패" << endl;
		}
		else 
		{
			loginedUser.SetRecord("", "", "");
			ID = "false";
			if (!SendID(id, ID))
				cout << "클라이언트 \"" << id << "\"에게 \"" << "아이디 실패 전송 실패" << endl;
		}
		cout << "클라이언트 \"" << id << "\"의 아이디 확인 완료" << endl;
		break;
	}
	case P_PW:
	{
		string PW;
		if (!GetString(id, PW)) // PW를 변수에 저장
			return false; // PW를 받지 못했을 경우

		if (loginedUser.GetPassword() == PW)
		{
			if (!SendPW(id, PW))
				cout << "클라이언트 \"" << id << "\"에게 \"" << "패스워드 승인 전송 실패" << endl;
		}
		else
		{
			loginedUser.SetRecord("", "", "");
			PW = "false";
			if (!SendPW(id, PW))
				cout << "클라이언트 \"" << id << "\"에게 \"" << "패스워드 실패 전송 실패" << endl;
		}
		cout << "클라이언트 \"" << id << "\"의 패스워드 확인 완료" << endl;
		break;
	}
	case P_NID:
	{
		string NID;
		if (!GetString(id, NID)) // NID를 변수에 저장
			return false; // NID를 받지 못했을 경우

		loginedUser.SetId(NID);
		break;
	}
	case P_NPW:
	{
		string NPW;
		if (!GetString(id, NPW)) // NPW를 변수에 저장
			return false; // NPW를 받지 못했을 경우

		loginedUser.SetPassword(NPW);
		break;
	}
	case P_NName:
	{
		string NName;
		if (!GetString(id, NName)) // NName를 변수에 저장
			return false; // NName를 받지 못했을 경우

		loginedUser.SetName(NName);
		userList.Add(loginedUser);
		loginedUser.SetRecord("", "", "");
		break;
	}
	case P_FTRFile:
	{
		string filename;
		if (!GetString(id, filename))
			return false;

		connections[id].file.ifs.open(filename, ios::binary | ios::ate);
		if (!connections[id].file.ifs.is_open())
		{
			cout << " # 클라이언트 \"" << id << "\"가 요청한 파일이 없습니다." << endl;
			return true;
		}

		connections[id].file.fileName = filename;
		connections[id].file.fileSize = connections[id].file.ifs.tellg();
		connections[id].file.ifs.seekg(0);
		connections[id].file.fileOffset = 0;

		if (!HandleSendFile(id))
			return false;

		break;
	}
	case P_FTRNBuffer:
	{
		if (!HandleSendFile(id))
			return false;
		break;
	}
	case P_Friend:
	{
		break;
	}
	case P_CurChat:
	{
		string roomID;
		if (!GetString(id, roomID))
			return false;

		connections[id].curChat = roomID;
		break;
	}
	case P_ChatRoom:
	{
		string roomName;
		ChatRoom chat;
		if (!GetString(id, roomName))
			return false;

		chat.SetChatRoom(connections[id].curChat, roomName);
		chatList.Add(chat);
		break;
	}
	default:
		cout << "미확인 된 패킷: " << _packettype << endl;
		break;
	}
	return true;
}

bool Server::HandleSendFile(int id)
{
	if (connections[id].file.fileOffset >= connections[id].file.fileSize)
		return true;

	if (!SendPacket(id, P_FTBBuffer))
		return false;

	connections[id].file.rBytes = connections[id].file.fileSize - connections->file.fileOffset;

	if (connections[id].file.rBytes > connections[id].file.buffersize)
	{
		connections[id].file.ifs.read(connections[id].file.buffer, connections[id].file.buffersize);
		
		if (!SendInt(id, connections[id].file.buffersize))
			return false;

		if (!sendall(id, connections[id].file.buffer, connections[id].file.buffersize))
			return false;

		connections[id].file.fileOffset += connections[id].file.buffersize;
	}
	else
	{
		connections[id].file.ifs.read(connections[id].file.buffer, connections[id].file.rBytes);

		if (!SendInt(id, connections[id].file.rBytes))
			return false;

		if (!sendall(id, connections[id].file.buffer, connections[id].file.rBytes))
			return false;

		connections[id].file.fileOffset += connections[id].file.rBytes;
	}

	if (connections[id].file.fileOffset == connections[id].file.fileSize)
	{
		if (!SendPacket(id, P_FTeof))
			return false;

		connections[id].file.ifs.close();

		cout << " # " << connections[id].file.fileName << " 파일 전송 완료." << endl;
	}

	return true;
}

void Server::ClientHandlerThread(int id)
{
	Packet packettype;

	while (1)
	{
		if (!serverptr->GetPacket(id, packettype)) // 패킷을 가져온다.
			break;

		if (!serverptr->ProcessPacket(id, packettype)) // 패킷이 정상적으로 처리 되지 않음
			break;
	}

	cout << "클라이언트 \"" << id << "\"의 연결이 끊어짐" << endl;
	closesocket(serverptr->connections[id].socket); // 패킷 처리 실패 시 소켓을 닫는다.
}

void Server::StartServer()
{
	for (int i = 0; i < 100; i++)
		ListenForNewConnection(); // 새로운 연결 허용
}