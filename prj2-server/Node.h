#pragma once

/**
*	링크 시스템에서 이용될 노드 구조체
*/
template <typename T>
struct NodeType
{
	T data;			///< 각 노드의 데이터
	NodeType* next;	///< 다음 노드를 가르키기 위한 노드 pointer
};
