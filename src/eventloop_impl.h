#pragma once

template<class EVENT_TYPE, class EVENT_CLASS>
void EventLoop<EVENT_TYPE, EVENT_CLASS>::subscribe(Subscriber<EVENT_TYPE, EVENT_CLASS>* s, EVENT_TYPE t) {
	mSubscribers[t].insert(s);
}

template<class EVENT_TYPE, class EVENT_CLASS>
void EventLoop<EVENT_TYPE, EVENT_CLASS>::unsubscribe(Subscriber<EVENT_TYPE, EVENT_CLASS>* s, EVENT_TYPE t) {
	mSubscribers[t].erase(s);
}

template<class EVENT_TYPE, class EVENT_CLASS>
void EventLoop<EVENT_TYPE, EVENT_CLASS>::subscribe(Subscriber<EVENT_TYPE, EVENT_CLASS>* s) {
	for (EVENT_TYPE evType : s->acceptTypes()) {
		subscribe(s, evType);
	}
}

template<class EVENT_TYPE, class EVENT_CLASS>
void EventLoop<EVENT_TYPE, EVENT_CLASS>::unsubscribe(Subscriber<EVENT_TYPE, EVENT_CLASS>* s) {
	for (EVENT_TYPE evType : s->acceptTypes()) {
		unsubscribe(s, evType);
	}
}

template<class EVENT_TYPE, class EVENT_CLASS>
void EventLoop<EVENT_TYPE, EVENT_CLASS>::pushEvent(EVENT_CLASS* e) {
	mEvents.push(e);
	//outfile << "Pushed event " << e->type << std::endl;
}

template<class EVENT_TYPE, class EVENT_CLASS>
bool EventLoop<EVENT_TYPE, EVENT_CLASS>::pullEvent() {
	if (mEvents.empty()) return false;

	EVENT_CLASS* e = mEvents.front();
	mEvents.pop();
	std::set<Subscriber<EVENT_TYPE, EVENT_CLASS>*>& subs = mSubscribers[(EVENT_TYPE)(e->getType())];
	for (auto it = subs.begin(); it != subs.end(); ++it) {
		(*it)->processEvent(e);
	}

	delete e;

	return true;
}
