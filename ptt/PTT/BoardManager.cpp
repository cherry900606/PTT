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

	// 系統自動產生管理員
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
		cout << "註冊成功，請重新登入！" << endl;
		system("pause");

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
	cout << "上一頁(b) 新增貼文(n) 選擇貼文(編號): ";
	cin >> cmd;

	if (cmd == "b")
	{
		this->state = SELECT_BOARD;
	}
	else if (cmd == "n")
	{
		if (users[current_user].permissionLevel == GUEST)
		{
			cout << "只有登入的使用者才能新增貼文！" << endl;
			return;
		}

		system("cls");

		Post post;
		post.author = users[current_user].account;
		cin.ignore();
		cout << "請輸入標題: ";
		getline(cin, post.postName);
		cout << "請輸入內容(以 :wq 結束輸入): " << endl;

		string s;
		while (getline(cin, s))
		{
			if (s == ":wq")
				break;
			post.content += s + "\n";
		}
		cout << "貼文新增成功" << endl;

		boards[current_board].posts.push_back(post);

		// 寫檔
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
	// 其他操作:
	//		- 新增貼文
}
void BoardManager::postOperation()
{
	string cmd;
	cout << "上一頁(b) 留言(c): ";
	cin >> cmd;

	if (cmd == "b")
	{
		this->state = BOARD;
	}
	else if (cmd == "c")
	{
		if (users[current_user].permissionLevel == GUEST)
		{
			cout << "只有登入的使用者才能留言！" << endl;
		}
		else
		{
			int type;
			cout << "0)推 1)噓文: ";
			cin >> type;
			cin.ignore();

			string comment;
			cout << "留言內容: " ;
			getline(cin, comment);
			
			if (type == 0)
				comment = "推 " + users[current_user].account + ": " + comment;
			else
				comment = "噓 " + users[current_user].account + ": " + comment;
			boards[current_board].posts[current_post].comment.push_back(comment);

			cout << "留言成功！" << endl;

			// 寫回檔案！！
			string path = ".\\" + boards[current_board].boardName + "\\" +
				boards[current_board].posts[current_post].postName + ".txt";
			ofstream file(path, ios::app);
			file << comment << endl;
		}
	}
	// 其他操作:
	//		- 編輯
	//		- 刪除
}