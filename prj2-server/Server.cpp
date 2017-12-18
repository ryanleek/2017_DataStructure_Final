#include "Server.h"

Server::Server()
{
	ReadFile();

	//WinSock ����
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock ���� ����", "����", MB_OK | MB_ICONERROR); // ����â ǥ��
		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //���� ������ ���� �ּ� ����
	addr.sin_port = htons(1111); // ������ Ȯ���� �� ��Ʈ
	addr.sin_family = AF_INET; // IPv4 ���� ���

	sListen = socket(AF_INET, SOCK_STREAM, NULL); // ���ο� ������ ���� ���� ����
	bind(sListen, (SOCKADDR*)&addr, addrlen); // �ּҸ� ���Ͽ� ���ε�
	listen(sListen, SOMAXCONN); // ������ ������ ��ٸ�

	ConnectionCounter = 0;
	serverptr = this;
}

bool Server::ListenForNewConnection()
{
	SOCKET newConnection; // Ŭ���̾�Ʈ���� ������ ������ ����
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); // ���ο� ������ ���

	if (newConnection == 0) // Ŭ���̾�Ʈ ���� ���� ��
	{
		cout << "Ŭ���̾�Ʈ ���� ���� ����." << endl;
		return false;
	}
	else // Ŭ���̾�Ʈ ���� ����
	{
		cout << "Ŭ���̾�Ʈ ���� ����!" << endl;
		connections[ConnectionCounter].socket = newConnection; // �迭�� ������ ����

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(ConnectionCounter), NULL, NULL); // ������ Thread ����, �ε����� i.
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
		string Message; // �޼����� ������ ���ڿ�
		if (!GetString(id, Message)) // Message�� ������ ����
			return false; // �޼����� ���� ������ ���

		for (int i = 0; i < ConnectionCounter; i++)
		{
			if (i == id)
				continue; // �޼����� ������ Ŭ���̾�Ʈ�� ��ŵ

			if (!SendMsg(i, Message))
				cout << "Ŭ���̾�Ʈ \"" << i << "\"���� \"" << id << "\"�� �޼��� ���� ����" << endl;
		}
		cout << "Ŭ���̾�Ʈ \"" << id << "\"�� �޼��� ó�� �Ϸ�" << endl;
		break;
	}
	case P_ID:
	{
		string ID;
		if (!GetString(id, ID)) // ID�� ������ ����
			return false; // ID�� ���� ������ ���

		loginedUser.SetId(ID);

		if (userList.Get(loginedUser))
		{
			if (!SendID(id, ID))
				cout << "Ŭ���̾�Ʈ \"" << id << "\"���� \"" << "���̵� ���� ���� ����" << endl;
		}
		else 
		{
			loginedUser.SetRecord("", "", "");
			ID = "false";
			if (!SendID(id, ID))
				cout << "Ŭ���̾�Ʈ \"" << id << "\"���� \"" << "���̵� ���� ���� ����" << endl;
		}
		cout << "Ŭ���̾�Ʈ \"" << id << "\"�� ���̵� Ȯ�� �Ϸ�" << endl;
		break;
	}
	case P_PW:
	{
		string PW;
		if (!GetString(id, PW)) // PW�� ������ ����
			return false; // PW�� ���� ������ ���

		if (loginedUser.GetPassword() == PW)
		{
			if (!SendPW(id, PW))
				cout << "Ŭ���̾�Ʈ \"" << id << "\"���� \"" << "�н����� ���� ���� ����" << endl;
		}
		else
		{
			loginedUser.SetRecord("", "", "");
			PW = "false";
			if (!SendPW(id, PW))
				cout << "Ŭ���̾�Ʈ \"" << id << "\"���� \"" << "�н����� ���� ���� ����" << endl;
		}
		cout << "Ŭ���̾�Ʈ \"" << id << "\"�� �н����� Ȯ�� �Ϸ�" << endl;
		break;
	}
	case P_NID:
	{
		string NID;
		if (!GetString(id, NID)) // NID�� ������ ����
			return false; // NID�� ���� ������ ���

		loginedUser.SetId(NID);
		break;
	}
	case P_NPW:
	{
		string NPW;
		if (!GetString(id, NPW)) // NPW�� ������ ����
			return false; // NPW�� ���� ������ ���

		loginedUser.SetPassword(NPW);
		break;
	}
	case P_NName:
	{
		string NName;
		if (!GetString(id, NName)) // NName�� ������ ����
			return false; // NName�� ���� ������ ���

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
			cout << " # Ŭ���̾�Ʈ \"" << id << "\"�� ��û�� ������ �����ϴ�." << endl;
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
		cout << "��Ȯ�� �� ��Ŷ: " << _packettype << endl;
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

		cout << " # " << connections[id].file.fileName << " ���� ���� �Ϸ�." << endl;
	}

	return true;
}

void Server::ClientHandlerThread(int id)
{
	Packet packettype;

	while (1)
	{
		if (!serverptr->GetPacket(id, packettype)) // ��Ŷ�� �����´�.
			break;

		if (!serverptr->ProcessPacket(id, packettype)) // ��Ŷ�� ���������� ó�� ���� ����
			break;
	}

	cout << "Ŭ���̾�Ʈ \"" << id << "\"�� ������ ������" << endl;
	closesocket(serverptr->connections[id].socket); // ��Ŷ ó�� ���� �� ������ �ݴ´�.
}

void Server::StartServer()
{
	for (int i = 0; i < 100; i++)
		ListenForNewConnection(); // ���ο� ���� ���
}