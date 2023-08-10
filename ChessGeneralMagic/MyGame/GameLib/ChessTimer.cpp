#include "ChessTimer.h"


using namespace std::chrono_literals;

ChessTimer::ChessTimer()
	: isTimerRunning(false)
	, currentPlayerTurn(0)
	, whiteTimerDuration(std::chrono::duration_cast<std::chrono::milliseconds>(1min))
	, blackTimerDuration(std::chrono::duration_cast<std::chrono::milliseconds>(1min))
{}

void ChessTimer::StartTimer()
{
	if (!isTimerRunning)
	{
		isTimerRunning = true;
		m_condition.notify_one();
		m_timerThread = std::thread(&ChessTimer::TimerThread, this);
	}
}

void ChessTimer::StopTimer()
{
	if (isTimerRunning)
	{
		isTimerRunning = false;
		m_condition.notify_one();
		if (m_timerThread.joinable())
			m_timerThread.join();
	}
}

void ChessTimer::PauseTimer()
{
	isTimerRunning = false;
	m_condition.notify_one();
}

void ChessTimer::ResumeTimer()
{
	isTimerRunning = true;
	m_condition.notify_one();
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
	whiteTimerDuration = std::chrono::duration_cast<std::chrono::milliseconds>(10min);
	blackTimerDuration = std::chrono::duration_cast<std::chrono::milliseconds>(10min);
	isTimerRunning = false;
	m_condition.notify_one();
	currentPlayerTurn = 0;
}

int ChessTimer::GetTimerDuration(EPlayer player) const
{
	return (int)player ? blackTimerDuration.load().count() / 1000 : whiteTimerDuration.load().count() / 1000;
}

void ChessTimer::TimerThread()
{
	auto currentTurn = currentPlayerTurn.load();
	auto startTime = std::chrono::steady_clock::now();

	while (isTimerRunning)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_condition.wait_for(lock, 1ms, [this, currentTurn] { return (currentTurn != currentPlayerTurn.load()) || !isTimerRunning.load(); });
		currentTurn = currentPlayerTurn.load();

		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::milliseconds(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime));
		startTime = std::chrono::steady_clock::now();

		if (currentTurn)
		{
			blackTimerDuration.store(blackTimerDuration.load() - elapsedTime);
			NotifyTimer();
		}
		else
		{
			whiteTimerDuration.store(whiteTimerDuration.load() - elapsedTime);
			NotifyTimer();
		}
	}
}