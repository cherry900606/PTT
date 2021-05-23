#include "Board.h"

Board::Board()
{
	this->boardName = "";
}
Board::Board(string name)
{
	this->boardName = name;
	Post post("預設貼文", "我是預設貼文");
	this->posts.push_back(post);
}