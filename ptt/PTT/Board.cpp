#include "Board.h"

Board::Board()
{
	this->boardName = "";
}

// 建立新板，包含: 板名、預設貼文、存貼文的資料夾、存貼文列表的.txt、貼文
Board::Board(string name)
{
	this->boardName = name;
	Post post("預設貼文", "我是預設貼文", "admin");
	this->posts.push_back(post);

	// create folder
	string pathName = ".\\" + name;
	char path[100] = {};
	for (int i = 0; i < pathName.size(); i++)
	{
		path[i] = pathName[i];
	}
	_mkdir(path); // 直接根據板名創造相同名稱的資料夾 (應該不會在下次被覆寫掉)
	ofstream file(pathName + "\\postList.txt", ios::app); // 紀錄板上貼文 
	file << "";
	file.close();

	ifstream inputFile(pathName + "\\postList.txt"); // 讀檔
	string postName, content;
	while (getline(inputFile, postName)) // 讀取紀錄的所有文章標題
	{
		Post post(postName);
		ifstream fileOfPost(pathName + "\\" + postName + ".txt"); // 打開相對應的post
		fileOfPost >> post.author; // 第一行是作者
		while (getline(fileOfPost, content)) // 後面是內容
		{
			if (content == "---") // 後面是留言，另外存
			{
				break;
			}
			post.content += content + "\n";
		}
		while (getline(fileOfPost, content))
		{
			post.comment.push_back(content);
		}
		fileOfPost.close();
		posts.push_back(post); // 存進去
	}
	
	inputFile.close();
}