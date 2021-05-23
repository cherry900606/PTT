#pragma once
#include <iostream>
#include <vector>
using namespace std;

enum Authority
{
	GUEST,
	USER,
	ADMIN
};
class User
{
public:
	string account;
	string password;
	int permissionLevel;
	User();
	User(string account, string password, int authority);
	vector<int> postsID;
};