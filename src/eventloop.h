#pragma once
#include <queue>
#include <map>
#include <set>
#include "subscriber.h"

template<class EVENT_TYPE, class EVENT_CLASS>
class EventLoop {
public:
	//EventLoop();
	void subscribe(Subscriber<EVENT_TYPE, EVENT_CLASS>*, EVENT_TYPE);
	void unsubscribe(Subscriber<EVENT_TYPE, EVENT_CLASS>*, EVENT_TYPE);

	void subscribe(Subscriber<EVENT_TYPE, EVENT_CLASS>*);
	void unsubscribe(Subscriber<EVENT_TYPE, EVENT_CLASS>*);

	void pushEvent(EVENT_CLASS* e);

	bool pullEvent(); //returns false if queue is empty, true otherwise
private:
	std::queue<EVENT_CLASS*> mEvents;
	std::map<EVENT_TYPE, std::set<Subscriber<EVENT_TYPE, EVENT_CLASS>*>> mSubscribers;
};

#include "eventloop_impl.h"