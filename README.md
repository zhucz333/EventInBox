## EventInBox
EventInBox通过对通用异步事件队列的封装，方便和简化事件模型在实际项目中的使用。
EventInBox的原型来自于量化平台项目，并在实际使用的基础上进行了扩充，同时支持Disruptor（https://github.com/Abc-Arbitrage/Disruptor-cpp）和MTthread两种事件调度方式。

### 使用
1）定义一个事件，确定事件名称，如两数相减的事件，事件名为SUB
```cpp
  class SubEvent: public IEvent
  {
  public:
  	SubEvent(int a, int b) : m_nA(a), m_nB(b) {};
  	~SubEvent() = default;
  
  	virtual std::string GetEventKey() override
  	{
  		return "SUB";
  	}
  
  	int GetA() { return m_nA; }
  	int GetB() { return m_nB; }
  private:
  	int m_nA;
  	int m_nB;
  };
```
2)定义事件处理类，如EventHandler，处理事件SUB
```cpp
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
```
3)定义一个信箱，设定信箱使用的事件处理模型、及线程数、绑定事件处理类对象，同时启用信箱
```cpp
  std::shared_ptr<IEventInBox> box_disruptor = IEventInBox::GetInBox();
  EventHandler* handler = new EventHandler();
  box_disruptor->Init(1, handler, SchedulerDisruptor);
  
  box_disruptor->Start();
 ```
 4）生成事件，并向信箱投递事件
 ```cpp
  std::shared_ptr<IEvent> event = std::make_shared<SubEvent>(2000, 500);
  box_disruptor->Post(event);
 ```
 5)使用完毕，关闭信箱
 ```cpp
  box_disruptor->Stop();
 ```
 ### Disruptor和MThread性能比较
 1）测试场景
 <br>分别通过多个线程的方式产生总数为10000个的异步事件，分别对两种事件调度器各使用一个消费线程来处理异步事件，当一个处理完毕时，统计另一个处理的事件总数。</br>
 2）测试结果
<br>生产者线程数目	每个生产者生产事件数	事件总数	Disruptor执行事件数	Mthread执行事件数</br>
<br>1	                  10000	         10000	      10000	            7155</br>
<br>10	                1000	         10000	      10000	            6854</br>
<br>100	                100	           10000	      10000	            7186</br>

Disruptor的性能至少比MThread快30%~40%

