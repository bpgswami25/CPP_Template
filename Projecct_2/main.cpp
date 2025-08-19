#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <type_traits>

template<typename T>
class DataSet {
    std::vector<T> mdata;
public:
    // SFINAE on constructor
    template<typename U = T, typename = typename std::enable_if<std::is_arithmetic<U>::value>,bool = true>
    DataSet(std::vector<U> data) : mdata(data.begin(), data.end()) {}

    ~DataSet() {}

    void print() const {
        for (auto t : mdata) {
            std::cout << t << " ";
        }
        std::cout << std::endl;
    }

    T getMin() const {
        return *std::min_element(mdata.begin(), mdata.end());
    }

    T getMax() const {
        return *std::max_element(mdata.begin(), mdata.end());
    }

    double getAverage() const {
        if (mdata.empty()) return 0.0;
        return static_cast<double>(std::accumulate(mdata.begin(), mdata.end(), 0)) / mdata.size();
    }

    void sortData() {
        std::sort(mdata.begin(), mdata.end());
    }

    bool findElement(const T& value) const {
        return std::find(mdata.begin(), mdata.end(), value) != mdata.end();
    }

    DataSet<T> filter(std::function<bool(const T&)> predicate) const {
        std::vector<T> filtered;
        for (const auto& item : mdata) {
            if (predicate(item)) {
                filtered.push_back(item);
            }
        }
        return DataSet<T>(filtered);
    }

    DataSet<T> transform(std::function<T(const T&)> func) const {
        std::vector<T> transformed;
        transformed.reserve(mdata.size());
        for (const auto& item : mdata) {
            transformed.push_back(func(item));
        }
        return DataSet<T>(transformed);
    }
};

int main()
{
    std::vector<int> v1{3,0,5,7,2,7};
    std::vector<float> v2{2.4,3.2,4.5,1.5,6,8};
    std::vector<int> v3{3,0,5,7,2,7};
    //std::vector<std::string>v3{"Hello","Hi","How","Are"};

    DataSet<int> d1(v1);
    d1.print();
    std::cout<<d1.getMin()<<std::endl;
    std::cout<<d1.getMax()<<std::endl;
    d1.sortData();
    d1.print();

    DataSet<int> evens = d1.filter([](int x) { return x % 2 == 0; });
    evens.print();

    DataSet<int> squares = d1.transform([](int x) { return x * x; });
    squares.print();

    DataSet<float> d2(v2);
    d2.print();
    std::cout<<d2.getMin()<<std::endl;
    std::cout<<d2.getMax()<<std::endl;
    d2.sortData();
    d2.print();

    DataSet<int> d3(v3);
    d3.print();
    std::cout<<d3.getMin()<<std::endl;
    std::cout<<d3.getMax()<<std::endl;
    d3.sortData();
    d3.print();

    return 0;
}