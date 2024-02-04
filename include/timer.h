#ifndef TIMER_H_
#define TIMER_H_

#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

#include <priority_queue.hpp>
#include <types.h>


/**
 * @file timer.h
 * @brief Include Timer releated data structure and operations
 * @author Yakup Beyoglu
 * @date December 8, 2023
 * @see https://github.com/yakupbeyoglu
 */

namespace yb {
void foo();

/**
 * @brief Represents a timer event structure.
 */
class TimerEvent {

public:
  /**
   * @brief Base class for comparator objects.
   */
  class BaseComparator {
  public:
    virtual bool operator()(const TimerEvent &lhs, const TimerEvent &rhs) = 0;
    virtual ~BaseComparator() = default; // Ensure virtual destructor
  };

  /**
   * @brief Used by Desc order sorting
   * @param lhs The left-hand side TimerEvent object.
   * @param rhs The right-hand side TimerEvent object.
   * @return True if the left-hand side TimerEvent is "less than" the right-hand
   * side TimerEvent, false otherwise.
   */

  class ComparatorDesc : public BaseComparator {
  public:
    virtual bool operator()(const TimerEvent &lhs,
                            const TimerEvent &rhs) override {
      return lhs.expiration_time > rhs.expiration_time;
    }
  };

  /**
   * @brief Used by Asc order sorting
   * @param lhs The left-hand side TimerEvent object.
   * @param rhs The right-hand side TimerEvent object.
   * @return True if the right-hand side TimerEvent is "less than" the left-hand
   * side TimerEvent, false otherwise.
   */

  class ComparatorAsc : public BaseComparator {
  public:
    virtual bool operator()(const TimerEvent &lhs,
                            const TimerEvent &rhs) override {
      return lhs.expiration_time < rhs.expiration_time;
    }
  };
  types::TimePoint expiration_time;
  bool is_periodic;
  std::chrono::milliseconds interval;
  std::function<void()> callback_function;

  explicit TimerEvent(bool is_periodic,
                     std::chrono::milliseconds interval,
                     std::function<void()> &&callback_function)
      : is_periodic(is_periodic), interval(interval),
        callback_function(std::move(callback_function)) {
    expiration_time = std::chrono::high_resolution_clock::now() + interval;
  }

  void invokeCallBack() const { callback_function(); }
};

template<typename EventType = yb::TimerEvent>
class BaseTimer {
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void emplace(EventType &&event);
protected:
    virtual void loop() = 0;
};

template<typename EventType = yb::TimerEvent, typename Compare = yb::TimerEvent::ComparatorAsc, int limit = -1>
class Timer: protected BaseTimer<EventType> {

    Timer();
    ~Timer();

    Timer(const Timer &) = delete;
    Timer &operator = (const Timer &) = delete;

    Timer(Timer &&) = delete;
    Timer &operator = (const Timer &&) = delete;

    virtual void start() override;
    virtual void stop() override;

    virtual void emplace(EventType &&event);


protected:
    virtual void loop()override;
private:
    std::thread event_loop;

    std::atomic<bool> running;
    std::mutex loop_mutex, queue_mutex;
    std::condition_variable loop_cv;
};

} // namespace yb

#endif
