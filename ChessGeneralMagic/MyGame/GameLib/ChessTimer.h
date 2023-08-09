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

	TimeInfo GetTimerDuration(EPlayer player) const;

	//void AddObservers(IChessTimerListenerWeakPtr obs);
	//void RemoveObservers(IChessTimerListener* obs);

	//void NotifyTimerStart();

private:
	void TimerThread();
	TimeInfo PlayerCountDown(TimeInfo duration);

private:
	std::thread m_timerThread;

	std::atomic<bool> isTimerRunning;
	std::atomic<int> currentPlayerTurn;

	std::atomic<TimeInfo> whiteTimerDuration;
	std::atomic<TimeInfo> blackTimerDuration;

	Callback notify;
	std::mutex m_mutex;
	std::condition_variable m_condition;

	//Observers m_observers;
};
