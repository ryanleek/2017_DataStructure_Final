#include "Server.h"

bool Server::recvall(int index, char* data, int totalbytes)
{
	int bytesrecieved = 0;

	while (bytesrecieved < totalbytes)
	{
		int RetnCheck = recv(connections[index].socket, data, totalbytes - bytesrecieved, NULL);
		
		if (RetnCheck == SOCKET_ERROR)
			return false;

		bytesrecieved += RetnCheck;
	}
	return true;
}

bool Server::sendall(int index, char* data, int totalbytes)
{
	int bytessent = 0; 

	while (bytessent < totalbytes)
	{
		int RetnCheck = send(connections[index].socket, data + bytessent, totalbytes - bytessent, NULL);

		if (RetnCheck == SOCKET_ERROR)
			return false;

		bytessent += RetnCheck;
	}
	return true;
}

// ������ �����ϸ� �����ߴ��� Ȯ��
bool Server::SendInt(int index, int _int)
{
	int RetnCheck = send(connections[index].socket, (char*)&_int, sizeof(int), NULL);

	if (RetnCheck == SOCKET_ERROR) // ���ۿ� ����
		return false;

	return true;
}

// ��Ŷ�� �����ϸ� �����ߴ��� Ȯ��
bool Server::SendPacket(int index, Packet _packettype)
{
	int RetnCheck = send(connections[index].socket, (char*)&_packettype, sizeof(Packet), NULL);

	if (RetnCheck == SOCKET_ERROR) // ���ۿ� ����
		return false;

	return true;
}

// �޽����� �۽��ϸ� �����ߴ��� Ȯ��
bool Server::SendMsg(int index, string &_string)
{
	if (!SendPacket(index, P_ChatMessage)) // ��Ŷ ���ۿ� ����
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // ���� ���� ���ۿ� ����
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string ���� ���ۿ� ����
		return false;

	return true;
}

// ���̵� �۽��ϸ� �����ߴ��� Ȯ��
bool Server::SendID(int index, string &_string)
{
	if (!SendPacket(index, P_ID)) // ��Ŷ ���ۿ� ����
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // ���� ���� ���ۿ� ����
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string ���� ���ۿ� ����
		return false;

	return true;
}

// �н����带 �۽��ϸ� �����ߴ��� Ȯ��
bool Server::SendPW(int index, string &_string)
{
	if (!SendPacket(index, P_PW)) // ��Ŷ ���ۿ� ����
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // ���� ���� ���ۿ� ����
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string ���� ���ۿ� ����
		return false;

	return true;
}

// ģ�� ���̵� �۽��ϸ� �����ߴ��� Ȯ��
bool Server::SendFriend(int index, string &_string)
{
	if (!SendPacket(index, P_Friend)) // ��Ŷ ���ۿ� ����
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // ���� ���� ���ۿ� ����
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string ���� ���ۿ� ����
		return false;

	return true;
}

// �� ���̵� �۽��ϸ� �����ߴ��� Ȯ��
bool Server::SendRoomID(int index, string &_string)
{
	if (!SendPacket(index, P_ChatRoom)) // ��Ŷ ���ۿ� ����
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // ���� ���� ���ۿ� ����
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string ���� ���ۿ� ����
		return false;

	return true;
}

// ������ �����ϸ� �����ߴ��� Ȯ��
bool Server::GetInt(int index, int &_int)
{
	int RetnCheck = recv(connections[index].socket, (char*)&_int, sizeof(int), NULL);

	if (RetnCheck == SOCKET_ERROR) // ���ſ� ����
		return false;

	return true;
}

// ��Ŷ�� �����ϸ� �����ߴ��� Ȯ��
bool Server::GetPacket(int index, Packet &_packettype)
{
	int RetnCheck = recv(connections[index].socket, (char*)&_packettype, sizeof(Packet), NULL);

	if (RetnCheck == SOCKET_ERROR) // ���ۿ� ����
		return false;

	return true;
}

// �޼�����  �����ϸ� �����ߴ��� Ȯ��
bool Server::GetString(int index, string &_string)
{
	int bufferlength; // ������ ���̸� ���� 

	if (!GetInt(index, bufferlength)) // ������ ���̸� �������� ������ �����Ѵ�
		return false;

	char* buffer = new char[bufferlength + 1]; // ������ �޸� �Ҵ�
	buffer[bufferlength] = '\0';

	int RetnCheck = recv(connections[index].socket, buffer, bufferlength, NULL); // �޼��� ����
	_string = buffer; // string�� ���� �޼����� ����
	delete[] buffer; // memory leak�� ���� ���� ������ �޸� ����

	if (RetnCheck == SOCKET_ERROR) // ���� ���� ���� �߻�
		return false;

	return true;
}
