#include "BoardManager.h"

BoardManager::BoardManager()
{
	// �w�]��l���A
	this->state = MENU;
	this->current_user = -1;
	this->current_board = 0;
	this->current_post = 0;

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
		if (stoi(cmd) - 1 >= boards[current_board].posts.size())
		{
			cout << "���K�夣�s�b" << endl;
			return;
		}
		this->current_post = stoi(cmd) - 1;
		this->state = POST;
	}
	// ��L�ާ@:
	//		- �s�W�K��
}
void BoardManager::postOperation()
{
	string cmd;
	cout << "�W�@��(b) �d��(c) �s��(e) �R���K��(d) �R���d��(t): ";
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
			cout << "0)�� 1)�N�� 2)�b�Y: ";
			cin >> type;
			cin.ignore();

			string comment;
			cout << "�d�����e: " ;
			getline(cin, comment);
			
			for (auto it : boards[current_board].posts[current_post].comment)
			{
				string author = it, upVote = "��", downVote = "�N";
				author.erase(0, 3);
				author = author.substr(0, author.find_first_of(" "));
				author.pop_back();
				if (author == users[current_user].account)
				{
					if (it[0] == upVote[0] && it[1] == upVote[1] && type == 0)
					{
						cout << "���i���Ʊ���I" << endl;
						return;
					}
					else if (it[0] == downVote[0] && it[1] == downVote[1] && type == 1)
					{
						cout << "���i���ƼN��I" << endl;
						return;
					}
				}
			}

			if (type == 0)
				comment = "�� " + users[current_user].account + ": " + comment;
			else if (type == 1)
				comment = "�N " + users[current_user].account + ": " + comment;
			else
				comment = "�� " + users[current_user].account + ": " + comment;
			boards[current_board].posts[current_post].comment.push_back(comment);

			cout << "�d�����\�I" << endl;

			// �g�^�ɮסI�I
			string path = ".\\" + boards[current_board].boardName + "\\" +
				boards[current_board].posts[current_post].postName + ".txt";
			ofstream file(path, ios::app);
			file << comment << endl;
		}
	}
	else if (cmd == "e")
	{
		if (users[current_user].account == boards[current_board].posts[current_post].author)
		{
			string path = ".\\" + boards[current_board].boardName + "\\" +
				boards[current_board].posts[current_post].postName + ".txt";
			string cmd;
			/*cout << "�O�_�s����D(Y/N)? ";    <--------�����޼��D�s��\��
			cin >> cmd;
			if (cmd == "Y")
			{
				string title;
				cin.ignore();
				cout << "�п�J���D: ";
				getline(cin, title);
				boards[current_board].posts[current_post].postName = title;
			}*/

			cout << "�O�_�s�褺��(Y/N)? ";
			cin >> cmd;
			if (cmd == "Y" || cmd == "y")
			{
				string content;
				cout << "�п�J���e(�H :wq ����):" << endl;
				boards[current_board].posts[current_post].content = ""; // ���M��
				while (getline(cin, content))
				{
					if (content == ":wq")
						break;
					boards[current_board].posts[current_post].content += content + "\n";
				}
			}
			cout << "�s�覨�\�I" << endl;

			// �g��
			ofstream file(path);
			file << users[current_user].account << endl;
			file << boards[current_board].posts[current_post].content;
			file << "---" << endl;
			for (auto it : boards[current_board].posts[current_post].comment)
				file << it << endl;
			file.close();
		}
		else
		{
			cout << "����s��O�H���峹�I" << endl;
		}
	}
	else if (cmd == "d")
	{
		// �ۤv�R���ۤv���峹
		if (users[current_user].account == boards[current_board].posts[current_post].author)
		{
			string cmd;
			cout << "�O�_�R���峹(Y/N)? ";
			cin >> cmd;

			if (cmd == "Y" || cmd == "y")
			{
				string path = ".\\" + boards[current_board].boardName + "\\" + "postList.txt";
				string title = boards[current_board].posts[current_post].postName;
				boards[current_board].posts[current_post].isDeleted = true;
				boards[current_board].posts[current_post].postName = "�峹�w�Q�R�� [" + users[current_user].account + "]";

				// �g��
				ifstream file(path);
				string s, result;
				while (getline(file, s))
				{
					if (s != title)
						s += title + "\n";
				}
				file.close();

				ofstream wfile(path);
				wfile << s;
				wfile.close();
			}
		}
		// �޲z���R���O�H���峹
		else if (users[current_user].permissionLevel == ADMIN)
		{
			string cmd;
			cout << "�O�_�R���峹(Y/N)? ";
			cin >> cmd;

			if (cmd == "Y" || cmd == "y")
			{
				string reason;
				cout << "�R����]: ";
				cin.ignore();
				getline(cin, reason);

				string path = ".\\" + boards[current_board].boardName + "\\" + "postList.txt";
				string title = boards[current_board].posts[current_post].postName;
				boards[current_board].posts[current_post].isDeleted = true;
				boards[current_board].posts[current_post].postName = "�峹�w�Q�޲z���R�� [" + users[current_user].account +
					"] ��]: " + reason;

				// �g��
				ifstream file(path);
				string s, result;
				while (getline(file, s))
				{
					if (s != title)
						s += title + "\n";
				}
				file.close();

				ofstream wfile(path);
				wfile << title;
				wfile.close();
			}
		}
		else
		{
			cout << "����R���O�H���峹�I" << endl;
		}
	}
	else if (cmd == "t")
	{
		if (users[current_user].permissionLevel != ADMIN)
		{
			cout << "�u���޲z����i�榹�ާ@�I" << endl;
			return;
		}
		int floor;
		cout << "�п�J�R���Ӽh: ";
		cin >> floor;
		string reason;
		cout << "�п�J�R����]: ";
		cin >> reason;

		boards[current_board].posts[current_post].comment[floor - 1] = "���d���w�Q�޲z���R�� ��]: " + reason;
		/*boards[current_board].posts[current_post].comment.erase(
			boards[current_board].posts[current_post].comment.begin() + floor - 1);*/

		// �g��
		string path = ".\\" + boards[current_board].boardName + "\\" +
			boards[current_board].posts[current_post].postName + ".txt";
		ofstream file(path);
		file << users[current_user].account << endl;
		file << boards[current_board].posts[current_post].content;
		file << "---" << endl;
		for (auto it : boards[current_board].posts[current_post].comment)
			file << it << endl;
		file.close();
	}

	// ��L�ާ@:
	//		- �s��
	//		- �R��
}