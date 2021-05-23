#include "BoardManager.h"

BoardManager::BoardManager()
{
	// �w�]��l���A
	this->state = MENU;
	this->current_user = -1;

	// load user information
	ifstream file("UserInfo.txt");
	string account, password;
	while (file >> account >> password)
	{
		User user(account, password, USER);
		this->users.push_back(user);
	}
	file.close();

	// load board information
	file.open("BoardList.txt");
	string boardName;
	while (getline(file, boardName))
	{
		Board board(boardName);
		this->boards.push_back(board);
	}

	// �t�Φ۰ʲ��ͺ޲z��
	User user("admin", "123", ADMIN);
	this->users.push_back(user);
}
void BoardManager::loop()
{
	while (1)
	{
		if (this->state == MENU) // enter the account
		{
			system("cls");
			viewer.showMenu();
			menuLogin();
		}
		else if (this->state == SELECT_BOARD) // display & select next operation
		{
			system("cls");
			viewer.showAllBoard(this->boards);
			cout << "�ڬO " << users[current_user].account << endl;
			selectBoard();
			system("pause");
		}
		else if (this->state == BOARD) // display each post & select post
		{
			system("cls");
			viewer.showBoard(boards[current_board]);
			cout << "�ڬO " << users[current_user].account << endl;
			selectPost();
			system("pause");
		}
		else if (this->state == POST) // display post next
		{
			system("cls");
			viewer.showPost(boards[current_board].posts[current_post]);
			cout << "�ڬO " << users[current_user].account << endl;
			postOperation();
			system("pause");
		}
		else if (this->state == EESC) // exit the loop
		{
			return;
		}
	}
}
void BoardManager::menuLogin()
{
	string account;
	cout << "�п�J�N���A�ΥH guest ���[�A�ΥH new ���U:";
	cin >> account;
	if (account == "guest") // �C��
	{
		User user("�C��", "", GUEST);
		this->users.push_back(user);
		this->current_user = users.size() - 1;
		this->state = SELECT_BOARD;
	}
	else if (account == "new") // ���U�s�b��
	{
		string newAccount, password;
		cout << "�п�J�N��: ";
		cin >> newAccount;
		cout << "�п�J�K�X: ";
		cin >> password;

		// �ˬd�s�b���O�_����
		ifstream checkFile("UserInfo.txt");
		string recordAccount, recordPassword;
		while (checkFile >> recordAccount >> recordPassword)
		{
			if (newAccount == recordAccount)
			{
				cout << "���U���ѡA���b���W�٤w�s�b�I" << endl;
				system("pause");
				return;
			}
		}
		checkFile.close();

		// �g�J.txt�x�s�Τ�b�K
		ofstream file("UserInfo.txt", ios::app);
		file << newAccount << " " << password << endl;
		file.close();

		// �s�iusers
		User user(newAccount, password, USER);
		users.push_back(user);
	}
	else // �@��n�J
	{
		string password;
		cout << "�п�J�K�X: ";
		cin >> password;

		// set user
		for (int i = 0; i < users.size(); i++)
		{
			if (account == users[i].account && password == users[i].password)
			{
				cout << "�n�J���\�I" << endl;
				this->state = SELECT_BOARD;
				this->current_user = i;
				system("pause");
				return;
			}
			if (account == users[i].account && password != users[i].password)
			{
				cout << "�K�X��J���~" << endl;
				system("pause");
				return;
			}
		}
		cout << "�L���Τ�I" << endl;
		system("pause");
	}
}
void BoardManager::selectBoard()
{
	string cmd;
	cout << "�ݪO���(�^�D���:b): ";
	cin >> cmd;

	if (cmd == "b")
	{
		this->state = MENU;
	}
	else
	{
		this->current_board = stoi(cmd) - 1;
		this->state = BOARD;
	}
}
void BoardManager::selectPost()
{
	string cmd;
	cout << "�K����(�^�D���:b): ";
	cin >> cmd;

	if (cmd == "b")
	{
		this->state = SELECT_BOARD;
	}
	else
	{
		this->current_post = stoi(cmd) - 1;
		this->state = POST;
	}
	// ��L�ާ@:
	//		- �s�W�K��
}
void BoardManager::postOperation()
{
	string cmd;
	cout << "�^�D���(b):";
	cin >> cmd;

	if (cmd == "b")
	{
		this->state = BOARD;
	}
	// ��L�ާ@:
	//		- �d��(���N)
	//		- �s��
	//		- �R��
}