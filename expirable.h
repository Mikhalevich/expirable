#pragma once

#include <chrono>
#include <utility>

#ifdef EXPIRABLE_ENABLE_THREADS
#include <mutex>
#endif // EXPIRABLE_ENABLE_THREADS

template<typename T>
class Expirable
{
    using time_period = std::chrono::steady_clock::duration;
public:
    Expirable(const T& dv, time_period period)
        : m_defaultValue(dv)
        , m_value(dv)
        , m_expirationPeriod(period)
    {
        // empty
    }

    Expirable(const T& defaultValue, const T& value, time_period period)
        : m_defaultValue(defaultValue)
        , m_expirationPeriod(period)
    {
        setValue(value);
    }

    void setValue(const T& value)
    {
#ifdef EXPIRABLE_ENABLE_THREADS
        std::lock_guard<std::mutex> lock(m_mut);
#endif // EXPIRABLE_ENABLE_THREADS

        m_value = value;

        if (isExpirationPeriodValid())
        {
            m_updateTime = std::chrono::steady_clock::now();
        }
    }

    T value() const
    {
        auto p = valueWithPeriod();
        return p.first;
    }

    time_period period() const
    {
        auto p = valueWithPeriod();
        return p.second;
    }

    operator T() const
    {
        return value();
    }

    std::pair<T, time_period> valueWithPeriod() const
    {
#ifdef EXPIRABLE_ENABLE_THREADS
        std::lock_guard<std::mutex> lock(m_mut);
#endif // EXPIRABLE_ENABLE_THREADS

        if (!isExpirationPeriodValid())
        {
            return std::make_pair(m_value, time_period::zero());
        }

        auto duration = std::chrono::steady_clock::now() - m_updateTime;
        if (m_expirationPeriod > duration)
        {
            return std::make_pair(m_value, m_expirationPeriod - duration);
        }

        return std::make_pair(m_defaultValue, time_period::zero());
    }

private:
    bool isExpirationPeriodValid() const
    {
        return (m_expirationPeriod != time_period::zero());
    }

    T m_defaultValue;
    T m_value;
    time_period m_expirationPeriod;
    std::chrono::steady_clock::time_point m_updateTime;

#ifdef EXPIRABLE_ENABLE_THREADS
    mutable std::mutex m_mut;
#endif // EXPIRABLE_ENABLE_THREADS
};
