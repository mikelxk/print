#include "print.hpp"

int main()
{
    vector v1{1, 3, 2};
    vector v3{3, 8, 9, 10, 7, 8, 9};
    vector<string> vs{"a", "b"};
    vector<bool> vb{true, false};
    double da[] = {1.3, 1.7};
    map<int, int> mp{{1, 2}, {3, 4}};
    print(v1);
    print(v3);
    print(vs);
    print(vb);
    print(da);
    print(mp);
    tuple t = {1, "hello", 0.2};
    print(t);
}
