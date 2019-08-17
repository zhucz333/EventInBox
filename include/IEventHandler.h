//////////////////////////////////////////////////////////////////////////
///@file	IEventHandler.h												//
///@brief	class IEventHandler											//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/08/05													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "IEvent.h"

class IEventHandler
{
public:
	IEventHandler() = default;
	virtual ~IEventHandler() = default;

	virtual bool OnEvent(const std::shared_ptr<IEvent>& event) = 0;
};
