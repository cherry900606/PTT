#include "Board.h"

Board::Board()
{
	this->boardName = "";
}
Board::Board(string name)
{
	this->boardName = name;
	Post post("�w�]�K��", "�ڬO�w�]�K��");
	this->posts.push_back(post);
}