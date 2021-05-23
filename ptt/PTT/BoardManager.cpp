#include "BoardManager.h"

BoardManager::BoardManager()
{
	// 預設初始狀態
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

	// 系統自動產生管理員
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
			cout << "我是 " << users[current_user].account << endl;
			selectBoard();
			system("pause");
		}
		else if (this->state == BOARD) // display each post & select post
		{
			system("cls");
			viewer.showBoard(boards[current_board]);
			cout << "我是 " << users[current_user].account << endl;
			selectPost();
			system("pause");
		}
		else if (this->state == POST) // display post next
		{
			system("cls");
			viewer.showPost(boards[current_board].posts[current_post]);
			cout << "我是 " << users[current_user].account << endl;
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
	cout << "請輸入代號，或以 guest 參觀，或以 new 註冊:";
	cin >> account;
	if (account == "guest") // 遊客
	{
		User user("遊客", "", GUEST);
		this->users.push_back(user);
		this->current_user = users.size() - 1;
		this->state = SELECT_BOARD;
	}
	else if (account == "new") // 註冊新帳號
	{
		string newAccount, password;
		cout << "請輸入代號: ";
		cin >> newAccount;
		cout << "請輸入密碼: ";
		cin >> password;

		// 檢查新帳號是否重複
		ifstream checkFile("UserInfo.txt");
		string recordAccount, recordPassword;
		while (checkFile >> recordAccount >> recordPassword)
		{
			if (newAccount == recordAccount)
			{
				cout << "註冊失敗，此帳號名稱已存在！" << endl;
				system("pause");
				return;
			}
		}
		checkFile.close();

		// 寫入.txt儲存用戶帳密
		ofstream file("UserInfo.txt", ios::app);
		file << newAccount << " " << password << endl;
		file.close();

		// 存進users
		User user(newAccount, password, USER);
		users.push_back(user);
	}
	else // 一般登入
	{
		string password;
		cout << "請輸入密碼: ";
		cin >> password;

		// set user
		for (int i = 0; i < users.size(); i++)
		{
			if (account == users[i].account && password == users[i].password)
			{
				cout << "登入成功！" << endl;
				this->state = SELECT_BOARD;
				this->current_user = i;
				system("pause");
				return;
			}
			if (account == users[i].account && password != users[i].password)
			{
				cout << "密碼輸入錯誤" << endl;
				system("pause");
				return;
			}
		}
		cout << "無此用戶！" << endl;
		system("pause");
	}
}
void BoardManager::selectBoard()
{
	string cmd;
	cout << "看板選擇(回主選單:b): ";
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
	cout << "貼文選擇(回主選單:b): ";
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
	// 其他操作:
	//		- 新增貼文
}
void BoardManager::postOperation()
{
	string cmd;
	cout << "回主選單(b):";
	cin >> cmd;

	if (cmd == "b")
	{
		this->state = BOARD;
	}
	// 其他操作:
	//		- 留言(推噓)
	//		- 編輯
	//		- 刪除
}