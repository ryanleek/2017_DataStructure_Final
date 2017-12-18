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

// 정수를 전송하며 성공했는지 확인
bool Server::SendInt(int index, int _int)
{
	int RetnCheck = send(connections[index].socket, (char*)&_int, sizeof(int), NULL);

	if (RetnCheck == SOCKET_ERROR) // 전송에 실패
		return false;

	return true;
}

// 패킷을 전송하며 성공했는지 확인
bool Server::SendPacket(int index, Packet _packettype)
{
	int RetnCheck = send(connections[index].socket, (char*)&_packettype, sizeof(Packet), NULL);

	if (RetnCheck == SOCKET_ERROR) // 전송에 실패
		return false;

	return true;
}

// 메시지를 송신하며 성공했는지 확인
bool Server::SendMsg(int index, string &_string)
{
	if (!SendPacket(index, P_ChatMessage)) // 패킷 전송에 실패
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // 버퍼 길이 전송에 실패
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string 버퍼 전송에 실패
		return false;

	return true;
}

// 아이디를 송신하며 성공했는지 확인
bool Server::SendID(int index, string &_string)
{
	if (!SendPacket(index, P_ID)) // 패킷 전송에 실패
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // 버퍼 길이 전송에 실패
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string 버퍼 전송에 실패
		return false;

	return true;
}

// 패스워드를 송신하며 성공했는지 확인
bool Server::SendPW(int index, string &_string)
{
	if (!SendPacket(index, P_PW)) // 패킷 전송에 실패
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // 버퍼 길이 전송에 실패
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string 버퍼 전송에 실패
		return false;

	return true;
}

// 친구 아이디를 송신하며 성공했는지 확인
bool Server::SendFriend(int index, string &_string)
{
	if (!SendPacket(index, P_Friend)) // 패킷 전송에 실패
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // 버퍼 길이 전송에 실패
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string 버퍼 전송에 실패
		return false;

	return true;
}

// 방 아이디를 송신하며 성공했는지 확인
bool Server::SendRoomID(int index, string &_string)
{
	if (!SendPacket(index, P_ChatRoom)) // 패킷 전송에 실패
		return false;

	int bufferlength = _string.size();
	if (!SendInt(index, bufferlength)) // 버퍼 길이 전송에 실패
		return false;

	int RetnCheck = send(connections[index].socket, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR) // string 버퍼 전송에 실패
		return false;

	return true;
}

// 정수를 수신하며 성공했는지 확인
bool Server::GetInt(int index, int &_int)
{
	int RetnCheck = recv(connections[index].socket, (char*)&_int, sizeof(int), NULL);

	if (RetnCheck == SOCKET_ERROR) // 수신에 실패
		return false;

	return true;
}

// 패킷을 수신하며 성공했는지 확인
bool Server::GetPacket(int index, Packet &_packettype)
{
	int RetnCheck = recv(connections[index].socket, (char*)&_packettype, sizeof(Packet), NULL);

	if (RetnCheck == SOCKET_ERROR) // 전송에 실패
		return false;

	return true;
}

// 메세지를  수신하며 성공했는지 확인
bool Server::GetString(int index, string &_string)
{
	int bufferlength; // 버퍼의 길이를 저장 

	if (!GetInt(index, bufferlength)) // 버퍼의 길이를 가져오고 변수에 저장한다
		return false;

	char* buffer = new char[bufferlength + 1]; // 버퍼의 메모리 할당
	buffer[bufferlength] = '\0';

	int RetnCheck = recv(connections[index].socket, buffer, bufferlength, NULL); // 메세지 수신
	_string = buffer; // string을 받은 메세지로 설정
	delete[] buffer; // memory leak을 막기 위해 버퍼의 메모리 해제

	if (RetnCheck == SOCKET_ERROR) // 소켓 연결 에러 발생
		return false;

	return true;
}
