#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <tuple>
#include <string>
#include<random>
#include <climits>

using namespace std;

tuple<int, int> find_match(vector<vector<int>> board, int match_length){
    int x_matches = 0;
    int o_mathces = 0;
    for(int i = 0 ; i < 6 ; i ++){
        for (int j = 0 ; j < 4 ; j ++){
            bool match = true;
            vector<int> next_four(3, 0);
            for (int k = 0 ; k < 4 ; k ++){
                next_four[board[i][j + k]]++;
            }
            if(next_four[1] != 0 && next_four[2] != 0){
                //both x and o in the next four. no match
                match = false;
            }
            else{
                if(next_four[1] != 0){
                    match = true;
                    x_matches++;
                }
                else if(next_four[2] != 0){
                    match = true;
                    o_mathces++;
                }
                else{
                    match = false;
                }
            }
        }
    }
    for(int i = 0 ; i < 3 ; i ++){
        for (int j = 0 ; j < 7 ; j ++){
            bool match = true;
            vector<int> next_four(3, 0);
            for (int k = 0 ; k < 4 ; k ++){
                next_four[board[i + k][j]]++;
            }
            if(next_four[1] != 0 && next_four[2] != 0){
                //both x and o in the next four. no match
                match = false;
            }
            else{
                if(next_four[1] != 0){
                    match = true;
                    x_matches++;
                }
                else if(next_four[2] != 0){
                    match = true;
                    o_mathces++;
                }
                else{
                    match = false;
                }
            }
        }
    }
    for(int i = 0 ; i < 3 ; i ++){
        for (int j = 0 ; j < 4 ; j ++){
            bool match = true;
            vector<int> next_four(3, 0);
            for (int k = 0 ; k < 4 ; k ++){
                next_four[board[i + k][j + k]]++;
            }
            if(next_four[1] != 0 && next_four[2] != 0){
                //both x and o in the next four. no match
                match = false;
            }
            else{
                if(next_four[1] != 0){
                    match = true;
                    x_matches++;
                }
                else if(next_four[2] != 0){
                    match = true;
                    o_mathces++;
                }
                else{
                    match = false;
                }
            }
        }
    }
    for(int i = 0 ; i < 3 ; i ++){
        for (int j = 6 ; j > 2 ; j --){
            bool match = true;
            vector<int> next_four(3, 0);
            for (int k = 0 ; k < 4 ; k ++){
                next_four[board[i + k][j - k]]++;
            }
            if(next_four[1] != 0 && next_four[2] != 0){
                //both x and o in the next four. no match
                match = false;
            }
            else{
                if(next_four[1] != 0){
                    match = true;
                    x_matches++;
                }
                else if(next_four[2] != 0){
                    match = true;
                    o_mathces++;
                }
                else{
                    match = false;
                }
            }
        }
    }
    return make_tuple(x_matches, o_mathces);
}

int gameover(vector<vector<int>> board){
    for(int i = 0 ; i < 6 ; i ++){
        for (int j = 0 ; j < 4 ; j ++){
            bool match = true;
            for (int k = 0 ; k < 4 ; k ++){
                if (board[i][j]!=board[i][j + k] || board[i][j] == 0 || board[i][j + k] == 0){
                    match=false;
                    break;
                }
            }
            if (match==true){
                if(board[i][j] == 1 ){
                    return 10;
                }
                else if(board[i][j] == 2){
                    return -10;
                }
            }

        }
    }
    for(int i = 0 ; i < 3 ; i ++){
        for (int j = 0 ; j < 7 ; j ++){
            bool match = true;
            for (int k = 0 ; k < 4 ; k ++){
                if (board[i][j] != board[i + k][j] || board[i][j] == 0 || board[i+k][j] == 0){
                    match = false;
                    break;
                }
            }
            if (match == true){
                if(board[i][j] == 1 ){
                    return 10;
                }
                else if(board[i][j] == 2){
                    return -10;
                }
            }
        }
    }
    for(int i = 0 ; i < 3 ; i ++){
        for (int j = 0 ; j < 4 ; j ++){
            bool match = true;
            for (int k = 0 ; k < 4 ; k ++){
                if (board[i][j] != board[i + k][j + k] || board[i][j] == 0 || board[i + k][j + k] == 0){
                    match = false;
                    break;
                }
            }
            if (match == true){
                if(board[i][j] == 1){
                    return 10;
                }
                else if(board[i][j] == 2){
                    return -10;
                }
            }
        }
    }
    for(int i = 0 ; i < 3 ; i ++){
        for (int j = 6 ; j > 2 ; j --){
            bool match = true;
            for (int k = 0 ; k < 4 ; k ++){
                if (board[i][j]!=board[i + k][j - k] || board[i][j] == 0 || board[i+k][j-k] == 0){
                    match = false;
                    break;
                }
            }
            if (match == true){
                if(board[i][j] == 1){
                    return 10;
                }
                else if(board[i][j] == 2){
                    return -10;
                }
            }
        }
    }
    return 0;
}

int evaluate(vector<vector<int>> board){
    tuple<int, int> two_matches = find_match(board, 2);
    tuple<int, int> three_matches = find_match(board, 3);

    int two_x_matches = get<0>(two_matches);
    int two_o_matches = get<1>(two_matches);

    int three_x_matches = get<0>(three_matches);
    int three_o_matches = get<1>(three_matches);

    int score = 0;

    score += two_x_matches;
    score -= two_o_matches;
    score += three_x_matches * 2;
    score -= three_o_matches * 2;

    if(score < -9) score = -9;
    if(score > 9) score = 9;

    return score;
}

int isGameOver(vector<vector<int>> board){
      if(gameover(board) == 10 || gameover(board) == -10){
            return 1;
      }
      return 0;
}

vector<string> generate_moves(vector<vector<int>> board){
    int x = 0 , o = 0 , slot = 0, n = 7;
    for(int i = 0 ; i < 6 ; i ++){
        for(int j = 0 ; j < n ; j ++){
            if(board[i][j] == 1){
                x ++;
            }
            if (board[i][j] == 2){
                o ++ ;
            }
        }
    }
    vector<string> vstring;
    string turn = "";
    if(x>o){
        turn = "O";
    }
    else{
        turn = "X";
    }
    for(int j = 0; j < 7 ; j ++){
        if(board[5][j] == 0){
            vstring.push_back(turn + to_string(j));
        }
    }
    return vstring;
}

vector<vector<int>> apply_moves(vector<vector<int>> board, string m ){
    vector<vector<int>> temp_board(6 , vector<int>(7 , 0));
for (int i = 0 ; i < 6 ; i ++){
    for (int j = 0 ; j < 7 ; j ++){
        temp_board[i][j] = board[i][j];
    }
}

char a = m[0];
int b = m[1] - '0';
    for (int i = 0 ; i < 6 ; i ++){
        if (board[i][b] == 0){
            if(a == 'X'){
                temp_board[i][b] = 1;
            }
            if(a == 'O'){
                temp_board[i][b] = 2;
            }
            break;
        }
    }
    return temp_board;
}

int minmax_(vector<vector<int>> board, int player, int depth, int alpha, int beta) {
    int score;
    if (depth == 0 || isGameOver(board) == 1) {
        return gameover(board);
    }

    if (player == 1) {
        score = -10;
        vector<string> moves = generate_moves(board);
        for (int i = 0; i < moves.size(); i++) {
            vector<vector<int>> newboard = apply_moves(board, moves[i]);
            int tempscore = minmax_(newboard, 2, depth - 1, alpha, beta);
            score = max(score, tempscore);
            alpha = max(alpha, score);
            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
        return score;
    }

    if (player == 2) {
        score = 10;
        vector<string> moves = generate_moves(board);
        for (int i = 0; i < moves.size(); i++) {
            vector<vector<int>> newboard = apply_moves(board, moves[i]);
            int tempscore = minmax_(newboard, 1, depth - 1, alpha, beta);
            score = min(score, tempscore);
            beta = min(beta, score);
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }
        return score;
    }
    return score;
}

string getbestmoves(vector<vector<int>> board , int maximize , int depth){
    vector<string> moves = generate_moves(board);

    string bestMove = "";
    int score;
    if(maximize == 1){
        score = -10;
    }
    else{
        score = 10;
    }
    for(int i = 0 ; i < moves.size() ; i++){
        vector<vector<int>> temp_board = apply_moves(board , moves[i]);
        int temp_score = 0;
        if(maximize == 1){
            temp_score = minmax_(temp_board , 2 , depth - 1, INT_MIN, INT_MAX);
            if(temp_score > score){
                score = temp_score;
                bestMove = moves[i];
            }
        }
        else{
            temp_score = minmax_(temp_board , 1 , depth - 1, INT_MIN, INT_MAX);
            if(temp_score < score){
                score = temp_score;
                bestMove = moves[i];
            }
        }
    }
    return bestMove;
}

void print_board(vector<vector<int>> board){
    for(int i = board.size() - 1 ; i >= 0 ; i--){
        for(int j = 0 ; j < board[i].size() ; j ++){
            if(board[i][j] == 1){
                cout << "X ";
            }
            else if(board[i][j] == 2){
                cout << "O ";
            }
            else{
                cout << "_ ";
            }
        }
        cout << endl;
    }
}

void play_with_human(){
    vector<vector<int>> board(6 , vector<int>(7,0));
     while(isGameOver(board) == 0){
        int move_;
        cout << "Enter you move: ";
        cin >> move_ ;
        string m = "X" + to_string(move_);
        board = apply_moves(board,m);
        print_board(board);
        string aimoves = getbestmoves(board , 2 , 3);
        cout << "AI Move: " << aimoves << endl;
        board = apply_moves(board , aimoves);
        print_board(board);
     }
}

void test_evaluate(){
    vector<vector<int>> board(6 , vector<int>(7,0));
    board[0][0] = 2;
    board[0][1] = 2;
    board[0][2] = 2;

    print_board(board);
    cout << evaluate(board);
}

int main()
{
    std::srand(std::time(0));
    play_with_human();
    return 0;
}
