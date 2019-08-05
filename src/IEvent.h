//////////////////////////////////////////////////////////////////////////
///@file	IEvent.h													//
///@brief	class IEvent												//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/08/05													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

class IEvent
{
public:
	IEvent() = default;
	virtual ~IEvent() = default;

	virtual std::string GetEventKey() = 0;
};
