// 井字棋 —— 无前置声明，从上读到下一条线
// 编译：g++ tictactoe.cpp -o tictactoe.exe

#include <iostream>
#include <cstdlib>

char board[3][3] = { {' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '} };
char turn = 'X';   // X 先走

// ── 画棋盘 ──
void draw() {
    std::cout << std::endl;
    std::cout << "  1   2   3      ← 格子编号" << std::endl;
    std::cout << std::endl;
    for (int r = 0; r < 3; r++) {
        std::cout << "  " << board[r][0]
                  << " | " << board[r][1]
                  << " | " << board[r][2];
        if (r == 0) std::cout << "      ← 编号对应位置";
        std::cout << std::endl;
        if (r < 2) std::cout << " ---+---+---" << std::endl;
    }
    std::cout << std::endl;
}

// ── 编号(1~9) 转 棋盘坐标，空格才让落 ──
bool drop(int pos) {
    if (pos < 1 || pos > 9) return false;
    int r = (pos - 1) / 3;
    int c = (pos - 1) % 3;
    if (board[r][c] != ' ') return false;
    board[r][c] = turn;
    return true;
}

// ── 检查 turn 玩家是否赢了 ──
bool win() {
    for (int r = 0; r < 3; r++)
        if (board[r][0] == turn && board[r][1] == turn && board[r][2] == turn)
            return true;
    for (int c = 0; c < 3; c++)
        if (board[0][c] == turn && board[1][c] == turn && board[2][c] == turn)
            return true;
    if (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
        return true;
    if (board[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
        return true;
    return false;
}

// ── 检查是否满了 ──
bool full() {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == ' ') return false;
    return true;
}

// ═══════════════ main ═══════════════
int main() {
    system("chcp 65001 > nul");

    while (true) {
        draw();

        int pos;
        std::cout << "玩家 " << turn << "，落哪个格子？ ";
        std::cin >> pos;

        if (!drop(pos)) {
            std::cout << "这里不能落，换一个。" << std::endl;
            continue;
        }

        if (win()) {
            draw();
            std::cout << "玩家 " << turn << " 赢了！" << std::endl;
            break;
        }
        if (full()) {
            draw();
            std::cout << "平局！" << std::endl;
            break;
        }

        turn = (turn == 'X') ? 'O' : 'X';   // 换人
    }
    return 0;
}
