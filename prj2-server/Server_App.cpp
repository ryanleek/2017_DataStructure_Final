#include "Server.h"

void Server::ReadFile()
{
	ReadUserFile();
	ReadChatFile();
}

void Server::ReadUserFile()
{
	string id, pw, name;

	ifstream ifs;
	ifs.open("user.txt");

	while (!ifs.eof())
	{
		ifs >> id >> pw >> name;

		User* temp = new User;
		temp->SetRecord(id, pw, name);

		userList.Add(*temp);
	}
	ifs.close();
}

void Server::ReadChatFile()
{
	int msgc;
	string id, name, u_name, content;

	ifstream textFile;
	textFile.open("chatroom.txt");

	while (!textFile.eof())
	{
		textFile >> id >> name >> msgc;

		ChatRoom temp;
		temp.SetChatRoom(id, name);

		for (int i = 0; i < msgc; i++)
		{
			textFile >> u_name >> content;

			Message msg;
			msg.SetMessage(u_name, content);
			temp.AddChat(msg);
		}
		chatList.Add(temp);
	}
	textFile.close();
}

void Server::WriteFile()
{

}

void Server::searchUser()
{
	int found;
	string strData;
	User toSearch;

	searchInterface();
	cin >> strData;

	toSearch.SetId(strData);
	toSearch.SetName(strData);

	found = userList.Get(toSearch);

	if (found == 0)
		found = searchByName(toSearch);

	if (found == 0)
	{
		cout << "---------------------------------------" << endl;
		cout << " # 입력한 정보를 가진 유저를 찾을 수 없습니다." << endl;
		return;
	}
	
	manageUser(toSearch);
}

int Server::searchByName(User &_user)
{
	int length = userList.GetLength();
	if (length == 0)
		return 0;
	User temp;
	SortedLL<User> fList;
	userList.ResetList();
	int count = 0, fCount = 0;
	userList.GetNextItem(temp);
	cout << endl << endl;
	while (count < length)
	{
		if (temp.GetName().find(_user.GetName()) != -1)
		{
			fCount++;
			cout << fCount << ". ";
			temp.DisplayRecordOnScreen();
			fList.Add(temp);
			cout << endl;
		}
		count++;
		fList.GetNextItem(temp);
	}
	if (fCount == 0)
		return 0;
	int index;

	cout << "---------------------------------------" << endl;
	cout << " # 찾고자 하는 유저의 인덱스를 입력하세요.\n\n";
	cout << "---------------------------------------" << endl;
	cout << " -> ";
	cin >> index;
	count = 0;
	fList.ResetList();
	fList.GetNextItem(temp);
	while (count < index)
	{
		count++;
		if (count == index)
			_user = temp;
		fList.GetNextItem(temp);
	}
	return 1;
}

void Server::updateUser(User _user)
{
	_user.SetRecordFromKB();
	userList.Replace(_user);
	cout << "---------------------------------------" << endl;
	cout << " # 유저의 정보가 다음과 같이 수정되었습니다." << endl;
	cout << "---------------------------------------" << endl;
	_user.DisplayRecordOnScreen();
}

void Server::deleteUser(User _user)
{
	userList.Delete(_user);
	cout << "---------------------------------------" << endl;
	cout << " # 유저의 정보가 서버에서 삭제되었습니다." << endl;
}