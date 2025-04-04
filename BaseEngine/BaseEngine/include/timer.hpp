#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <string>
#include <chrono>

namespace BaseEngine {
    class Timer {
        public:
            Timer() {
                reset();
            }

            void reset() {
                m_Start = std::chrono::high_resolution_clock::now();
            }

            float elapsed() {
                return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
            }

            float elapsedMillis() {
                return elapsed() * 1000.0f;
            }

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
    };

    class ScopedTimer {
        public:
            ScopedTimer(const std::string &name) : m_Name(name) {}

            ~ScopedTimer() {
                float time = m_Timer.elapsedMillis();
                std::cout << "[TIMER] " << m_Name << " - " << time << "ms\n";
            }

        private:
            std::string m_Name;
            Timer m_Timer;
    };
}

#endif
