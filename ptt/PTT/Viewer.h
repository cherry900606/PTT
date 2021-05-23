#pragma once
#include <iostream>
#include <vector>
#include "Board.h"
#include "Post.h"
using namespace std;

class Viewer
{
public:
	Viewer(){}
	void showMenu(); // 印 menu
	void showAllBoard(vector<Board> boards); // 印所有看板
	void showBoard(Board board); // 印特定看板
	void showPost(Post post); // 印貼文
};