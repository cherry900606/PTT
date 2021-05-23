#include "User.h"

User::User()
{
	this->account = this->password = "";
	this->permissionLevel = GUEST;
}
User::User(string account, string password, int authority)
{
	this->account = account;
	this->password = password;
	this->permissionLevel = authority;
}