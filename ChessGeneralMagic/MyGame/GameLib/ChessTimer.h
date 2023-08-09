#include <thread>
#include <chrono>
#include <atomic>
#include "EPlayer.h"
#include "TimeInfo.h"
#include "IChessTimerListener.h"

#include <vector>
#include <functional>
#include <mutex>
#include <memory>

using Observers = std::vector<IChessTimerListenerWeakPtr>;

using Callback = std::function<void()>;

class ChessTimer
{
public:
	ChessTimer();

	void StartTimer();

	void StopTimer();

	void SetCallback(Callback cb);
	void NotifyTimer();

	void UpdateTurn();

	bool IsTimerRunning();

	void Reset();

	int GetTimerDuration(EPlayer player) const;

	//void AddObservers(IChessTimerListenerWeakPtr obs);
	//void RemoveObservers(IChessTimerListener* obs);

	//void NotifyTimerStart();

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

	//Observers m_observers;
};
