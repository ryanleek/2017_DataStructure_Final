#pragma once

#include "SortedLL.h"
#include "ChatRoom.h"

/**
*	������ ������ ���� Ŭ����.
*/
class User
{
public:

	/**
	*	�⺻ ������.
	*/
	User()
	{
		m_Id = "";
		m_sPassword = "";
		m_sName = "";
	}

	/**
	*	�Ҹ���.
	*/
	~User() {}

	/**
	*	@brief	������ ���̵� ��ȯ.
	*	@pre	������ ���̵� �����Ǿ� ����.
	*	@post	����.
	*	@return	������ ���̵�.
	*/
	string GetId();

	/**
	*	@brief	������ �н����� ��ȯ.
	*	@pre	������ �н����尡 �����Ǿ� ����.
	*	@post	����.
	*	@return	������ �н�����.
	*/
	string GetPassword();

	/**
	*	@brief	������ �̸� ��ȯ.
	*	@pre	������ �̸��� �����Ǿ� ����.
	*	@post	����.
	*	@return	������ �̸�.
	*/
	string GetName();

	/**
	*	@brief	������ ���̵� ����.
	*	@pre	����.
	*	@post	������ ���̵� ������.
	*	@param	inId	������ ���̵�.
	*/
	void SetId(string inId);

	/**
	*	@brief	������ �н����带 ����.
	*	@pre	����.
	*	@post	������ �н����尡 ������.
	*	@param	inPassword	������ �н�����.
	*/
	void SetPassword(string inPassword);

	/**
	*	@brief	������ �̸��� ����.
	*	@pre	����.
	*	@post	������ �̸��� ������.
	*	@param	inId	������ �̸�.
	*/
	void SetName(string inName);

	/**
	*	@brief	������ ���� ����.
	*	@pre	����.
	*	@post	������ ������ ������.
	*	@param	inId	������ ���̵�.
	*	@param	inPassword	������ �н�����.
	*	@param	inName	������ �̸�.
	*/
	void SetRecord(string inId, string inPassword, string inName);

	/**
	*	@brief	������ ���̵� ȭ�鿡 ���.
	*	@pre	������ ���̵� �����Ǿ�����.
	*	@post	������ ���̵� ȭ�鿡 ����.
	*/
	void DisplayIdOnScreen();

	/**
	*	@brief	������ �н����带 ȭ�鿡 ���.
	*	@pre	������ �н����尡 �����Ǿ�����.
	*	@post	������ �н����尡 ȭ�鿡 ����.
	*/
	void DisplayPasswordOnScreen();

	/**
	*	@brief	������ �̸��� ȭ�鿡 ���.
	*	@pre	������ �̸��� �����Ǿ�����.
	*	@post	������ �̸��� ȭ�鿡 ����.
	*/
	void DisplayNameOnScreen();

	/**
	*	@brief	������ ������ ȭ�鿡 ���.
	*	@pre	������ ������ �����Ǿ�����.
	*	@post	������ ������ ȭ�鿡 ����.
	*/
	void DisplayRecordOnScreen();

	/**
	*	@brief	������ ���̵� Ű���� �Է°����� ����.
	*	@pre	����.
	*	@post	������ ���̵� ������.
	*/
	void SetIdFromKB();

	/**
	*	@brief	������ �н����带 Ű���� �Է°����� ����.
	*	@pre	����.
	*	@post	������ �н����尡 ������.
	*/
	void SetPasswordFromKB();

	/**
	*	@brief	������ �̸��� Ű���� �Է°����� ����.
	*	@pre	����.
	*	@post	������ �̸��� ������.
	*/
	void SetNameFromKB();

	/**
	*	@brief	������ ������ Ű���� �Է°����� ����.
	*	@pre	����.
	*	@post	������ ������ ������.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	�� ������ ������ ���̵�� ��.
	*	@pre	�� ������ �ʱ�ȭ �Ǿ������.
	*	@param	item	�� �Ǵ� ��� ����.
	*	@return	this.id < data.id��� 1 ��ȯ, �� �ܿ� 0 ��ȯ.
	*/
	bool operator<(User item);

	/**
	*	@brief	�� ������ ������ ���̵�� ��.
	*	@pre	�� ������ �ʱ�ȭ �Ǿ������.
	*	@param	item	�� �Ǵ� ��� ����.
	*	@return	this.id == data.id��� 1 ��ȯ, �� �ܿ� 0 ��ȯ.
	*/
	bool operator==(User item);

protected:

	string m_Id;		///< ������ ���̵�.
	string m_sPassword;	///< ������ ��й�ȣ.
	string m_sName;		///< ������ �̸�.
};