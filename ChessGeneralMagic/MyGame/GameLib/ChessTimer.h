#include <thread>
#include <chrono>
#include <atomic>
#include "EPlayer.h"
#include "TimeInfo.h"

#include <vector>
#include <functional>
#include <mutex>
#include <memory>


using Callback = std::function<void()>;

class ChessTimer
{
public:
	ChessTimer();

	void StartTimer();
	void StopTimer();
	void PauseTimer();
	void ResumeTimer();

	void SetCallback(Callback cb);
	void NotifyTimer();

	void UpdateTurn();

	bool IsTimerRunning();

	void Reset();

	int GetTimerDuration(EPlayer player) const;

private:
	void TimerThread();

private:
	std::thread m_timerThread;

	std::atomic<bool> isTimerRunning;
	std::atomic<bool> currentPlayerTurn;

	std::atomic<std::chrono::milliseconds> whiteTimerDuration;
	std::atomic<std::chrono::milliseconds> blackTimerDuration;

	Callback notify;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};
