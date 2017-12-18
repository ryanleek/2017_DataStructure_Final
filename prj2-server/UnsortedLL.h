#pragma once
#include "Node.h"
#include <iostream>

#ifndef _UNSORTED_LINKED_LIST_H
#define _UNSORTED_LINKED_LIST_H

/**
*	아이템 관리를 위한 비정렬 링크드 리스트
*/
template <typename T>
class UnsortedLL
{
public:

	/**
	*	기본 생성자
	*/
	UnsortedLL();

	/**
	*	소멸자
	*/
	~UnsortedLL();

	/**
	*	@brief	리스트를 빈 상태로 초기화 시킨다.
	*	@pre	없음.
	*	@post	리스트가 비었음.
	*/
	void MakeEmpty();

	/**
	*	@brief	리스트에 존재하는 노드의 수를 가져온다.
	*	@pre	없음.
	*	@post	함수 값 = 리스트에 있는 노드의 수.
	*	@return	리스트에 있는 노드의 수.
	*/
	int GetLength() const;

	/**
	*	@brief	리스트의 마지막 위치에 item을 추가.
	*	@pre	리스트가 가득 차지 않아야함, 리스트에 item이 아직 추가 되지 않음.
	*	@post	item이 리스트에 추가됨.
	*/
	void Add(T item);

	/**
	*	@brief	item의 키와 일치하는 키를 가지는 리스트의 데이터를 삭제(있다면).
	*	@pre	리스트가 비어있지 않아야함, 리스트에 아이템이 아직 삭제 되지 않음.
	*	@post	데이터가 리스트에서 삭제 되고, item에 복사됨.
	*/
	void Delete(T& item);

	/**
	*	@brief	리스트에 있는 item의 데이터를 바꾼다.
	*	@pre	리스트가 비어있지 않고, 바꾸고자 하는 아이템이 리스트에 있음.
	*	@post	item의 데이터가 변경됨.
	*	@return	함수가 제대로 작동하면 1 반환 그 외에는 0 반환.
	*/
	int Replace(T item);

	/**
	*	@brief	item의 키와 일치하는 키를 가지는 리스트의 데이터를 반환(있다면).
	*	@pre	item의 키 멤버가 설정 되어있어야함.
	*	@post	item의 키와 일치하는 리스트의 데이터를 item에 복사.
	*	@return	성공적으로 데이터를 찾았다면 1 반환, 그 외에는 0 반환.
	*/
	int Get(T& item);

	/**
	*	@brief	리스트의 이터레이터 curPtr을 초기화.
	*	@pre	없음.
	*	@post	curPtr이 초기화 됨.
	*/
	void ResetList();

	/**
	*	@brief	리스트 상 다음 위치에 있는 노드에 접근.
	*	@pre	curPtr이 정의되어 있고, curPtr이 리스트의 마지막 노드를 가리키고 있지 않음.
	*	@post	curPtr이 다음 노드를 가리키고 있고, item은 그 노드를 복사함.
	*/
	void GetNextItem(T& item);

private:

	NodeType<T>* m_List;	///< 리스트의 첫 노드를 가리키는 포인터
	NodeType<T>* m_curPtr;	///< 리스트에서 현재 접근하고 있는 노드
	int length;				///< 리스트에 있는 노드의 수
};

// 기본 생성자
template <typename T>
UnsortedLL<T>::UnsortedLL()
{
	length = 0;
	m_List = NULL;
	m_curPtr = NULL;
}


// 소멸자
template <typename T>
UnsortedLL<T>::~UnsortedLL()
{
	//리스트내의 모든 node 제거
	MakeEmpty();
}


// 리스트를 빈 상태로 초기화
template <typename T>
void UnsortedLL<T>::MakeEmpty()
{
	// 리스트내의 모든 노드 제거 하고 리스트의 length를 초기화
	NodeType<T>* tempPtr;

	while (m_List != NULL)
	{
		tempPtr = m_List;
		m_List = m_List->next;
		delete tempPtr;
	}

	length = 0;
}


// 리스트에 있는 노드의 수 반환
template <typename T>
int UnsortedLL<T>::GetLength() const
{
	return length;
}


// 리스트에 데이터 추가
template <typename T>
void UnsortedLL<T>::Add(T item)
{
	// 리스트 초기화
	ResetList();

	// 리스트에 추가할 새로운 node 객체와 이전 노드를 가리킬 포인터 선언
	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre;
	T dummy;
	bool bFound = false;

	// node 객체에 입력받은 데이터 설정 및 초기화
	node->data = item;
	node->next = NULL;
	// list 에 node 가 존재하지 않는 경우
	if (!length)
	{
		m_List = node;
	}
	// list 에 node 가 하나 이상 존재하는 경우
	else
	{
		// 가장 마지막 node 로 이동 후 삽입
		while (1)
		{
			// 이전 노드를 가리키는 포인터 갱신
			pre = m_curPtr;
			// iteration 을 이용해 node 포인터 갱신.
			GetNextItem(dummy);
			// node 포인터가 마지막 node 를 가리키면 그 뒤에 새로운 node 삽입.
			if (m_curPtr->next == NULL)
			{
				// 마지막 node 와 새로운 node 연결
				m_curPtr->next = node;
				break;
			}
		}
	}
	length++;
}

// 리스트에서 노드 삭제
template <typename T>
void UnsortedLL<T>::Delete(T& item)
{
	bool moreToSearch, found;
	NodeType<T>* location;
	NodeType<T>* pre;

	location = m_List;
	found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (item == location->data)
		{
			found = true;
			item = location->data;

			if (location->data == m_List->data)
				m_List = location->next;
			else
				pre->next = location->next;

			delete location;
		}
		else
		{
			pre = location;
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}
	length--;
}

// 리스트에 있는 item의 데이터를 바꾼다
template <typename T>
int UnsortedLL<T>::Replace(T item)
{
	bool moreToSearch, found;
	NodeType<T>* location;	//변수 선언
	location = m_List;
	found = false;
	moreToSearch = (location != NULL);	//변수 초기화

	while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
	{
		if (item == location->data)
		{
			found = true;
			location->data = item;
		}	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 리스트의 항목에 item을 복사해준다.
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 NULL이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
	}
	if (found)
		return 1;
	else
		return 0;	//수정에 성공하면 1, 그렇지 못하면 0을 리턴한다.
}

// item의 키와 일치하는 키를 가지는 리스트의 데이터를 반환(있다면)
template <typename T>
int UnsortedLL<T>::Get(T& item)
{
	bool moreToSearch, found;
	NodeType<T>* location;

	location = m_List;
	found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (item == location->data)
		{
			found = true;
			item = location->data;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

	if (found)
		return 1;
	else
		return 0;
}


// 리스트의 이터레이터 curPtr을 초기화
template <typename T>
void UnsortedLL<T>::ResetList()
{
	// current pointer 초기화
	m_curPtr = NULL;
}


// 리스트 상 다음 위치에 있는 노드에 접근
template <typename T>
void UnsortedLL<T>::GetNextItem(T& item)
{
	// curPtr이 NULL이라면 처음 node를 가리킴.
	if (m_curPtr == NULL)
	{
		m_curPtr = m_List;
	}
	else
		//curPtr을 다음 노드로 이동
		m_curPtr = m_curPtr->next;

	//item 에 curPtr의 info 를 삽입
	item = m_curPtr->data;
}

#endif	// UNSORTED_LINKED_LIST