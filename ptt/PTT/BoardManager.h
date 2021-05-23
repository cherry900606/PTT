#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Board.h"
#include "User.h"
#include "Viewer.h"
using namespace std;

enum BoardState
{
    MENU,
    SELECT_BOARD,
    BOARD,
    POST,
    EESC
};

class BoardManager
{
public:
    BoardManager();
    vector <User> users; // �ʺA�x�s�ϥΪ�
    vector <Board> boards; // �����ݪO
    int current_user; // �ثe�W�u���ϥΪ�index
    int current_board; // �ثe���ĴX��board
    int current_post; // �ثe�ĴX�h�K��

    BoardState state; // �s�����A
    Viewer viewer; // �t�d�L�F���ù�

    void loop(); // ���A�̪�Loop
    void menuLogin(); // �ϥΪ̵n�J
    void selectBoard(); // ��ܭ��ӪO
    void selectPost(); // ��ܭ��h�K��
    void postOperation(); // �s���K��ɪ��U�ؾާ@
};
