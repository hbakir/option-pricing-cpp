#pragma once

/**
 * Templates for OptionData, ComputedData, IAlgorithm interface,
 * and policy-based SUD class (Source-Algorithm-Sink composition).
 */

#include <tuple>
#include <functional>

namespace op {

template <typename T>
using OptionData = std::tuple<T, T, T, T>;

template <typename T>
using ComputedData = std::tuple<T, T, T>;

template <typename T>
using IAlgorithm = std::function<ComputedData<T>(const OptionData<T>&, const T&)>;

template <typename T, template <typename> class Source, template <typename> class Sink>
class SUD : private Source<T>, private Sink<T>
{
    using Source<T>::getData;
    using Sink<T>::SendData;
    using Sink<T>::end;

    IAlgorithm<T> convert;

public:
    explicit SUD(const IAlgorithm<T>& conversion) : convert(conversion) {}

    void run(const T& S)
    {
        OptionData<T> t1 = getData();
        ComputedData<T> t2 = convert(t1, S);
        SendData(t2);
        end();
    }
};

} // namespace op

