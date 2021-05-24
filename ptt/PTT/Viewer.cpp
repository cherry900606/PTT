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
		for (int i = 0; i < board.posts.size(); i++)
		{
			cout << "\t" << i + 1 << "  " << board.posts[i].postName << endl;
		}
	}
	cout << endl << endl;
}
void Viewer::showPost(Post post)
{
	cout << "作者: " << post.author << endl;
	cout << "標題: " << post.postName << endl << endl;
	cout << post.content << endl;
	cout << "---" << endl;
	for (auto it : post.comment)
	{
		cout << it << endl;
	}
	cout << endl << endl;
}