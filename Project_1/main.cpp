#include "manager.hpp"

int main()
{
    std::vector<int> v1{3,0,5,7,2,7};
    std::vector<float> v2{2.4,3.2,4.5,1.5,6,8};
    std::vector<std::string>v3{"Hello","Hi","How","Are"};
    //std::vector<int> v3{3,0,5,7,2,7};

    DataSet d1(v1);
    d1.print();
    std::cout<<d1.getMin()<<std::endl;
    std::cout<<d1.getMax()<<std::endl;
    d1.sortData();
    d1.print();


    DataSet<int> evens = d1.filter([](int x) { return x % 2 == 0; });
    evens.print();

    // Transforming: squaring each element in the DataSet
    DataSet<int> squares = d1.transform([](int x) { return x * x; });
    squares.print();


    DataSet d2(v2);
    d2.print();
    std::cout<<d2.getMin()<<std::endl;
    std::cout<<d2.getMax()<<std::endl;
    d2.sortData();
    d2.print();

    DataSet d3(v3);
    d3.print();
    std::cout<<d3.getMin()<<std::endl;
    std::cout<<d3.getMax()<<std::endl;
    d3.sortData();
    d3.print();

    return 0;
}