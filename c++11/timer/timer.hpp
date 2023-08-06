#ifndef __TIMER_H__
#define __TIMER_H__

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <sstream>
#include <iomanip>
#include <memory>
#include <mutex>
#include <condition_variable>

class Timer {
public:
  Timer() :expired_(true), try_to_expire_(false) {}
  
  Timer(const Timer& timer) {
	expired_ = timer.expired_.load();
	try_to_expire_ = timer.try_to_expire_.load();
  }
  
  ~Timer() {
	stop();
  }
  
  void start(int interval, std::function<void()> task) {
	// is started, do not start again
	if (expired_ == false) {
	  return;
	}
	
	// start async timer, launch thread and wait in that thread
	expired_ = false;
	std::thread([this, interval, task]() {
	  int duration = interval;
	  while (!try_to_expire_) {
		// sleep every interval and do the task agin and again until times up
		std::this_thread::sleep_for(std::chrono::milliseconds(duration));
		auto beforeTime = std::chrono::steady_clock::now();
		task();
		std::cout << "current_time:" << this->format_time() << std::endl;
		auto afterTime = std::chrono::steady_clock::now();
		double diff = std::chrono::duration<double, std::milli>(afterTime - beforeTime).count();
		if (diff < interval) {
		  duration = interval - diff;
		} else {
		  duration = interval / 10;
		}
	  }
		
	  {
	    // timer be stopped, update the condition variable expired and wake main thread
		std::lock_guard<std::mutex> locker(mtx_);
		expired_ = true;
		cond_.notify_one();
	  }
	}).detach();
  }
  
  void startOnce(int delay, std::function<void()> task) {
	// Sufficient time is needed to wait for the task to complete
	std::thread([delay, task]() {
	  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	  task();
	}).detach();
  }

  void stop() {
	// do not stop again
	if (expired_) {
	  return;
	}
	
	if (try_to_expire_) {
	  return;
	}
	
	// wait until timer
	// change this bool value to make timer while loop stop
	try_to_expire_ = true;
	{
      std::unique_lock<std::mutex> locker(mtx_);
	  cond_.wait(locker, [this] {
		return expired_ == true;
	  });
	  
	  // reset the timer
	  if (expired_ == true) {
	    try_to_expire_ = false;
	  }
	}
  }
  
  std::string format_time() {
	auto now = std::chrono::system_clock::now();
	auto timet = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count() % 1000;
	std::stringstream ss;
	ss << std::put_time(localtime(&timet), "%Y-%m-%d %H:%M:%S") << "." << ms;
	return ss.str();
  }

private:
  // timer stopped status
  std::atomic<bool> expired_;
  // timer is in stop process
  std::atomic<bool> try_to_expire_;
  std::mutex mtx_;
  std::condition_variable cond_;
};


#endif//__TIMER_H__
