#include "Viewer.h"
void Viewer::showMenu()
{
	cout << endl << endl;
	cout << "        ■■■■   ■■■■   ■■■■" << endl;
	cout << "        ■    ■      ■         ■" << endl;
	cout << "        ■■■■      ■         ■" << endl;
	cout << "        ■            ■         ■ " << endl;
	cout << "        ■            ■         ■" << endl;
	cout << endl << endl;
}
void Viewer::showAllBoard(vector<Board> boards)
{
	cout << endl << endl;
	for (int i = 0; i < boards.size(); i++)
	{
		cout << "\t " << i + 1 << "  ‧" << boards[i].boardName <<"‧ "<< endl;
	}
	cout << endl << endl;
}
void Viewer::showBoard(Board board)
{
	if (board.posts.size() == 0)
	{
		cout << "本看板目前沒有貼文" << endl;
	}
	else
	{
		cout << "\t編號\t文  章  標  題" << endl;
		for (int i = 0; i < board.posts.size(); i++)
		{
			cout << "\t  " << i + 1 << "\t" << board.posts[i].postName << endl;
		}
	}
	cout << endl << endl;
}
void Viewer::showPost(Post post)
{
	if (post.isDeleted)
	{
		cout << "文章已被刪除" << endl;
		return;
	}
	cout << "作者: " << post.author << endl;
	cout << "標題: " << post.postName << endl << endl;
	cout << post.content << endl;
	cout << "---" << endl;

	int index = 1;
	for (auto it : post.comment)
	{
		cout << index << "F " << it << endl;
		index++;
	}
	cout << endl << endl;
}