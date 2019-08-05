//////////////////////////////////////////////////////////////////////////
///@file	EventInBox.h												//
///@brief	class EventInBox											//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/08/05													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "EventInBox.h"
#include "Disruptor/ProducerType.h"
#include "Disruptor/BlockingWaitStrategy.h"
#include "Disruptor/IWorkHandler.h"
#include "Disruptor/ThreadPerTaskScheduler.h"
#include "DisruptorEventHandler.h"
#include "DisruptorExceptionHandler.h"

std::shared_ptr<IEventInBox> IEventInBox::GetInBox()
{
	return std::make_shared<EventInBox>();
}

EventInBox::~EventInBox()
{
	if (m_ptrMThread)
	{
		m_ptrMThread->Stop();
		m_ptrMThread = nullptr;
	}

	if (m_ptrDisruptor)
	{
		m_ptrDisruptor->shutdown();
		m_ptrTaskScheduler->stop();

		m_ptrDisruptor = nullptr;
		m_ptrTaskScheduler = nullptr;
	}
}

bool EventInBox::Init(int thread_num, IEventHandler* handler, EventScheduler scheduler)
{
	m_nThreadNum = thread_num;
	m_ptrEventHandler = handler;
	m_eScheduler = scheduler;

	if (m_eScheduler == EventScheduler::SchedulerMThread)
	{
		m_ptrMThread = std::make_shared<MThread>();
	}
	else if (m_eScheduler == EventScheduler::SchedulerDisruptor)
	{
		auto strategy = std::make_shared<Disruptor::BlockingWaitStrategy>();
		m_ptrTaskScheduler = std::make_shared<Disruptor::ThreadPerTaskScheduler>();
		m_ptrDisruptor = std::make_shared<Disruptor::disruptor<DisruptorEvent>>(
			[]() { return DisruptorEvent(); }, 
			1024, 
			m_ptrTaskScheduler, 
			Disruptor::ProducerType::Multi, 
			strategy
			);

		m_ptrDisruptor->setDefaultExceptionHandler(std::dynamic_pointer_cast<Disruptor::IExceptionHandler<DisruptorEvent>>(std::make_shared<DisruptorExceptionHandler>()));

		std::vector<std::shared_ptr<Disruptor::IWorkHandler<DisruptorEvent>>> vecWorkHandlers;
		for (int i = 0; i < m_nThreadNum; i++)
		{
			vecWorkHandlers.push_back(std::dynamic_pointer_cast<Disruptor::IWorkHandler<DisruptorEvent>>(std::make_shared<DisruptorEventHandler>(m_ptrEventHandler)));
		}

		m_ptrDisruptor->handleEventsWithWorkerPool(vecWorkHandlers);
	}

	return true;
}

bool EventInBox::Start()
{
	if (m_eScheduler == SchedulerMThread)
	{
		m_ptrMThread->Start(m_nThreadNum);
	}
	else if (m_eScheduler == SchedulerDisruptor)
	{
		m_ptrTaskScheduler->start(m_nThreadNum);
		m_ptrDisruptor->start();
	}

	return true;
}

bool EventInBox::Stop()
{
	if (m_eScheduler == SchedulerMThread)
	{
		m_ptrMThread->Stop();
		m_ptrMThread = nullptr;
	}
	else if (m_eScheduler == SchedulerDisruptor)
	{
		m_ptrDisruptor->shutdown();
		m_ptrTaskScheduler->stop();
		m_ptrDisruptor = nullptr;
		m_ptrTaskScheduler = nullptr;
	}

	return true;
}

bool EventInBox::Post(std::shared_ptr<IEvent>& event)
{
	if (m_eScheduler == SchedulerMThread)
	{
		m_ptrMThread->Post(std::bind(&IEventHandler::OnEvent, m_ptrEventHandler, event));
	}
	else if (m_eScheduler == SchedulerDisruptor)
	{
		auto ringBuffer = m_ptrDisruptor->ringBuffer();
		const auto nextSequence = ringBuffer->next();
		(*ringBuffer)[nextSequence].SetEvent(event);
		ringBuffer->publish(nextSequence);
	}

	return true;
}
