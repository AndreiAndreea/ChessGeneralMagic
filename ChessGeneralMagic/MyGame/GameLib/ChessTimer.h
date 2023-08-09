#include <thread>
#include <chrono>
#include <atomic>
#include "EPlayer.h"
#include "TimeInfo.h"

class ChessTimer
{
public:
	ChessTimer();

	void StartTimer();

	void StopTimer();

	void UpdateTurn();

	bool IsTimerRunning();

	TimeInfo GetTimerDuration(EPlayer player) const;

private:
	void TimerThread();
	TimeInfo PlayerCountDown(TimeInfo duration);

private:
	std::thread m_timerThread;

	std::atomic<bool> isTimerRunning;
	std::atomic<int> currentPlayerTurn;

	std::atomic<TimeInfo> whiteTimerDuration;
	std::atomic<TimeInfo> blackTimerDuration;
};
