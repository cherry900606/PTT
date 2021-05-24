#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Post
{
public:
	string postName;
	string content;
	string author;
	vector<string> comment;

	Post();
	Post(string postName);
	Post(string postName, string content, string author);
};