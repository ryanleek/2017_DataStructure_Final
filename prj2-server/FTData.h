#pragma once
#include <fstream>
using namespace std;

// ���� ������ �̿�Ǵ� ����ü
struct FTData 
{
	static const int buffersize = 8192; // �ִ� ���� ������

	string fileName; // ������ �̸�
	int fileOffset;
	int fileSize;
	int rBytes;

	ifstream ifs;
	ofstream ofs;
	char buffer[buffersize];
};