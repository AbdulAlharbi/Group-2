/*
Name: Allison Kameda, 2001941679, CS 202-1004, ASSIGNMENT 5
Description: Allows the user to play Miniature Chess
Input: Takes board coordinates
Output: Updates board with moved pieces until a winner is found
ChatGPT: https://chatgpt.com/share/67c2a692-a2a8-8012-a767-07dd1c8d047e
*/

/*Sadly this file does not function without the associated header files*/
#include <iostream>
#include <string>
#include "chessPiece.h"
#include "queenType.h"
#include "rookType.h"
#include "bishopType.h"
#include "knightType.h"

#define RESET "\033[0m"
#define RED "\033[31m"

void outputBoard(chessPiece***);
void clearBoard(chessPiece***);

int main()
{
	chessPiece *** board;
	
	board = new chessPiece**[8];

	for (int i = 0; i < 8; i++)
		board[i] = new chessPiece*[8];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = nullptr;


	//place the black chess pieces onto
	//the board
	board[0][3] = new knightType(false);
	board[1][0] = new rookType(false);
	board[1][2] = new bishopType(false);
	board[1][3] = new queenType(false);
	board[1][4] = new bishopType(false);
	board[1][6] = new rookType(false);
	board[2][3] = new knightType(false);

	//place the red chess pieces onto
	//the board
	board[5][4] = new knightType(true);
	board[6][1] = new rookType(true);
	board[6][3] = new bishopType(true);
	board[6][4] = new queenType(true);
	board[6][5] = new bishopType(true);
	board[6][7] = new rookType(true);
	board[7][4] = new knightType(true);	

	outputBoard(board);

	char row1, row2;
	int col1, col2;

	int redPieces = 7;
	int blackPieces = 7;

    /*Begin ChatGPT suggestions*/
    bool turn = true;  // True = Red, False = Black
    while (redPieces > 0 && blackPieces > 0) {
        playerTurn(turn, turn ? blackPieces : redPieces, board);
        outputBoard(board);

        if (blackPieces == 0) {
            std::cout << "\nRed wins!" << std::endl;
            break;
        }
        if (redPieces == 0) {
            std::cout << "\nBlack wins!" << std::endl;
            break;
        }
        turn = !turn;  // Alternate turns
    }

    clearBoard(board);
}

void playerTurn(bool isRed, int &opponentPieces, Piece* board[8][8]) {
    char row1, row2;
    int col1, col2;
    bool validMove = false;

    while (!validMove) {
        std::string input;
        std::cout << "\nEnter starting coordinates (" << (isRed ? "Red" : "Black") << " Turn): ";
        std::getline(std::cin, input);

        row1 = input[0];
        col1 = stoi(input.substr(1,2)) - 1;
        int rowInt1 = row1 - 'A';

        if (board[rowInt1][col1] == nullptr || board[rowInt1][col1]->getPlayerType() != isRed) {
            std::cout << "Invalid piece selected." << std::endl;
            continue;
        }

        std::cout << "Enter ending coordinates: ";
        std::getline(std::cin, input);
        row2 = input[0];
        col2 = stoi(input.substr(1,2)) - 1;
        int rowInt2 = row2 - 'A';

        if (!board[rowInt1][col1]->move(row1, col1, row2, col2, board)) {
            std::cout << "Invalid move!" << std::endl;
            continue;
        }

        if (board[rowInt2][col2] != nullptr) {
            delete board[rowInt2][col2];
            board[rowInt2][col2] = nullptr;
            opponentPieces--;
        }

        board[rowInt2][col2] = board[rowInt1][col1];
        board[rowInt1][col1] = nullptr;
        validMove = true;
    }
}
