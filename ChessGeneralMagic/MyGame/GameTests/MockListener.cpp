#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "IGameListener.h"
#include "Game.h"

class MockListener : public IGameListener
{
public:
	MOCK_METHOD(void, OnMoveMade, ());
	MOCK_METHOD(void, OnPawnUpgrade, ());
	MOCK_METHOD(void, OnGameOver, (EGameResult result));
};


TEST(ListenreMockTest, OnMoveMade)
{
	//MockListener mock;

	auto mock = std::make_shared<MockListener>();

	Game g;
	g.AddListener(mock);

	EXPECT_CALL(*mock, OnMoveMade()).Times(2);

	g.MakeMove(Position(6, 3), Position(4, 3));
	g.MakeMove(Position(1, 3), Position(3, 3));


}