#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "IGameListener.h"
#include "Game.h"
#include "InvalidMovingPatternException.h"

class MockListener : public IGameListener
{
public:
	MOCK_METHOD(void, OnMoveMade, (Position startPos, Position endPos, PositionList prevPossibleMoves));
	MOCK_METHOD(void, OnPawnUpgrade, ());
	MOCK_METHOD(void, OnGameOver, (EGameResult result));
};


class MockGameListener : public testing::Test
{
	void SetUp() override
	{
		mock = std::make_shared<MockListener>();
	}

protected:
	std::shared_ptr<MockListener> mock;
};


using ::testing::_;
using ::testing::AtLeast;


TEST(ListenreMockTest, OnMoveMade)
{
	auto mock = std::make_shared<MockListener>();

	Game g;
	g.AddListener(mock);

	EXPECT_CALL(*mock, OnMoveMade).Times(AtLeast(2));

	g.MakeMove(Position(6, 3), Position(4, 3));
	g.MakeMove(Position(1, 3), Position(3, 3));

	
	EXPECT_THROW(g.MakeMove(Position(4, 3), Position(5, 3)), InvalidMovingPatternException);

}

TEST_F(MockGameListener, OnPawnUpgrade)
{

	ConfigMatrix m = {
				/*0    1    2    3    4    5    6    7*/
		/*0*/	{'-', 'K', '-', '-', '-', '-', '-', '-'},
		/*1*/	{'-', '-', '-', 'p', '-', '-', '-', '-'},
		/*2*/	{'-', '-', 'b', '-', '-', '-', '-', '-'},
		/*3*/	{'-', '-', '-', '-', 'n', '-', 'r', '-'},
		/*4*/	{'-', '-', '-', 'k', '-', '-', '-', '-'},
		/*5*/	{'-', '-', '-', '-', '-', '-', '-', '-'},
		/*6*/	{'-', '-', 'B', '-', '-', 'P', '-', '-'},
		/*7*/	{'-', '-', '-', '-', '-', '-', '-', '-'}
	};
	
	Game g(0, EGameState::Playing, m);
	g.AddListener(mock);

	EXPECT_CALL(*mock, OnPawnUpgrade);

	g.MakeMove(Position(1, 3), Position(0, 3));
}