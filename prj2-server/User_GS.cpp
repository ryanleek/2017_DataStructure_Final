#include "User.h"

// 유저의 아이디 반환
string User::GetId()
{
	return m_Id;
}

// 유저의 패스워드 반환
string User::GetPassword()
{
	return m_sPassword;
}

// 유저의 이름 반환
string User::GetName()
{
	return m_sName;
}

// 유저의 아이디 설정
void User::SetId(string inId)
{
	m_Id = inId;
}

// 유저의 패스워드 설정
void User::SetPassword(string inPassword)
{
	m_sPassword = inPassword;
}

// 유저의 이름 설정
void User::SetName(string inName)
{
	m_sName = inName;
}

// 유저의 정보 설정
void User::SetRecord(string inId, string inPassword, string inName)
{
	SetId(inId);
	SetPassword(inPassword);
	SetName(inName);
}

// 유저의 아이디 출력
void User::DisplayIdOnScreen()
{
	cout << "\t아이디: " << this->m_Id << endl;
}

// 유저의 패스워드 출력
void User::DisplayPasswordOnScreen()
{
	cout << "\t패스워드: " << this->m_sPassword << endl;
}

// 유저의 이름 출력
void User::DisplayNameOnScreen()
{
	cout << "\t이름: " << this->m_sName << endl;
}

// 유저의 정보 출력
void User::DisplayRecordOnScreen()
{
	DisplayIdOnScreen();
	DisplayPasswordOnScreen();
	DisplayNameOnScreen();
}

// 유저의 아이디를 키보드 입력값으로 설정
void User::SetIdFromKB()
{
	string inId;

	cout << "\t아이디 입력: ";
	cin >> inId;

	m_Id = inId;
}

// 유저의 패스워드를 키보드 입력값으로 설정
void User::SetPasswordFromKB()
{
	string inPassword;

	cout << "\t패스워드 입력: ";
	cin >> inPassword;

	m_sPassword = inPassword;
}

// 유저의 이름을 키보드 입력값으로 설정
void User::SetNameFromKB()
{
	string inName;

	cout << "\t이름 입력: ";
	cin >> inName;

	m_sName = inName;
}

// 유저의 정보를 키보드 입력값으로 설정
void User::SetRecordFromKB()
{
	SetPasswordFromKB();
	SetNameFromKB();
}

// 두 유저를 유저의 아이디로 비교
bool User::operator<(User item)
{
	return (this->GetId() < item.GetId());
}

// 두 유저를 유저의 아이디로 비교
bool User::operator==(User item)
{
	return (this->GetId() == item.GetId());
}