//////////////////////////////////////////////////////////////////////////
///@file	EventInBox.h												//
///@brief	class EventInBox											//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/08/05													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include "IEventInBox.h"
#include "Disruptor/Disruptor.h"
#include "Disruptor/ITaskScheduler.h"
#include "MThread.h"
#include "DisruptorEvent.h"

class EventInBox : public IEventInBox
{
public:
	EventInBox() = default;
	virtual ~EventInBox();

	virtual bool Init(int thread_num, IEventHandler* handler, EventScheduler scheduler) override;
	virtual bool Start() override;
	virtual bool Stop() override;
	virtual bool Post(std::shared_ptr<IEvent>& event) override;

private:
	int														m_nThreadNum;
	EventScheduler											m_eScheduler;
	IEventHandler*											m_ptrEventHandler;
	std::shared_ptr<MThread>								m_ptrMThread;
	std::shared_ptr<Disruptor::ITaskScheduler>				m_ptrTaskScheduler;
	std::shared_ptr<Disruptor::disruptor<DisruptorEvent>>	m_ptrDisruptor;
};
