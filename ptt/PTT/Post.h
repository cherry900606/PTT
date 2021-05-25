#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Post
{
public:
	string postName; // �K��W��
	string content; // ����
	string author; // �@��
	vector<string> comment; // �d��
	bool isDeleted; // �Q�R��

	Post();
	Post(string postName);
	Post(string postName, string content, string author);
};