//
//  Akari_parallel.cpp
//  data structure
//
//  Created by Walker on 2019/7/11.
//  Copyright © 2019 Carves Von. All rights reserved.
//

// #include "Akari_parallel.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <sstream>
#include <ctime>
#include <pthread.h>

#define DOT -3
#define EMPTY -2

#define BLOCK -1
#define BLOCK_0 0
#define BLOCK_1 1
#define BLOCK_2 2
#define BLOCK_3 3
#define BLOCK_4 4
#define BLUB 5
#define COVER 6

using namespace std;

namespace aka{
    
#define DOT -3
#define EMPTY -2

#define BLOCK -1
#define BLOCK_0 0
#define BLOCK_1 1
#define BLOCK_2 2
#define BLOCK_3 3
#define BLOCK_4 4
#define BLUB 5
#define COVER 6
    void printG(vector<vector<int>>& g);
    typedef struct Node{
        int x;
        int y;
        int value;
        Node* next;
    } Barrier, *Barr_list;
    
    
    
    int m, n;
    vector<vector<int> > g_board;
    bool isSolved;
    
    Barr_list makeBarrierList(vector<vector<int >> &g) {
        Barr_list head = NULL, p = NULL;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (g[i][j] == BLOCK_0) { // 0号方块最先处理
                    Barrier *q = (Barrier*) malloc(sizeof(Barrier));
                    q->x = i; q->y = j; q->value = BLOCK_0; q->next = NULL;
                    if (head == NULL)
                        head = p = q;
                    else{
                        p->next =q; p = p->next;
                    }
                }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (g[i][j] == BLOCK_4) {
                    Barrier *q = (Barrier*) malloc(sizeof(Barrier));
                    q->x = i; q->y = j; q->value = BLOCK_4; q->next = NULL;
                    if (head == NULL)
                        head = p = q;
                    else{
                        p->next =q; p = p->next;
                    }
                }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (g[i][j] == BLOCK_3) {
                    Barrier *q = (Barrier*) malloc(sizeof(Barrier));
                    q->x = i; q->y = j; q->value = BLOCK_3; q->next = NULL;
                    if (head == NULL)
                        head = p = q;
                    else{
                        p->next =q; p = p->next;
                    }
                }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (g[i][j] == BLOCK_2) {
                    Barrier *q = (Barrier*) malloc(sizeof(Barrier));
                    q->x = i; q->y = j; q->value = BLOCK_2; q->next = NULL;
                    if (head == NULL)
                        head = p = q;
                    else{
                        p->next =q; p = p->next;
                    }
                }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (g[i][j] == BLOCK_1) { // 二号方块最后处理
                    Barrier *q = (Barrier*) malloc(sizeof(Barrier));
                    q->x = i; q->y = j; q->value = BLOCK_1; q->next = NULL;
                    if (head == NULL)
                        head = p = q;
                    else{
                        p->next =q; p = p->next;
                    }
                }
        return head;
    }
    
    void copy_board(vector<vector<int> >& board1, const vector<vector<int> >& board2) {
        for (int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                board1[i][j] = board2[i][j];
    }
    
    
    // 设置dot的原因是，当前的黑色块选择了这种放置方法，那么其他相邻黑色块想要在dot处放置灯泡时就不被允许了
    bool put_dot(vector<vector<int> >& board, int x, int y) {
        if (x == 3 && y == 6){}
//            printG(board);
        if (x < 0 || x >= n || y < 0 || y >= m) return true; // 超出边界返回true
        if (board[x][y] == BLUB) return false; // 如果该点已经放置了灯泡，不能设置为dot了
        else if (board[x][y] == EMPTY)
            board[x][y] = DOT;
        return true;
    }
    
    bool put_blub(vector<vector<int> >& board, int x, int y) {
        if (x < 0 || x >= n || y < 0 || y >= m) return false; // 超出边界
        if (board[x][y] != EMPTY && board[x][y] != BLUB) return false; // 如果不是空闲位置或者已经放置了灯泡
        else if (board[x][y] == BLUB) return true;
        // 灯光蔓延
        board[x][y] = BLUB;
        for (int i = x+1; i < n && (board[i][y] <= EMPTY || board[i][y] == COVER); i++)
            board[i][y] = COVER;
        for (int i = x-1; i >=0 && (board[i][y] <= EMPTY|| board[i][y] == COVER); i--)
            board[i][y] = COVER;
        for (int j = y+1; j < m && (board[x][j] <= EMPTY|| board[x][j] == COVER); j++)
            board[x][j] = COVER;
        for (int j = y-1; j >=0 && (board[x][j] <= EMPTY|| board[x][j] == COVER); j--)
            board[x][j] = COVER;
        return true;
        
    }
    
    int next_empty(int last, vector<vector<int> >& board) {
        int row = (last+1) / m;
        int col = (last+1) % m;
        int i, j;
        for (i = row; i < n; i++)
            for (i== row?j=col:j = 0; j < m; j++)
                if (board[i][j] == EMPTY) {
                    return i * m + j;
                }
        return -1;
    }
    
    bool is_complete(vector<vector<int> >& g) {
        for (int x = 0; x < n; x++)
            for (int y = 0; y < m; y++) {
                if (g[x][y] <= EMPTY) return false;
            }
        return true;
    }
    
    bool handle_empty(int cur, vector<vector<int> >& g) {
        if (isSolved) return true;
        bool handle = false;
        vector<vector<int> >* cp_board = NULL;
        if (is_complete(g)) {
            copy_board(g_board, g);
            isSolved = true;
            return true;
        }
        if (cur == -1) // 如果没有空位可以选择了
            return false;
        cp_board = new vector<vector<int> >(n, vector<int>(m, 0));
        copy_board(*cp_board, g);
        put_blub(*cp_board, cur / m, cur % m);
        handle = handle_empty(next_empty(cur, *cp_board), *cp_board);
        if (!handle) {
            // 如果放置不能解决问题，那么就不要在当前坐标放置灯泡
            copy_board(*cp_board, g);
            handle = handle_empty(next_empty(cur, *cp_board), *cp_board);
        }
        free(cp_board);
        return handle;
    }
    
    // for debug
    void printG(vector<vector<int> >& g) {
        for (vector<int> v : g) {
            for (int n : v) {
                if (n < 0)
                    cout << n << " ";
                else
                    cout << " " << n << " ";
            }
            cout  << endl;
        }
        cout << endl;
    }
    bool solve_puzzle(Barrier* barr, vector<vector<int> >& g) {
        if (isSolved) return true;
        if (NULL != barr) {
            Barrier *p = barr;
            vector<vector<int> >* cp_board = new vector<vector<int> >(n, vector<int>(m, 0));
            int r = barr->x, c = barr->y; // r是列号，c是行号
            bool handle = false; // 用来保存是否解决w
            
            copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
            switch (p->value) {
                case 4:
                    if (put_blub(*cp_board, r-1, c) && put_blub(*cp_board, r+1, c)
                            && put_blub(*cp_board, r, c+1) && put_blub(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    break;
                case 3:
                    if (put_dot(*cp_board, r-1, c) && put_blub(*cp_board, r+1, c)
                        && put_blub(*cp_board, r, c+1) && put_blub(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_blub(*cp_board, r-1, c) && put_dot(*cp_board, r+1, c)
                        && put_blub(*cp_board, r, c+1) && put_blub(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_blub(*cp_board, r-1, c) && put_blub(*cp_board, r+1, c)
                        && put_dot(*cp_board, r, c+1) && put_blub(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_blub(*cp_board, r-1, c) && put_blub(*cp_board, r+1, c)
                        && put_blub(*cp_board, r, c+1) && put_dot(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    break;
                case 2:
                    
                    if (put_dot(*cp_board, r-1, c) && put_dot(*cp_board, r+1, c)
                        && put_blub(*cp_board, r, c+1) && put_blub(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
//                    printG(*cp_board);
                    if (!isSolved && put_blub(*cp_board, r-1, c) && put_dot(*cp_board, r+1, c)
                        && put_dot(*cp_board, r, c+1) && put_blub(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_blub(*cp_board, r-1, c) && put_blub(*cp_board, r+1, c)
                        && put_dot(*cp_board, r, c+1) && put_dot(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_dot(*cp_board, r-1, c) && put_blub(*cp_board, r+1, c)
                        && put_dot(*cp_board, r, c+1) && put_blub(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_blub(*cp_board, r-1, c) && put_dot(*cp_board, r+1, c)
                        && put_blub(*cp_board, r, c+1) && put_dot(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_dot(*cp_board, r-1, c) && put_blub(*cp_board, r+1, c)
                        && put_blub(*cp_board, r, c+1) && put_dot(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    break;
                case 1:
                    if (put_blub(*cp_board, r-1, c) && put_dot(*cp_board, r+1, c)
                        && put_dot(*cp_board, r, c+1) && put_dot(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_dot(*cp_board, r-1, c) && put_blub(*cp_board, r+1, c)
                        && put_dot(*cp_board, r, c+1) && put_dot(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_dot(*cp_board, r-1, c) && put_dot(*cp_board, r+1, c)
                        && put_blub(*cp_board, r, c+1) && put_dot(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    copy_board(*cp_board, g); // 为了保证回溯的时候g不被破坏
                    if (!isSolved && put_dot(*cp_board, r-1, c) && put_dot(*cp_board, r+1, c)
                        && put_dot(*cp_board, r, c+1) && put_blub(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    break;
                case 0:
                    if (put_dot(*cp_board, r-1, c) && put_dot(*cp_board, r+1, c)
                        && put_dot(*cp_board, r, c+1) && put_dot(*cp_board, r, c-1))
                        handle = solve_puzzle(p->next, *cp_board);
                    break;
                default:
                    break;
            }
            delete cp_board;
            return handle;
        } else {
            return handle_empty(next_empty(-1, g), g);
        }
    }
    
    vector<vector<int> > solveAkari(vector<vector<int> >& g) {
        n = (int)g.size();
        m = (int)g[0].size();
        g_board.resize(n);
        for (int i = 0; i < n; i++)
            g_board[i].resize(m);
        Barr_list head = makeBarrierList(g);
        isSolved = false;
        solve_puzzle(head, g);
        // 释放内存
        while (head != NULL) {
            Barrier *p = head->next;
            free(head);
            head = p;
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (g_board[i][j] == 6) g_board[i][j] = -2;
        return g_board;
    }
}
using namespace aka;


vector<vector<int> > genVector(string s, int n, int m) {
    vector<vector<int> > res(n, vector<int>(m, 0));
    stringstream ss(s);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ss >> res[i][j];
        }
    }
    return res;
}
int main() {
    vector<vector<int> > game = genVector("-2 -1 -2 3 -2 -1 -2 -2 -1 -2 1 0 -2 -2 \
                                            -2 -2 -2 -2 2 -2 -2 -2 -2 -2 -2 -2 -2 -1 \
                                             -1 -2 -2 -2 -2 -2 -2 -2 -2 1 0 -2 -2 -2 \
                                            0 -2 -1 1 -2 -2 -2 -2 -2 -2 1 -2 -2 3\
                                            -2 -2 1 -2 -2 -1 1 -2 -1 -2 -2 -2 -1 -2\
                                            -1 -2 -2 -2 1 -2 -1 -2 -2 -1 -2 -2 -2 2\                                                                                     
                                            -2 -2 -2 -2 -2 -2 -2 -2 -1 -1 -2 -2 -2 -2\                                           
                                            -2 -2 -2 -2 -1 3 -2 -2 -2 -2 -2 -2 -2 -2 \
                                            1 -2 -2 -2 -1 -2 -2 -1 -2 -1 -2 -2 -2 2 \
                                            -2 -1 -2 -2 -2 -1 -2 -1 -1 -2 -2 -1 -2 -2 \ 
                                            1 -2 -2 -1 -2 -2 -2 -2 -2 -2 -1 1 -2 -1 \                                           
                                            -2 -2 -2 -1 2 -2 -2 -2 -2 -2 -2 -2 -2 -1 \
                                            -1 -2 -2 -2 -2 -2 -2 -2 -2 2 -2 -2 -2 -2 \
                                            -2 -2 -1 -1 -2 -1 -2 -2 -1 -2 -1 -2 -1 -2", 14, 14);

//    vector<vector<int> > game = genVector("2 -2 -2 -2 2 -2 -2 -2 -2 -1\
//                                          -2 -1 -2 -2 -2 -2 -2 -2 -1 -2\
//                                          -2 -2 -2 2 -2 -1 -2 -2 -2 -2\
//                                          -2 -2 -2 -2 -2 -2 -2 2 -2 -2\
//                                          -2 -2 2 -2 -2 -2 -2 -2 -2 1\
//                                          -1 -2 -2 -2 -2 -2 -2 0 -2 -2\
//                                          -2 -2 2 -2 -2 -2 -2 -2 -2 -2\
//                                          -2 -2 -2 -2 1 -2 -1 -2 -2 -2\
//                                          -2 -1 -2 -2 -2 -2 -2 -2 1 -2\
//                                          1 -2 -2 -2 -2 1 -2 -2 -2 0", 10, 10);

//    vector<vector<int> > game = genVector("-2 -2 -2 -2 -1 -2 -2\
//                                          -2 2 -2 -2 -2 4 -2\
//                                          -1 -2 -2 -1 -2 -2 -2\
//                                          -2 -2 2 -1 1 -2 -2\
//                                          -2 -2 -2 -1 -2 -2 1\
//                                          -2 2 -2 -2 -2 -1 -2\
//                                          -2 -2 2 -2 -2 -2 -2", 7, 7);

//    vector<vector<int> > game = genVector("2 5 -2 -2 2 5 -2 -2 -2 -1\
//                                          5 -1 -2 -2 5 -2 -2 -2 -1 5\
//                                          -2 -2 5 2 -2 -1 -2 5 -2 -2\
//                                          -2 -2 -2 5 -2 -2 -2 2 5 -2\
//                                          -2 5 2 -2 -2 -2 5 -2 -2 1\
//                                          -1 -2 5 -2 -2 -2 -2 0 -2 5\
//                                          -2 -2 2 -2 -2 -2 -2 -2 -2 -2\
//                                          -2 -2 5 -2 1 5 -1 -2 -2 -2\
//                                          5 -1 -2 -2 -2 -2 -2 5 1 -2\
//                                          1 -2 -2 -2 5 1 5 -2 -2 0", 10, 10);

    long start,end;
    double duration;
    start = clock();
  //  for (int i = 0; i < 14; i++){
        game = aka::solveAkari(game);
  //  }
    end = clock();
    duration  =(end - start) / CLOCKS_PER_SEC;
    printf("Time duration: %.6lfs\n", duration);
    printG(game);


    return 0;
}

