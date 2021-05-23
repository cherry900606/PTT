#include "Post.h"

Post::Post()
{
	this->postName = "";
	this->content = "";
}
Post::Post(string postName)
{
	this->postName = postName;
	this->content = "";
}
Post::Post(string postName, string content)
{
	this->postName = postName;
	this->content = content;
}