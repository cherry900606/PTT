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

	// �t�Φ۰ʲ��ͺ޲z��
	User user("admin", "123", ADMIN);
	this->users.push_back(user);

	// load board information
	file.open("BoardList.txt");
	string boardName;
	while (getline(file, boardName))
	{
		// create board
		Board board(boardName);
		this->boards.push_back(board);
	}
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
		cout << "���U���\�A�Э��s�n�J�I" << endl;
		system("pause");

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
	cout << "�W�@��(b) �s�W�K��(n) ��ܶK��(�s��): ";
	cin >> cmd;

	if (cmd == "b")
	{
		this->state = SELECT_BOARD;
	}
	else if (cmd == "n")
	{
		if (users[current_user].permissionLevel == GUEST)
		{
			cout << "�u���n�J���ϥΪ̤~��s�W�K��I" << endl;
			return;
		}

		system("cls");

		Post post;
		post.author = users[current_user].account;
		cin.ignore();
		cout << "�п�J���D: ";
		getline(cin, post.postName);
		cout << "�п�J���e(�H :wq ������J): " << endl;

		string s;
		while (getline(cin, s))
		{
			if (s == ":wq")
				break;
			post.content += s + "\n";
		}
		cout << "�K��s�W���\" << endl;

		boards[current_board].posts.push_back(post);

		// �g��
		string path = ".\\" + boards[current_board].boardName + "\\" +
			post.postName + ".txt";
		ofstream file(path);
		file << post.author << endl;
		file << post.content;
		file << "---" << endl;
		file.close();

		path= ".\\" + boards[current_board].boardName + "\\" +
			"postList.txt";
		ofstream wfile(path, ios::app);
		wfile << post.postName << endl;
		wfile.close();

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
	cout << "�W�@��(b) �d��(c): ";
	cin >> cmd;

	if (cmd == "b")
	{
		this->state = BOARD;
	}
	else if (cmd == "c")
	{
		if (users[current_user].permissionLevel == GUEST)
		{
			cout << "�u���n�J���ϥΪ̤~��d���I" << endl;
		}
		else
		{
			int type;
			cout << "0)�� 1)�N��: ";
			cin >> type;
			cin.ignore();

			string comment;
			cout << "�d�����e: " ;
			getline(cin, comment);
			
			if (type == 0)
				comment = "�� " + users[current_user].account + ": " + comment;
			else
				comment = "�N " + users[current_user].account + ": " + comment;
			boards[current_board].posts[current_post].comment.push_back(comment);

			cout << "�d�����\�I" << endl;

			// �g�^�ɮסI�I
			string path = ".\\" + boards[current_board].boardName + "\\" +
				boards[current_board].posts[current_post].postName + ".txt";
			ofstream file(path, ios::app);
			file << comment << endl;
		}
	}
	// ��L�ާ@:
	//		- �s��
	//		- �R��
}