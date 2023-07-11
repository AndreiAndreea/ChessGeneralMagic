#pragma once
class Piece
{
private:
	bool white = false;
public:
	Piece(bool white);
	bool isWhite();
	void setColor(bool white);
	virtual bool canMove()=0;
};