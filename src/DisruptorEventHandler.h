//////////////////////////////////////////////////////////////////////////
///@file	DisruptorEventHandler.h										//
///@brief	class DisruptorEventHandler									//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/08/05													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <Disruptor/IWorkHandler.h>
#include "DisruptorEvent.h"
#include "IEventHandler.h"

class DisruptorEventHandler : public Disruptor::IWorkHandler<DisruptorEvent>
{
public:
	DisruptorEventHandler(IEventHandler* handler) : m_ptrHandler(handler) {};
	virtual ~DisruptorEventHandler() = default;

	void onEvent(DisruptorEvent& event) override;;

private:
	IEventHandler* m_ptrHandler;
};

inline void DisruptorEventHandler::onEvent(DisruptorEvent& event)
{
	m_ptrHandler->OnEvent(event.GetEvent());
}
