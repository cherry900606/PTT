#pragma once
#include <iostream>
using namespace std;

class Post
{
public:
	string postName;
	string content;
	// string comment
	Post();
	Post(string postName);
	Post(string postName, string content);
};