#include "User.h"

// ������ ���̵� ��ȯ
string User::GetId()
{
	return m_Id;
}

// ������ �н����� ��ȯ
string User::GetPassword()
{
	return m_sPassword;
}

// ������ �̸� ��ȯ
string User::GetName()
{
	return m_sName;
}

// ������ ���̵� ����
void User::SetId(string inId)
{
	m_Id = inId;
}

// ������ �н����� ����
void User::SetPassword(string inPassword)
{
	m_sPassword = inPassword;
}

// ������ �̸� ����
void User::SetName(string inName)
{
	m_sName = inName;
}

// ������ ���� ����
void User::SetRecord(string inId, string inPassword, string inName)
{
	SetId(inId);
	SetPassword(inPassword);
	SetName(inName);
}

// ������ ���̵� ���
void User::DisplayIdOnScreen()
{
	cout << "\t���̵�: " << this->m_Id << endl;
}

// ������ �н����� ���
void User::DisplayPasswordOnScreen()
{
	cout << "\t�н�����: " << this->m_sPassword << endl;
}

// ������ �̸� ���
void User::DisplayNameOnScreen()
{
	cout << "\t�̸�: " << this->m_sName << endl;
}

// ������ ���� ���
void User::DisplayRecordOnScreen()
{
	DisplayIdOnScreen();
	DisplayPasswordOnScreen();
	DisplayNameOnScreen();
}

// ������ ���̵� Ű���� �Է°����� ����
void User::SetIdFromKB()
{
	string inId;

	cout << "\t���̵� �Է�: ";
	cin >> inId;

	m_Id = inId;
}

// ������ �н����带 Ű���� �Է°����� ����
void User::SetPasswordFromKB()
{
	string inPassword;

	cout << "\t�н����� �Է�: ";
	cin >> inPassword;

	m_sPassword = inPassword;
}

// ������ �̸��� Ű���� �Է°����� ����
void User::SetNameFromKB()
{
	string inName;

	cout << "\t�̸� �Է�: ";
	cin >> inName;

	m_sName = inName;
}

// ������ ������ Ű���� �Է°����� ����
void User::SetRecordFromKB()
{
	SetPasswordFromKB();
	SetNameFromKB();
}

// �� ������ ������ ���̵�� ��
bool User::operator<(User item)
{
	return (this->GetId() < item.GetId());
}

// �� ������ ������ ���̵�� ��
bool User::operator==(User item)
{
	return (this->GetId() == item.GetId());
}