#pragma once



class IChessTimerListener
{
public:
	
	virtual void OnTimerStart() = 0;

	virtual ~IChessTimerListener() = default;
};

using IChessTimerListenerPtr = std::shared_ptr<IChessTimerListener>;
using IChessTimerListenerWeakPtr = std::weak_ptr<IChessTimerListener>;