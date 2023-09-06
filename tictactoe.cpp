#include <iostream>
#define pis pair<int, string>
using namespace std;
string colorify(string i, string color){
    string mid = "";
    string k = "\033[";
    if(color == "red"){mid = "31;1m";}
    if(color == "gray"){mid ="90;1m";}
    if(color == "blue"){mid = "34;1m";}
    return "\033["+mid+i+"\033[0m";
}
pis checkhorizontal(string arr[]){
    pis j = make_pair(false, "-");
    for(int i = 0; i < 3; i++){
        if(arr[3*i] == arr[3*i+1] && arr[3*i] == arr[3*i+2]){
            j.first = true;
            j.second = arr[3*i];
            break;
        }
    }
    return j;
}
pis checkvertical(string arr[]){
    pis j = make_pair(false, "-");
    for(int i = 0; i < 3; i++){
        if(arr[i] == arr[i+3] && arr[i] == arr[i+6]){
            j.first = true;
            j.second = arr[i];
            break;
        }
    }
    return j;
}
pis checkdiagonal(string arr[]){
    pis j = make_pair(false, "-");
    if((arr[0] == arr[4] && arr[0] == arr[8])||(arr[2] == arr[4] && arr[2] == arr[6])){
        j.first = true;
        j.second = arr[4];
    }
    return j;
}
bool gameover(string arr[]){
    pis horiz = checkhorizontal(arr);
    pis vert = checkvertical(arr);
    pis diag = checkdiagonal(arr);
    string player1 = colorify("O", "blue");
    string winner = "";
    if (horiz.second!="-"){
        winner = horiz.second;
    }
    if (vert.second!="-"){
        winner = vert.second;
    }
    if (diag.second!="-"){
        winner = diag.second;
    }
    if(winner!=""){
        if(winner == player1){
            cout << "Player 1 is the winner";
        }
        else{
            cout << "Player 2 is the winner";
        }
    }
    return(horiz.first||vert.first||diag.first);
}
void printboard(string arr[]){
    string board[7] = {"┏━━━━━┳━━━━━┳━━━━━┓", "", "┣━━━━━╋━━━━━╋━━━━━┫", "", "┣━━━━━╋━━━━━╋━━━━━┫", "", "┗━━━━━┻━━━━━┻━━━━━┛"};
    for(int i = 0; i < 3; i++){
        board[1+2*i]+=("┃  "+arr[3*i]+"  ┃  "+arr[3*i+1]+"  ┃  "+arr[3*i+2]+"  ┃");
    }
    system("clear");
    cout << "Current board state:\n";
    for(string a: board){
        cout << a << "\n";
    }
}
void initializearr(string arr[]){
    for(int i = 0; i < 9; i++){
        arr[i] = colorify(to_string(i+1), "gray");
    }
}
void playgame(string arr[]){
    char input; int move; bool used[9] = {}; bool turn = true; int movecount = 0;
    while(!(gameover(arr)) && movecount<9){
        if(turn){
            cout << "Player 1 move: ";
        }
        else{
            cout << "Player 2 move: ";
        }
        cin >> input;
        move = input-'0';
        if (0<move && move<10 && !(used[move-1])){
            if (turn){
                arr[move-1] = colorify("O", "blue");
            }
            else{
                arr[move-1] = colorify("X", "red");
            }
            turn = !turn;
            movecount++;
            used[move-1] = true;
            printboard(arr);
            if (movecount == 9){
                cout << "Tie";
            }
        }
        else{
            cout << "Not a valid move" << "\n";
        }
    }
}
int main(){
    string arr[9];
    initializearr(arr);
    printboard(arr);
    playgame(arr);
    return 0;
}