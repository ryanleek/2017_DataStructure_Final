#pragma once

#include "SortedLL.h"
#include "ChatRoom.h"

/**
*	유저의 정보를 가진 클래스.
*/
class User
{
public:

	/**
	*	기본 생성자.
	*/
	User()
	{
		m_Id = "";
		m_sPassword = "";
		m_sName = "";
	}

	/**
	*	소멸자.
	*/
	~User() {}

	/**
	*	@brief	유저의 아이디 반환.
	*	@pre	유저의 아이디가 설정되어 있음.
	*	@post	없음.
	*	@return	유저의 아이디.
	*/
	string GetId();

	/**
	*	@brief	유저의 패스워드 반환.
	*	@pre	유저의 패스워드가 설정되어 있음.
	*	@post	없음.
	*	@return	유저의 패스워드.
	*/
	string GetPassword();

	/**
	*	@brief	유저의 이름 반환.
	*	@pre	유저의 이름이 설정되어 있음.
	*	@post	없음.
	*	@return	유저의 이름.
	*/
	string GetName();

	/**
	*	@brief	유저의 아이디를 설정.
	*	@pre	없음.
	*	@post	유저의 아이디가 설정됨.
	*	@param	inId	유저의 아이디.
	*/
	void SetId(string inId);

	/**
	*	@brief	유저의 패스워드를 설정.
	*	@pre	없음.
	*	@post	유저의 패스워드가 설정됨.
	*	@param	inPassword	유저의 패스워드.
	*/
	void SetPassword(string inPassword);

	/**
	*	@brief	유저의 이름을 설정.
	*	@pre	없음.
	*	@post	유저의 이름이 설정됨.
	*	@param	inId	유저의 이름.
	*/
	void SetName(string inName);

	/**
	*	@brief	유저의 정보 설정.
	*	@pre	없음.
	*	@post	유저의 정보가 설정됨.
	*	@param	inId	유저의 아이디.
	*	@param	inPassword	유저의 패스워드.
	*	@param	inName	유저의 이름.
	*/
	void SetRecord(string inId, string inPassword, string inName);

	/**
	*	@brief	유저의 아이디를 화면에 출력.
	*	@pre	유저의 아이디가 설정되어있음.
	*	@post	유저의 아이디가 화면에 있음.
	*/
	void DisplayIdOnScreen();

	/**
	*	@brief	유저의 패스워드를 화면에 출력.
	*	@pre	유저의 패스워드가 설정되어있음.
	*	@post	유저의 패스워드가 화면에 있음.
	*/
	void DisplayPasswordOnScreen();

	/**
	*	@brief	유저의 이름을 화면에 출력.
	*	@pre	유저의 이름이 설정되어있음.
	*	@post	유저의 이름이 화면에 있음.
	*/
	void DisplayNameOnScreen();

	/**
	*	@brief	유저의 정보를 화면에 출력.
	*	@pre	유저의 정보가 설정되어있음.
	*	@post	유저의 정보가 화면에 있음.
	*/
	void DisplayRecordOnScreen();

	/**
	*	@brief	유저의 아이디를 키보드 입력값으로 설정.
	*	@pre	없음.
	*	@post	유저의 아이디가 설정됨.
	*/
	void SetIdFromKB();

	/**
	*	@brief	유저의 패스워드를 키보드 입력값으로 설정.
	*	@pre	없음.
	*	@post	유저의 패스워드가 설정됨.
	*/
	void SetPasswordFromKB();

	/**
	*	@brief	유저의 이름을 키보드 입력값으로 설정.
	*	@pre	없음.
	*	@post	유저의 이름이 설정됨.
	*/
	void SetNameFromKB();

	/**
	*	@brief	유저의 정보를 키보드 입력값으로 설정.
	*	@pre	없음.
	*	@post	유저의 정보가 설정됨.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	두 유저를 유저의 아이디로 비교.
	*	@pre	두 유저가 초기화 되었어야함.
	*	@param	item	비교 되는 대상 유저.
	*	@return	this.id < data.id라면 1 반환, 그 외엔 0 반환.
	*/
	bool operator<(User item);

	/**
	*	@brief	두 유저를 유저의 아이디로 비교.
	*	@pre	두 유저가 초기화 되었어야함.
	*	@param	item	비교 되는 대상 유저.
	*	@return	this.id == data.id라면 1 반환, 그 외엔 0 반환.
	*/
	bool operator==(User item);

protected:

	string m_Id;		///< 유저의 아이디.
	string m_sPassword;	///< 유저의 비밀번호.
	string m_sName;		///< 유저의 이름.
};