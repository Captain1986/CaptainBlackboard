/*********************************************************
 * C++11 chrono库封装的一个高精度计时器类（使用真实世界挂钟时间，具体时间依赖于系统）
 * 使用方式：
 * Timer t; // 开始计时
 * func();  // 运行待计时的函数
 * std::cout << t.elapsed() << std::endl; // 打印计时时间，默认毫秒为单位
 * std::cout << t.elapsed_micro() << std::endl; // 微秒
 * std::cout << t.elapsed_nano() << std::endl; // 纳秒
*********************************************************/

#ifndef _TIMER_
#define _TIMER_

#include <chrono>
using namespace std;
using namespace std::chrono;

class Timer {
    public:
        Timer() : m_begin(high_resolution_clock::now()) {}
        void reset() { m_begin = high_resolution_clock::now(); }

        // 默认输出毫秒
        template<typename Duration=milliseconds>
        int64_t elapsed() const {
            return duration_cast<Duration>(high_resolution_clock::now() - m_begin).count();
        }

        // 微秒
        int64_t elapsed_micro() const {
            return elapsed<microseconds>();
        }

        // 纳秒
        int64_t elapsed_nano() const {
            return elapsed<nanoseconds>();
        }

        // 秒
        int64_t elapsed_seconds() const {
            return elapsed<seconds>();
        }

        // 分
        int64_t elapsed_minutes() const {
            return elapsed<minutes>();
        }

        // 时
        int64_t elapsed_hours() const {
            return elapsed<hours>();
        }

    private:
        time_point<high_resolution_clock> m_begin;
};

#endif // !_TIMER_

