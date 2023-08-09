#include "ChessTimer.h"


ChessTimer::ChessTimer()
	: isTimerRunning(false)
	, currentPlayerTurn(0)
	, whiteTimerDuration{ { 10, 0 } } 
	, blackTimerDuration{ { 10, 0 } }
{}

void ChessTimer::StartTimer()
{
	if (!isTimerRunning) {
		isTimerRunning = true;
		m_timerThread = std::thread(&ChessTimer::TimerThread, this);
	}
}

void ChessTimer::StopTimer()
{
	if (isTimerRunning) {
		isTimerRunning = false;
		m_timerThread.join();
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

TimeInfo ChessTimer::GetTimerDuration(EPlayer player) const
{
	return (int)player ? blackTimerDuration : whiteTimerDuration;
}

TimeInfo ChessTimer::PlayerCountDown(TimeInfo duration)
{
	auto currentTurn = currentPlayerTurn.load();
	while (isTimerRunning && currentTurn == currentPlayerTurn.load())
	{
		if (duration.minutes == 0 && duration.seconds == 0) {
			isTimerRunning = false;
		}
		else {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			if (duration.seconds == 0) {
				duration.minutes--;
				duration.seconds = 59;
			}
			else {
				duration.seconds--;
			}
		}

		return duration;
	}
}

void ChessTimer::TimerThread()
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