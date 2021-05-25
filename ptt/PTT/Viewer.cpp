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
	cout << endl << endl;
}
void Viewer::showBoard(Board board)
{
	if (board.posts.size() == 0)
	{
		cout << "���ݪO�ثe�S���K��" << endl;
	}
	else
	{
		cout << "\t�s��\t��  ��  ��  �D" << endl;
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
		cout << "�峹�w�Q�R��" << endl;
		return;
	}
	cout << "�@��: " << post.author << endl;
	cout << "���D: " << post.postName << endl << endl;
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