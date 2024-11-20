#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Function to print the 2D grid
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows;
    string encrypted_message;

    cin >> rows;
    cin >> encrypted_message;

    int cols = encrypted_message.size();

    vector<vector<int>> diagonal(rows, vector<int>(cols, 0));

    // remake diagonal
    bool down = true;
    int currRow = 0;
    int currCol = 0;

    for (int i = 0; i < cols; i++) {
        diagonal[currRow][currCol] = 1;
        
        if (!down && currRow == 0) {
            down = true;
        } else if ((currRow + 1) == rows) {
            // time to go up
            down = false;
        }   

        if (down) {
            currRow++;
        } else if (!down) {
            currRow--;
        }

        currCol++;
    }

    vector<vector<char>> crypted_message(rows, vector<char>(cols, ' '));

    currRow = 0;
    for (int i = 0; i < cols; i++) {
        bool charPlaced = false;
        for (int col = 0; col < cols; col++) {
            if (diagonal[currRow][col] == 1) {
                diagonal[currRow][col] = 0;
                crypted_message[currRow][col] = encrypted_message[i];
                charPlaced = true;
                break;
            }
        }
        if (!charPlaced) {
            currRow++;
            i--;
        }
    }

    // now read the thing
    currRow = 0;
    bool printedSmth = false;
    for (int j = 0; j < cols; j++) {
        for (int row = 0; row < rows; row++) {
            if (crypted_message[row][j] != ' ') {
                cout << crypted_message[row][j];
                printedSmth = true;
                break;
            }
        }
    }

    if (printedSmth) {
        cout << endl;
    }

    return 0;
}
