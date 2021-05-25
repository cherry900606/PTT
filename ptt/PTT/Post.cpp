#include "Post.h"

Post::Post()
{
	this->postName = "";
	this->content = "";
	this->isDeleted = false;
}
Post::Post(string postName)
{
	this->postName = postName;
	this->content = "";
	this->isDeleted = false;
}
Post::Post(string postName, string content, string author)
{
	this->postName = postName;
	this->content = content;
	this->author = author;
	this->isDeleted = false;
}