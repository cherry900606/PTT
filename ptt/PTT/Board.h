#pragma once
#include <vector>
#include <iostream>
#include <direct.h>
#include <fstream>
#include <string>
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