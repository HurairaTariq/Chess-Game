#include <iostream>
#include<dos.h>
#include<time.h>
#include <thread>
#include <chrono>
using namespace std;
class Piece
{
public:
	Piece(char color1) : Color(color1) {}
	~Piece() {}
	virtual char getpiece() = 0;
	char getcolor() {
		return Color;
	}
	bool Check_Valid_Move(int PreRow, int PreCol, int NextRow, int NextCol, Piece* ABoard[8][8]) {
		Piece* Destination = ABoard[NextRow][NextCol];
		if ((Destination == 0) || (Color != Destination->getcolor())) {
			return Check_Valid_Boxes(PreRow, PreCol, NextRow, NextCol, ABoard);
		}
		return false;
	}
private:
	virtual bool Check_Valid_Boxes(int PreRow, int PreCol, int NextRow, int NextCol, Piece* ABoard[8][8]) = 0;
	char Color;
};

class Pawn : public Piece
{
public:
	Pawn(char color1) : Piece(color1) {}
	~Pawn() {}
private:
	virtual char getpiece() {
		return 'p';
	}
	bool Check_Valid_Boxes(int PreRow, int PreCol, int NextRow, int NextCol, Piece* ABoard[8][8]) {
		Piece* Destination = ABoard[NextRow][NextCol];
		if (Destination == 0) {

			if (PreCol == NextCol) {                        // destination square is unoccupied
				if (getcolor() == 'w') {
					if (NextRow == PreRow + 1) {
						return true;
					}
				}
				else {
					if (NextRow == PreRow - 1) {
						return true;
					}
				}
			}
		}
		else {

			if ((PreCol == NextCol + 1) || (PreCol == NextCol - 1)) 
{                       // dest holds piece of opposite color
				if (getcolor() == 'w') {
					if (NextRow == PreRow + 1) {
						return true;
					}
				}
				else {
					if (NextRow == PreRow - 1) {
						return true;
					}
				}
			}
		}
		return false;
	}
};

class Knight : public Piece
{
public:
	Knight(char color1) : Piece(color1) {}
	~Knight() {}
private:
	virtual char getpiece() {
		return 'n';
	}
	bool Check_Valid_Boxes(int PreRow, int PreCol, int NextRow, int NextCol, Piece* ABoard[8][8]) {

		if ((PreCol == NextCol + 1) || (PreCol == NextCol - 1)) {									// destination square is unoccupied or occupied by opposite color
			if ((PreRow == NextRow + 2) || (PreRow == NextRow - 2)) {
				return true;
			}
		}
		if ((PreCol == NextCol + 2) || (PreCol == NextCol - 2)) {
			if ((PreRow == NextRow + 1) || (PreRow == NextRow - 1)) {
				return true;
			}
		}
		return false;
	}
};

class Bishop : public Piece
{
public:
	Bishop(char color1) : Piece(color1) {}
	~Bishop() {}
private:
	virtual char getpiece() {
		return 'b';
	}
	bool Check_Valid_Boxes(int PreRow, int PreCol, int NextRow, int NextCol, Piece* ABoard[8][8]) {
		if ((NextCol - PreCol == NextRow - PreRow) || (NextCol - PreCol == PreRow - NextRow)) {

			int SetRow = (NextRow - PreRow > 0) ? 1 : -1;								// make sure that all invervening squares are empty
			int SetCol = (NextCol - PreCol > 0) ? 1 : -1;
			int CheckRow;
			int CheckCol;
			for (CheckRow = PreRow + SetRow, CheckCol = PreCol + SetCol;
				CheckRow != NextRow;
				CheckRow = CheckRow + SetRow, CheckCol = CheckCol + SetCol)
			{
				if (ABoard[CheckRow][CheckCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class Rook : public Piece
{
public:
	Rook(char color1) : Piece(color1) {}
	~Rook() {}
private:
	virtual char getpiece() {
		return 'r';
	}
	bool Check_Valid_Boxes(int PreRow, int PreCol, int NextRow, int NextCol, Piece* ABoard[8][8]) {
		if (PreRow == NextRow) {

			int SetCol = (NextCol - PreCol > 0) ? 1 : -1;													// make sure that all invervening squares are empty
			for (int CheckCol = PreCol + SetCol; CheckCol != NextCol; CheckCol = CheckCol + SetCol) {
				if (ABoard[PreRow][CheckCol] != 0) {
					return false;
				}
			}
			return true;
		}
		else if (NextCol == PreCol) {

			int SetRow = (NextRow - PreRow > 0) ? 1 : -1;												// make sure that all invervening squares are empty
			for (int CheckRow = PreRow + SetRow; CheckRow != NextRow; CheckRow = CheckRow + SetRow) {
				if (ABoard[CheckRow][PreCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class Queen : public Piece
{
public:
	Queen(char color1) : Piece(color1) {}
	~Queen() {}
private:
	virtual char getpiece() {
		return 'q';
	}
	bool Check_Valid_Boxes(int PreRow, int PreCol, int NextRow, int NextCol, Piece* ABoard[8][8]) {
		if (PreRow == NextRow) {

			int SetCol = (NextCol - PreCol > 0) ? 1 : -1;														// make sure that all invervening squares are empty
			for (int CheckCol = PreCol + SetCol; CheckCol != NextCol; CheckCol = CheckCol + SetCol) {
				if (ABoard[PreRow][CheckCol] != 0) {
					return false;
				}
			}
			return true;
		}
		else if (NextCol == PreCol) {

			int SetRow = (NextRow - PreRow > 0) ? 1 : -1;															// make sure that all invervening squares are empty
			for (int CheckRow = PreRow + SetRow; CheckRow != NextRow; CheckRow = CheckRow + SetRow) {
				if (ABoard[CheckRow][PreCol] != 0) {
					return false;
				}
			}
			return true;
		}
		else if ((NextCol - PreCol == NextRow - PreRow) || (NextCol - PreCol == PreRow - NextRow)) {

			int SetRow = (NextRow - PreRow > 0) ? 1 : -1;												// make sure that all invervening squares are empty
			int SetCol = (NextCol - PreCol > 0) ? 1 : -1;
			int CheckRow;
			int CheckCol;
			for (CheckRow = PreRow + SetRow, CheckCol = PreCol + SetCol;
				CheckRow != NextRow;
				CheckRow = CheckRow + SetRow, CheckCol = CheckCol + SetCol)
			{
				if (ABoard[CheckRow][CheckCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class King : public Piece
{
public:
	King(char color1) : Piece(color1) {}
	~King() {}
private:
	virtual char getpiece() {
		return 'k';
	}
	bool Check_Valid_Boxes(int PreRow, int PreCol, int NextRow, int NextCol, Piece* ABoard[8][8]) {
		int rowdelta = NextRow - PreRow;
		int coldelta = NextCol - PreCol;
		if (((rowdelta >= -1) && (rowdelta <= 1)) &&
			((coldelta >= -1) && (coldelta <= 1)))
		{
			return true;
		}
		return false;
	}
};

class Board
{
public:
	Piece* Board_1[8][8];
	Board() {
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				Board_1[row][col] = 0;
			}
		}

		for (int col = 0; col < 8; ++col) {									// allocate and place black pieces
			Board_1[6][col] = new Pawn('b');
		}
		Board_1[7][0] = new Rook('b');
		Board_1[7][1] = new Knight('b');
		Board_1[7][2] = new Bishop('b');
		Board_1[7][3] = new King('b');
		Board_1[7][4] = new Queen('b');
		Board_1[7][5] = new Bishop('b');
		Board_1[7][6] = new Knight('b');
		Board_1[7][7] = new Rook('b');

		for (int col = 0; col < 8; ++col) {												// allocate and place white pieces
			Board_1[1][col] = new Pawn('w');
		}
		Board_1[0][0] = new Rook('w');
		Board_1[0][1] = new Knight('w');
		Board_1[0][2] = new Bishop('w');
		Board_1[0][3] = new King('w');
		Board_1[0][4] = new Queen('w');
		Board_1[0][5] = new Bishop('w');
		Board_1[0][6] = new Knight('w');
		Board_1[0][7] = new Rook('w');
	}
	~Board() {
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				delete Board_1[row][col];
				Board_1[row][col] = 0;
			}
		}
	}

	void print() {
		const int widht = 4;
		const int height = 3;
		for (int row = 0; row < 8 * height; ++row) {
			int SqRow = row / height;

			if (row % 3 == 1) {											// print side border with numbering
				cout << '-' << (char)('1' + 7 - SqRow) << '-';
			}
			else {
				cout << "---";
			}

			for (int col = 0; col < 8 * widht; ++col) {													// print the chess board
				int SqCol = col / widht;
				if (((row % 3) == 1) && ((col % 4) == 1 || (col % 4) == 2) && Board_1[7 - SqRow][SqCol] != 0) {
					if ((col % 4) == 1) {
						cout << Board_1[7 - SqRow][SqCol]->getcolor();
					}
					else {
						cout << Board_1[7 - SqRow][SqCol]->getpiece();
					}
				}
				else {
					if ((SqRow + SqCol) % 2 == 1) {
						cout << '*';
					}
					else {
						cout << ' ';
					}
				}
			}
			cout << endl;
		}

		for (int row = 0; row < height; ++row) {											// print the bottom border with numbers
			if (row % 3 == 1) {
				cout << "---";
				for (int col = 0; col < 8 * widht; ++col) {
					int SqCol = col / widht;
					if ((col % 4) == 1) {
						cout << (SqCol + 1);
					}
					else {
						cout << '-';
					}
				}
				cout << endl;
			}
			else {
				for (int col = 1; col < 9 * widht; ++col) {
					cout << '-';
				}
				cout << endl;
			}
		}
	}

	bool isincheck(char color1) {

		int KingRow = 0;																// find the king
		int KingCol = 0;
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (Board_1[row][col] != 0) {
					if (Board_1[row][col]->getcolor() == color1) {
						if (Board_1[row][col]->getpiece() == 'k') {
							KingRow = row;
							KingCol = col;
						}
					}
				}
			}
		}

		for (int row = 0; row < 8; ++row) {															// run through the opponent's pieces and see if any can take the king
			for (int col = 0; col < 8; ++col) {
				if (Board_1[row][col] != 0) {
					if (Board_1[row][col]->getcolor() != color1) {
						if (Board_1[row][col]->Check_Valid_Move(row, col, KingRow, KingCol, Board_1)) {
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	bool Can_Move(char color1) {

		for (int row = 0; row < 8; ++row) {										// run through all pieces
			for (int col = 0; col < 8; ++col) {
				if (Board_1[row][col] != 0) {

					if (Board_1[row][col]->getcolor() == color1) {								// if it is a piece of the current player, see if it has a legal move
						for (int Mrow = 0; Mrow < 8; ++Mrow) {
							for (int Mcol = 0; Mcol < 8; ++Mcol) {
								if (Board_1[row][col]->Check_Valid_Move(row, col, Mrow, Mcol, Board_1)) {

									Piece* qptemp = Board_1[Mrow][Mcol];                               	// make move and check whether king is in check
									Board_1[Mrow][Mcol] = Board_1[row][col];
									Board_1[row][col] = 0;
									bool PieceCanMove = !isincheck(color1);
									// undo the move
									Board_1[row][col] = Board_1[Mrow][Mcol];
									Board_1[Mrow][Mcol] = qptemp;
									if (PieceCanMove) {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}


};

class Chess
{
private:
	Board GameBoard;
	char Turn;
public:
	Chess() : Turn('w') {}
	~Chess() {}

	void start() {
		do {
			getnextmove(GameBoard.Board_1);
			Alternate_Turn();
		} while (!isgameover());
		GameBoard.print();
	}

	void getnextmove(Piece* ABoard[8][8]) {
		using namespace std;
		bool bvalidmove = false;
		do {
			system("cls");
			GameBoard.print();


			cout << Turn << "'s move: ";							// get input and convert to coordinates
			int istartmove;
			cin >> istartmove;
			int RowStart = (istartmove / 10) - 1;
			int ColStart = (istartmove % 10) - 1;

			cout << "to: ";
			int iendmove;
			cin >> iendmove;
			int EndRow = (iendmove / 10) - 1;
			int EndCol = (iendmove % 10) - 1;


			if ((RowStart >= 0 && RowStart <= 7) &&          // check that the indices are in range
				// and that the source and destination are different
				(ColStart >= 0 && ColStart <= 7) &&
				(EndRow >= 0 && EndRow <= 7) &&
				(EndCol >= 0 && EndCol <= 7)) {

				Piece* qpcurrpiece = ABoard[RowStart][ColStart];                               // additional checks in here

				if ((qpcurrpiece != 0) && (qpcurrpiece->getcolor() == Turn)) {													// check that the piece is the correct color

					if (qpcurrpiece->Check_Valid_Move(RowStart, ColStart, EndRow, EndCol, ABoard)) {								// check that the destination is a valid destination

						Piece* qptemp = ABoard[EndRow][EndCol];									// make the move
						ABoard[EndRow][EndCol] = ABoard[RowStart][ColStart];
						ABoard[RowStart][ColStart] = 0;

						if (!GameBoard.isincheck(Turn)) {												// make sure that the current player is not in check
							delete qptemp;
							bvalidmove = true;
						}
						else {																					// undo the last move
							ABoard[RowStart][ColStart] = ABoard[EndRow][EndCol];
							ABoard[EndRow][EndCol] = qptemp;
						}
					}
				}
			}
			if (!bvalidmove) {
				cout << "invalid move!" << endl;
			}
		} while (!bvalidmove);
	}

	void Alternate_Turn() {
		Turn = (Turn == 'w') ? 'b' : 'w';
	}

	bool isgameover() {

		bool PieceCanMove(false);                        // check that the current player can move
		                                               // if not, we have a CHECK or checkmate
		PieceCanMove = GameBoard.Can_Move(Turn);
		if (!PieceCanMove) {
			if (GameBoard.isincheck(Turn)) {
				Alternate_Turn();
				cout << "!!!!!!!!CHECKMATE!!!!!!!!!! " << Turn << " wins!" << endl;
			}
			else{
				cout << "CHECK!!!!!!!!!!!!!!" << endl;
			}
		}
		return !PieceCanMove;
	}

};

int main() {
	cout << "....................CHESS........................ " << endl;
	cout << "Developed BY 'ZAID' , HAIDER,  'HURAIRA'  " << endl;
	cout << "LOADING.........." << endl;
	int t = 100;
	for (int i = 1; i <= 50; i++){
		this_thread::sleep_for(chrono::milliseconds(t));
		cout << "|";
		if (t == 50){
			t += 50;
		}
		if (t == 100){
			t -= 25;
		}
		if (i == 50){
			cout << endl;
			cout << "Loading Completed.." << endl;
			this_thread::sleep_for(chrono::milliseconds(3000));

		}
	}
	Chess game;
	game.start();
	system("pause");
	return 0;
}