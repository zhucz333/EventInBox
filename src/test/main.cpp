#include "IEvent.h"
#include "IEventHandler.h"
#include "IEventInBox.h"
#include <iostream>
#include <thread>

class SubEvent: public IEvent
{
public:
	SubEvent(int a, int b) : m_nA(a), m_nB(b) {};
	~SubEvent() = default;

	std::string GetEventKey() override
	{
		return "SUB";
	}
	std::string ToString() override
	{
		return "m_nA=" + std::to_string(m_nA) + ",m_nb=" + std::to_string(m_nB);
	}

	int GetA() { return m_nA; }
	int GetB() { return m_nB; }

private:
	int m_nA;
	int m_nB;
};

class EventHandler : public IEventHandler
{
public:
	EventHandler() = default;
	~EventHandler() = default;

	bool OnEvent(const std::shared_ptr<IEvent>& event) override
	{
		if (event->GetEventKey() == "SUB")
		{
			std::shared_ptr<SubEvent> sub_event = std::dynamic_pointer_cast<SubEvent>(event);
			std::cout << "sub is:" << sub_event->GetA() - sub_event->GetB() << std::endl;
		}

		return true;
	}
};

std::shared_ptr<IEventInBox> box_mthread = IEventInBox::GetInBox();
std::shared_ptr<IEventInBox> box_disruptor = IEventInBox::GetInBox();

void thread_func_thread(int id)
{
	std::shared_ptr<IEvent> event = std::make_shared<SubEvent>(1000, 500);
	for (auto i = 0; i < 10000; i++)
	{
		box_mthread->Post(event);
	}
}

void thread_func_disruptor(int id)
{
	std::shared_ptr<IEvent> event = std::make_shared<SubEvent>(2000, 500);
	for (auto i = 0; i < 10000; i++)
	{
		box_disruptor->Post(event);
	}
}

int main()
{
	EventHandler* handler = new EventHandler();

	box_mthread->Init(1, handler, SchedulerMThread);
	box_disruptor->Init(1, handler, SchedulerDisruptor);

	box_mthread->Start();
	box_disruptor->Start();

	auto t1 = time(nullptr);

	for (auto i = 0; i < 1; i++)
	{
		auto t_2 = new std::thread(thread_func_thread, 0);
		auto t_1 = new std::thread(thread_func_disruptor, 0);
	}

	auto t2 = time(nullptr);

	std::cout << "cost: " << t2 - t1 << std::endl;

	getchar();

	box_disruptor->Stop();
	box_mthread->Stop();

	return 0;
}