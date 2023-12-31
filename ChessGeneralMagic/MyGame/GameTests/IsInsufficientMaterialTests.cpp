#include "gtest/gtest.h"

#include "Board.h"

TEST(BoardTest, InsufficientMaterial)
{
	ConfigMatrix m = { 
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'k', '-', '-', '-'}
	
	};

	Board board(m);
	EXPECT_TRUE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial2)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'N', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'k', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_TRUE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial3)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', 'k', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'n', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_TRUE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial4)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', 'B', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'k', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_TRUE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial5)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', 'k', '-'},
	{'-', 'B', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'b', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_TRUE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial6)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', 'k', '-'},
	{'-', 'B', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', 'b', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_FALSE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial7)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', 'k', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'b', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_TRUE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial8)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', 'n', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', 'k', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'b', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_FALSE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial9)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', '-', 'K', '-', 'k'},
	{'-', '-', '-', '-', '-', '-', '-', 'b'},
	{'-', '-', '-', '-', 'p', '-', '-', '-'},
	{'-', '-', '-', '-', 'B', '-', 'p', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_FALSE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial10)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', 'K', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', 'P', '-', '-', '-', '-'},
	{'P', '-', 'P', 'p', 'P', '-', '-', 'P'},
	{'p', '-', 'p', '-', 'p', '-', 'P', 'p'},
	{'-', '-', '-', '-', '-', '-', 'p', '-'},
	{'-', '-', '-', '-', '-', 'k', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_TRUE(board.IsInsufficientMaterial());
}

TEST(BoardTest, InsufficientMaterial11)
{
	ConfigMatrix m = { {
	{'-', '-', '-', '-', '-', 'K', '-', 'k'},
	{'-', '-', '-', '-', '-', '-', '-', 'b'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'B', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'}
	}
	};

	Board board(m);
	EXPECT_FALSE(board.IsInsufficientMaterial());
}