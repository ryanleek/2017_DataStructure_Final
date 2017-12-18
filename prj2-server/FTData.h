#pragma once
#include <fstream>
using namespace std;

// 파일 전송이 이용되는 구조체
struct FTData 
{
	static const int buffersize = 8192; // 최대 버퍼 사이즈

	string fileName; // 파일의 이름
	int fileOffset;
	int fileSize;
	int rBytes;

	ifstream ifs;
	ofstream ofs;
	char buffer[buffersize];
};