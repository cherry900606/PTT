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
	void showMenu(); // �L menu
	void showAllBoard(vector<Board> boards); // �L�Ҧ��ݪO
	void showBoard(Board board); // �L�S�w�ݪO
	void showPost(Post post); // �L�K��
};