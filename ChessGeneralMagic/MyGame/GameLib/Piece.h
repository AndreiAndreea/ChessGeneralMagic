#pragma once
class Piece
{
private:
	bool white = false;
public:
	Piece();
	bool isWhite();
	void setColor();
	virtual bool canMove()=0;
};

