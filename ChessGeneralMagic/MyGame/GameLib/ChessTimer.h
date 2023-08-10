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
	~ChessTimer();

	void StartTimer();
	void StopTimer();
	void PauseTimer();
	void ResumeTimer();

	void SetCallbackNotifyUI(Callback cb);
	void SetCallbackNotifyGameOver(Callback cb);
	void NotifyTimer();
	void NotifyGameOver();

	void UpdateTurn();

	bool IsTimerRunning() const;

	void Reset();

	int GetTimerDuration(EPlayer player) const;

private:
	bool IsTimeOut() const;
	void TimerThread();

private:
	std::thread m_timerThread;

	std::atomic<bool> isTimerRunning;
	std::atomic<bool> currentPlayerTurn;
	std::atomic<bool> isPaused;

	std::atomic<std::chrono::milliseconds> whiteTimerDuration;
	std::atomic<std::chrono::milliseconds> blackTimerDuration;

	Callback notifyUI;
	Callback notifyGameOver;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};
