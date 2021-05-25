#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Post
{
public:
	string postName; // 貼文名稱
	string content; // 內文
	string author; // 作者
	vector<string> comment; // 留言
	bool isDeleted; // 被刪掉

	Post();
	Post(string postName);
	Post(string postName, string content, string author);
};