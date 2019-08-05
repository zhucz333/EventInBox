//////////////////////////////////////////////////////////////////////////
///@file	DisruptorExceptionHandler.h									//
///@brief	class DisruptorExceptionHandler								//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/08/05													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "DisruptorEvent.h"
#include "IEventHandler.h"
#include <Disruptor/IExceptionHandler.h>

class DisruptorExceptionHandler : public Disruptor::IExceptionHandler<DisruptorEvent>
{
public:
	DisruptorExceptionHandler() = default;
	virtual ~DisruptorExceptionHandler() = default;

	virtual void handleEventException(const std::exception& ex, std::int64_t sequence, DisruptorEvent& evt) override
	{
	}

	virtual void handleOnStartException(const std::exception& ex) override
	{
	}

	virtual void handleOnShutdownException(const std::exception& ex) override
	{
	}

	virtual void handleOnTimeoutException(const std::exception& ex, std::int64_t sequence) override
	{
	}
};
