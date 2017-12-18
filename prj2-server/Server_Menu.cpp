#include "Server.h"

void Server::run()
{
	int choice;

	while (1)
	{
		mainInterface();
		cin >> choice;
		switch (choice)
		{
		case 1:
			StartServer();
			break;
		case 2:
			searchUser();
			break;
		case 0:
			return;
		default:
			break;
		}
	}
}

void Server::manageUser(User _user)
{
	int choice;

	while (1)
	{
		manageInterface();
		cin >> choice;

		switch (choice)
		{
		case 1:
			updateUser(_user);
			break;
		case 2:
			deleteUser(_user);
			return;
		case 0:
			return;
		default:
			cout << "\n\t※알림: 올바르지 않은 선택 입니다.\n\n";
			break;
		}
	}
}