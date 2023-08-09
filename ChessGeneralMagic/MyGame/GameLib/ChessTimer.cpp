#include "ChessTimer.h"


using namespace std::chrono_literals;

ChessTimer::ChessTimer()
	: isTimerRunning(false)
	, currentPlayerTurn(0)
	, whiteTimerDuration{ { 0, 15 } } 
	, blackTimerDuration{ { 1, 0 } }
{}

void ChessTimer::StartTimer()
{
	if (!isTimerRunning) 
	{
		isTimerRunning = true;
		m_timerThread = std::thread(&ChessTimer::TimerThread, this);
	}
}

void ChessTimer::StopTimer()
{
	if (isTimerRunning) 
	{
		isTimerRunning = false;
		m_timerThread.join();
	}
}

void ChessTimer::SetCallback(Callback cb)
{
	notify = cb;
}

void ChessTimer::NotifyTimer()
{
	if (notify) {
		notify();
	}
}

void ChessTimer::UpdateTurn()
{
	currentPlayerTurn = !currentPlayerTurn;
}

bool ChessTimer::IsTimerRunning()
{
	return isTimerRunning;
}

void ChessTimer::Reset()
{
	whiteTimerDuration = TimeInfo{10, 0};
	blackTimerDuration = TimeInfo{10, 0};
	isTimerRunning = false;
	currentPlayerTurn = 0;
}

TimeInfo ChessTimer::GetTimerDuration(EPlayer player) const
{
	return (int)player ? blackTimerDuration : whiteTimerDuration;
}

TimeInfo ChessTimer::PlayerCountDown(TimeInfo duration)
{
	auto currentTurn = currentPlayerTurn.load();
	auto startTime = std::chrono::steady_clock::now();

	while (isTimerRunning && currentTurn == currentPlayerTurn.load())
	{
		if (duration.minutes == 0 && duration.seconds == 0) 
		{
			isTimerRunning = false;
			auto currentTime = std::chrono::steady_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
			NotifyTimer();
		}
		else 
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_condition.wait_for(lock, 100ms, [this, currentTurn] { return currentTurn != currentPlayerTurn.load(); });

			//std::this_thread::sleep_for(std::chrono::seconds(1));
			if (duration.seconds == 0) {
				duration.minutes--;
				duration.seconds = 59;

				/*auto currentTime = std::chrono::steady_clock::now();
				auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();*/

				NotifyTimer();
			}
			else {
				duration.seconds--;
				NotifyTimer();
			}
		}
		//PerformAction();

		return duration;
	}

}

void ChessTimer::TimerThread()
{
	while (isTimerRunning)
	{
		if (currentPlayerTurn.load())
		{
			blackTimerDuration = PlayerCountDown(blackTimerDuration);
		}
		else
		{
			whiteTimerDuration = PlayerCountDown(whiteTimerDuration);
		}
	}
	
}