/*
 * Black-Scholes analytical formulas, Input/Output, and Processing policies
 * from Duffy's Financial Instrument Pricing Using C++ (Chapter 1).
 */

#pragma once

#include <cmath>
#include <tuple>
#include <mutex>
#include <iostream>
#include <functional>

#include "sud.hpp"

namespace op {

// Standard normal density function
inline double n(double x)
{
    constexpr double PI = 3.14159265358979323846;
    const double A = 1.0 / std::sqrt(2.0 * PI);
    return A * std::exp(-x * x * 0.5);
}

// Cumulative normal distribution using error function
inline double cndN(double x)
{
    return 0.5 * (1.0 - std::erf(-x / std::sqrt(2.0)));
}

inline double N(double x)
{
    return cndN(x);
}

// Option Pricing; price, delta and gamma
template <typename V>
ComputedData<V> CallValues(const OptionData<V>& optData, const V& S)
{
    V K = std::get<0>(optData);
    V T = std::get<1>(optData);
    V r = std::get<2>(optData);
    V v = std::get<3>(optData);
    V b = r;

    V tmp = v * std::sqrt(T);
    V d1 = (std::log(S / K) + (b + 0.5 * v * v) * T) / tmp;
    V d2 = d1 - tmp;

    V t1 = std::exp((b - r) * T);
    V t2 = std::exp(-r * T);
    V Nd1 = N(d1);
    V Nd2 = N(d2);

    V price = S * t1 * Nd1 - K * t2 * Nd2;
    V delta = t1 * Nd1;
    V gamma = (n(d1) * t1) / (S * tmp);

    return std::make_tuple(price, delta, gamma);
}

// Option Pricing; price, delta and gamma
template <typename V>
ComputedData<V> PutValues(const OptionData<V>& optData, const V& S)
{
    V K = std::get<0>(optData);
    V T = std::get<1>(optData);
    V r = std::get<2>(optData);
    V v = std::get<3>(optData);
    V b = r;

    V tmp = v * std::sqrt(T);
    V d1 = (std::log(S / K) + (b + 0.5 * v * v) * T) / tmp;
    V d2 = d1 - tmp;

    V t1 = std::exp((b - r) * T);
    V t2 = std::exp(-r * T);
    V Nmd2 = N(-d2);
    V Nmd1 = N(-d1);

    V price = K * t2 * Nmd2 - S * t1 * Nmd1;
    V delta = t1 * (Nmd1 - 1.0);
    V gamma = (n(d1) * t1) / (S * tmp);

    return std::make_tuple(price, delta, gamma);
}

// Function to avoid garbled output on the console (thread-safe)
template <typename T>
void ThreadSafePrint(const ComputedData<T>& tup)
{
    static std::mutex my_mutex;
    std::lock_guard<std::mutex> guard(my_mutex);
    std::cout << "("
              << std::get<0>(tup) << ","
              << std::get<1>(tup) << ","
              << std::get<2>(tup) << ")\n";
}

// Hard-coded source of OptionData
template <typename T>
class Input
{
public:
    static OptionData<T> getData()
    {
        T K = 65.0;
        T expiration = 0.25;
        T r = 0.08;
        T v = 0.3;
        return OptionData<T>(K, expiration, r, v);
    }
};

// Console sink for ComputedData
template <typename T>
class Output
{
public:
    void SendData(const ComputedData<T>& tup) const
    {
        ThreadSafePrint(tup);
    }

    void end() const
    {
        std::cout << "end\n";
    }
};

// Processing policy: call option
template <typename T>
class Processing
{
public:
    ComputedData<T> convert(const OptionData<T>& optData, const T& S) const
    {
        return CallValues(optData, S);
    }

    ComputedData<T> operator()(const OptionData<T>& optData, const T& S) const
    {
        return CallValues(optData, S);
    }
};

// Processing policy: put option
template <typename T>
class ProcessingII
{
public:
    ComputedData<T> convert(const OptionData<T>& optData, const T& S) const
    {
        return PutValues(optData, S);
    }

    ComputedData<T> operator()(const OptionData<T>& optData, const T& S) const
    {
        return PutValues(optData, S);
    }
};

} // namespace op
