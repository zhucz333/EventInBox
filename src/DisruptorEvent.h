//////////////////////////////////////////////////////////////////////////
///@file	DisruptorEvent.h														//
///@brief	class DisruptorEvent													//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/08/05													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include "IEvent.h"

class DisruptorEvent
{
public:
	DisruptorEvent() = default;
	virtual ~DisruptorEvent() = default;

	void SetEvent(const std::shared_ptr<IEvent>& event){ m_ptrEvent = event; };
	std::shared_ptr<IEvent> GetEvent() const { return m_ptrEvent; };

private:
	std::shared_ptr<IEvent> m_ptrEvent;
};
