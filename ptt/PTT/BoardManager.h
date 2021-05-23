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
    vector <User> users; // 動態儲存使用者
    vector <Board> boards; // 分類看板
    int current_user; // 目前上線的使用者index
    int current_board; // 目前選到第幾個board
    int current_post; // 目前第幾則貼文

    BoardState state; // 存取狀態
    Viewer viewer; // 負責印東西到螢幕

    void loop(); // 狀態們的Loop
    void menuLogin(); // 使用者登入
    void selectBoard(); // 選擇哪個板
    void selectPost(); // 選擇哪則貼文
    void postOperation(); // 瀏覽貼文時的各種操作
};
