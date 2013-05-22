#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include "elib/semaphore.h"

#include <mutex>
#include <atomic>
#include <condition_variable>
#include <cassert>

namespace elib {
namespace _elib {
	
using unique_lock = std::unique_lock<std::mutex>;

class SemaphoreImpl 
{
public:
	SemaphoreImpl(unsigned int size) : m_size(size), m_count(ATOMIC_VAR_INIT(size))
	{ }
	
	inline unsigned int down() {
		unique_lock lock(m_lock);
		m_nempty_cv.wait(lock, [this]{ return this->m_count.load() > 0; });
		unsigned int val = m_count.fetch_sub(1);
		assert(val > 0 && val <= m_size);
		return val;
	}
	
	inline bool try_down(unsigned int &resource) {
		unique_lock lock(m_lock, std::try_to_lock);
		if (lock.owns_lock() && m_count.load() > 0) {
			resource = m_count.fetch_sub(1);
			return true;
		} else {
			return false;
		}
	}
	
	inline void up() {
		m_count.fetch_add(1);
		assert(m_count.load() <= m_size);
		m_nempty_cv.notify_one();
	}
	
	inline unsigned int size() const { 
		return m_size; 
	}
	
	inline unsigned int available() const {
		return m_count.load();
	}
	
	inline unsigned int taken() const { 
		return m_size - m_count.load();
	}

private:
	unsigned int m_size;
	std::atomic_uint m_count;
	std::mutex m_lock;
	std::condition_variable m_nempty_cv;
	DISALLOW_COPY_AND_ASSIGN(SemaphoreImpl);
};


} /* namespace _elib */
} /* namespace elib */
#endif /* _SEMAPHORE_H */