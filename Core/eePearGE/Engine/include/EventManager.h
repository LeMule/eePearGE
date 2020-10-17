#ifndef _EEPEARGE_EVENTMANAGER_H_
#define _EEPEARGE_EVENTMANAGER_H_

#include <functional>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <memory>

namespace eePearGE
{
	template <class T>
	class EventManager
	{
	public:
		EventManager()
		{
			m_last_update_time = 0.0;
			m_callbackMap.clear();
		};

		void RegisterCallback(T evt, std::function<void()> cb)
		{
			if (m_callbackMap.find(evt) != m_callbackMap.end())
				m_callbackMap[evt].push_back(cb);
			else
			{
				std::vector<std::function<void()> > funcVec;
				funcVec.push_back(cb);
				m_callbackMap.insert(std::make_pair(evt, funcVec));
			}
		}

		void Update(float time_delta)
		{
			m_last_update_time += std::abs(time_delta);
			if (m_last_update_time >= (float)300000000.0)
			{
				Pump();
				m_last_update_time = 0.0;
			}
		}

		void QueueEvent(T evt) { m_eventQueue.push(evt); }
		bool EventsQueued() { return !m_eventQueue.empty(); }
		void ProcessEvent(T evt)
		{
			std::for_each(m_callbackMap.begin(), m_callbackMap.end(),
				[&](auto a)
				{
					if (a.first == evt)
					{
						for (auto i : a.second)
						{
							i();
						}
					}
				}
			);
		}

		void Pump()
		{
			T nextEvt;
			if (!m_eventQueue.empty())
			{
				nextEvt = m_eventQueue.front();
				ProcessEvent(nextEvt);
				m_eventQueue.pop();
			};
		}

	private:

		std::map<T, std::vector<std::function<void()> > > m_callbackMap;
		std::queue<T> m_eventQueue;

		float m_last_update_time;
	};

	typedef EventManager<std::string> WordEventManager;
	typedef std::shared_ptr<WordEventManager> EventManagerPtr;
}

#endif