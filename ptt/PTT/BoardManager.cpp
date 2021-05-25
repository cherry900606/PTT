#include "BoardManager.h"

BoardManager::BoardManager()
{
	// 預設初始狀態
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
		if (stoi(cmd) - 1 >= boards[current_board].posts.size())
		{
			cout << "此貼文不存在" << endl;
			return;
		}
		this->current_post = stoi(cmd) - 1;
		this->state = POST;
	}
	// 其他操作:
	//		- 新增貼文
}
void BoardManager::postOperation()
{
	string cmd;
	cout << "上一頁(b) 留言(c) 編輯(e) 刪除貼文(d) 刪除留言(t): ";
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
			cout << "0)推 1)噓文 2)箭頭: ";
			cin >> type;
			cin.ignore();

			string comment;
			cout << "留言內容: " ;
			getline(cin, comment);
			
			for (auto it : boards[current_board].posts[current_post].comment)
			{
				string author = it, upVote = "推", downVote = "噓";
				author.erase(0, 3);
				author = author.substr(0, author.find_first_of(" "));
				author.pop_back();
				if (author == users[current_user].account)
				{
					if (it[0] == upVote[0] && it[1] == upVote[1] && type == 0)
					{
						cout << "不可重複推文！" << endl;
						return;
					}
					else if (it[0] == downVote[0] && it[1] == downVote[1] && type == 1)
					{
						cout << "不可重複噓文！" << endl;
						return;
					}
				}
			}

			if (type == 0)
				comment = "推 " + users[current_user].account + ": " + comment;
			else if (type == 1)
				comment = "噓 " + users[current_user].account + ": " + comment;
			else
				comment = "→ " + users[current_user].account + ": " + comment;
			boards[current_board].posts[current_post].comment.push_back(comment);

			cout << "留言成功！" << endl;

			// 寫回檔案！！
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
			/*cout << "是否編輯標題(Y/N)? ";    <--------先不管標題編輯功能
			cin >> cmd;
			if (cmd == "Y")
			{
				string title;
				cin.ignore();
				cout << "請輸入標題: ";
				getline(cin, title);
				boards[current_board].posts[current_post].postName = title;
			}*/

			cout << "是否編輯內文(Y/N)? ";
			cin >> cmd;
			if (cmd == "Y" || cmd == "y")
			{
				string content;
				cout << "請輸入內容(以 :wq 結束):" << endl;
				boards[current_board].posts[current_post].content = ""; // 先清空
				while (getline(cin, content))
				{
					if (content == ":wq")
						break;
					boards[current_board].posts[current_post].content += content + "\n";
				}
			}
			cout << "編輯成功！" << endl;

			// 寫檔
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
			cout << "不能編輯別人的文章！" << endl;
		}
	}
	else if (cmd == "d")
	{
		// 自己刪除自己的文章
		if (users[current_user].account == boards[current_board].posts[current_post].author)
		{
			string cmd;
			cout << "是否刪除文章(Y/N)? ";
			cin >> cmd;

			if (cmd == "Y" || cmd == "y")
			{
				string path = ".\\" + boards[current_board].boardName + "\\" + "postList.txt";
				string title = boards[current_board].posts[current_post].postName;
				boards[current_board].posts[current_post].isDeleted = true;
				boards[current_board].posts[current_post].postName = "文章已被刪除 [" + users[current_user].account + "]";

				// 寫檔
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
		// 管理員刪除別人的文章
		else if (users[current_user].permissionLevel == ADMIN)
		{
			string cmd;
			cout << "是否刪除文章(Y/N)? ";
			cin >> cmd;

			if (cmd == "Y" || cmd == "y")
			{
				string reason;
				cout << "刪除原因: ";
				cin.ignore();
				getline(cin, reason);

				string path = ".\\" + boards[current_board].boardName + "\\" + "postList.txt";
				string title = boards[current_board].posts[current_post].postName;
				boards[current_board].posts[current_post].isDeleted = true;
				boards[current_board].posts[current_post].postName = "文章已被管理員刪除 [" + users[current_user].account +
					"] 原因: " + reason;

				// 寫檔
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
			cout << "不能刪除別人的文章！" << endl;
		}
	}
	else if (cmd == "t")
	{
		if (users[current_user].permissionLevel != ADMIN)
		{
			cout << "只有管理員能進行此操作！" << endl;
			return;
		}
		int floor;
		cout << "請輸入刪除樓層: ";
		cin >> floor;
		string reason;
		cout << "請輸入刪除原因: ";
		cin >> reason;

		boards[current_board].posts[current_post].comment[floor - 1] = "此留言已被管理員刪除 原因: " + reason;
		/*boards[current_board].posts[current_post].comment.erase(
			boards[current_board].posts[current_post].comment.begin() + floor - 1);*/

		// 寫檔
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

	// 其他操作:
	//		- 編輯
	//		- 刪除
}