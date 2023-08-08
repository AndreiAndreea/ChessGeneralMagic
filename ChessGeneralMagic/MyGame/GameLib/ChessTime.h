#pragma once
#include <thread>
#include <chrono>

class ChessTime
{
public:

	void Start() {
		if (!running) {
			start_time = std::chrono::high_resolution_clock::now();
			running = true;
		}
	}
	void Stop() {
		if (running) {
			stop_time = std::chrono::high_resolution_clock::now();
			running = false;
		}
	}

	bool IsRunning() const {
		return running;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
	std::chrono::time_point<std::chrono::high_resolution_clock> stop_time;
	bool running = false;
};

