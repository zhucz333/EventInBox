//////////////////////////////////////////////////////////////////////////
///@file	IXLog.h														//
///@brief	class Log													//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/04/08													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

class IEvent
{
public:
	IEvent() = default;
	virtual ~IEvent() = default;

	virtual std::string GetEventKey() { return "default name"; };
};
