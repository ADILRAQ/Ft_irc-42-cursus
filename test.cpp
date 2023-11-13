#include <iostream>
#include <poll.h>
#include <vector>

class test {
    private:
        int arr[1];
        short arr1[2];
    public:
        test() : arr[0](0), arr1[0](1){}
        int &operator [] (int i){return arr[0];}
        short operator [] (int i){return arr1[2];}
};

int main()
{
    test    t;

    std::cout << t[12] << std::endl;
    std::cout << t[10] << std::endl;
}