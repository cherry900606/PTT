#pragma once
#include <vector>
#include <iostream>
#include "Post.h"
using namespace std;

class Board
{
public:
	string boardName;
	vector<Post> posts;
	Board();
	Board(string name);
	
};