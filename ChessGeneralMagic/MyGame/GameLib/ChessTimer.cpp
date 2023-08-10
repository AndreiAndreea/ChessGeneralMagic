#include "ChessTimer.h"


using namespace std::chrono_literals;

ChessTimer::ChessTimer()
	: isTimerRunning(false)
	, isPaused(false)
	, currentPlayerTurn(0)
	, whiteTimerDuration(std::chrono::duration_cast<std::chrono::milliseconds>(5s))
	, blackTimerDuration(std::chrono::duration_cast<std::chrono::milliseconds>(1min))
{}

ChessTimer::~ChessTimer()
{
	StopTimer();
}

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
	isPaused = true;
	m_condition.notify_one();
}

void ChessTimer::ResumeTimer()
{
	isPaused = false;
	m_condition.notify_one();
}

void ChessTimer::SetCallbackNotifyUI(Callback cb)
{
	notifyUI = cb;
}

void ChessTimer::SetCallbackNotifyGameOver(Callback cb)
{
	notifyGameOver = cb;
}

void ChessTimer::NotifyTimer()
{
	if (notifyUI)
		notifyUI();
}

void ChessTimer::NotifyGameOver()
{
	if (notifyGameOver)
		notifyGameOver();
}

void ChessTimer::UpdateTurn()
{
	currentPlayerTurn = !currentPlayerTurn;
}

bool ChessTimer::IsTimerRunning() const
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
	return (int)player ? blackTimerDuration.load().count() : whiteTimerDuration.load().count();
}

bool ChessTimer::IsTimeOut() const
{
	return whiteTimerDuration.load().count() <= 0 || blackTimerDuration.load().count() <= 0;
}

void ChessTimer::TimerThread()
{
	auto currentTurn = currentPlayerTurn.load();
	auto startTime = std::chrono::steady_clock::now();

	while (isTimerRunning)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_condition.wait_for(lock, 1ms, [this, currentTurn]
			{
				return (currentTurn != currentPlayerTurn.load()) || isPaused.load() || !isTimerRunning.load() || IsTimeOut();
			});

		if (IsTimeOut())
		{
			NotifyGameOver();
			return;
		}

		currentTurn = currentPlayerTurn.load();

		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::milliseconds(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime));

		startTime = std::chrono::steady_clock::now();

		auto& duration = currentTurn ? blackTimerDuration : whiteTimerDuration;
		duration.store(duration.load() - elapsedTime);
		NotifyTimer();
	}
}