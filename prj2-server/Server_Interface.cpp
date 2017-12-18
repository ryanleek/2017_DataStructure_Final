#include "Server.h"

void Server::mainInterface()
{
	cout << "---------------------------------------" << endl;
	cout << " 서버 프로그램" << endl;
	cout << "---------------------------------------" << endl;
	cout << " 1. 서버 구동" << endl;
	cout << " 2. 유저 관리" << endl;
	cout << " 0. 종료" << endl;
	cout << "---------------------------------------" << endl;
	cout << " -> ";
}

void Server::manageInterface()
{
	cout << "---------------------------------------" << endl;
	cout << " 유저 관리" << endl;
	cout << "---------------------------------------" << endl;
	cout << " 1. 정보 수정" << endl;
	cout << " 2. 유저 삭제" << endl;
	cout << " 0. 뒤로 가기" << endl;
	cout << "---------------------------------------" << endl;
	cout << " -> ";
}

void Server::searchInterface()
{
	cout << "---------------------------------------" << endl;
	cout << " 관리할 유저의 이름 또는 아이디 입력" << endl;
	cout << "---------------------------------------" << endl;
	cout << " -> ";
}
