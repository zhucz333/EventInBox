//////////////////////////////////////////////////////////////////////////
///@file	IEventInBox.h												//
///@brief	class IEventInBox											//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/08/05													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "IEvent.h"
#include "IEventHandler.h"

enum EventScheduler
{
	SchedulerDisruptor = 0,
	SchedulerMThread
};

class IEventInBox
{
public:
	IEventInBox() = default;
	virtual ~IEventInBox() = default;

	static std::shared_ptr<IEventInBox> GetInBox();

	virtual bool Init(int thread_num, IEventHandler* handler, EventScheduler scheduler = SchedulerDisruptor) = 0;
	virtual bool Start() = 0;
	virtual bool Stop() = 0;
	virtual bool Post(std::shared_ptr<IEvent>& event) = 0;
};
