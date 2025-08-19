#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>

template<typename T>
class DataSet {
    std::vector<T> mdata;
public:
    DataSet(std::vector<T> data);
    ~DataSet();
    void print() const;
    T getMin() const;
    T getMax() const;
    double getAverage() const;
    void sortData();
    bool findElement(const T& value) const;
    DataSet<T> filter(std::function<bool(const T&)> predicate) const;
    DataSet<T> transform(std::function<T(const T&)> func) const;
};

// Implementation

template<typename T>
DataSet<T>::DataSet(std::vector<T> data): mdata(data) {}

template<typename T>
DataSet<T>::~DataSet() {}

template<typename T>
void DataSet<T>::print() const {
    for (auto t : mdata) {
        std::cout << t << " "  ;
    }
        std::cout << std::endl;
}

template<typename T>
T DataSet<T>::getMin() const {
    return *std::min_element(mdata.begin(), mdata.end());
}

template<typename T>
T DataSet<T>::getMax() const {
    return *std::max_element(mdata.begin(), mdata.end());
}

template<typename T>
double DataSet<T>::getAverage() const {
    if (mdata.empty()) return 0.0;
    return static_cast<double>(std::accumulate(mdata.begin(), mdata.end(), 0)) / mdata.size();
}

template<typename T>
void DataSet<T>::sortData() {
    std::sort(mdata.begin(), mdata.end());
}

template<typename T>
bool DataSet<T>::findElement(const T& value) const {
    return std::find(mdata.begin(), mdata.end(), value) != mdata.end();
}

template<typename T>
DataSet<T> DataSet<T>::filter(std::function<bool(const T&)> predicate) const {
    std::vector<T> filtered;
    for (const auto& item : mdata) {
        if (predicate(item)) {
            filtered.push_back(item);
        }
    }
    return DataSet<T>(filtered);
}

template<typename T>
DataSet<T> DataSet<T>::transform(std::function<T(const T&)> func) const {
    std::vector<T> transformed;
    transformed.reserve(mdata.size());
    for (const auto& item : mdata) {
        transformed.push_back(func(item));
    }
    return DataSet<T>(transformed);
}