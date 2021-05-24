#include "Board.h"

Board::Board()
{
	this->boardName = "";
}

// �إ߷s�O�A�]�t: �O�W�B�w�]�K��B�s�K�媺��Ƨ��B�s�K��C��.txt�B�K��
Board::Board(string name)
{
	this->boardName = name;
	Post post("�w�]�K��", "�ڬO�w�]�K��", "admin");
	this->posts.push_back(post);

	// create folder
	string pathName = ".\\" + name;
	char path[100] = {};
	for (int i = 0; i < pathName.size(); i++)
	{
		path[i] = pathName[i];
	}
	_mkdir(path); // �����ھڪO�W�гy�ۦP�W�٪���Ƨ� (���Ӥ��|�b�U���Q�мg��)
	ofstream file(pathName + "\\postList.txt", ios::app); // �����O�W�K�� 
	file << "";
	file.close();

	ifstream inputFile(pathName + "\\postList.txt"); // Ū��
	string postName, content;
	while (getline(inputFile, postName)) // Ū���������Ҧ��峹���D
	{
		Post post(postName);
		ifstream fileOfPost(pathName + "\\" + postName + ".txt"); // ���}�۹�����post
		fileOfPost >> post.author; // �Ĥ@��O�@��
		while (getline(fileOfPost, content)) // �᭱�O���e
		{
			if (content == "---") // �᭱�O�d���A�t�~�s
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
		posts.push_back(post); // �s�i�h
	}
	
	inputFile.close();
}