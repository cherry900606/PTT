#include "Viewer.h"
void Viewer::showMenu()
{
	cout << endl << endl;
	cout << "        ��������   ��������   ��������" << endl;
	cout << "        ��    ��      ��         ��" << endl;
	cout << "        ��������      ��         ��" << endl;
	cout << "        ��            ��         �� " << endl;
	cout << "        ��            ��         ��" << endl;
	cout << endl << endl;
}
void Viewer::showAllBoard(vector<Board> boards)
{
	cout << endl << endl;
	for (int i = 0; i < boards.size(); i++)
	{
		cout << "\t " << i + 1 << "  �E" << boards[i].boardName <<"�E "<< endl;
	}
}
void Viewer::showBoard(Board board)
{
	if (board.posts.size() == 0)
	{
		cout << "���ݪO�ثe�S���K��" << endl;
	}
	else
	{
		for (int i = 0; i < board.posts.size(); i++)
		{
			cout << "\t" << i + 1 << "  " << board.posts[i].postName << endl;
		}
	}
}
void Viewer::showPost(Post post)
{
	cout << "���D: " << post.postName << endl;
	cout << post.content << endl;
}