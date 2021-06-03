# expirable
simple header only llibrary for expirable values

### example

```c++
#include <iostream>
#include <thread>
#include <string>

#include "expirable.h"

template<typename T>
void printValueWithPeriod(const Expirable<T> &e)
{
    std::cout << "value = " << e.value() << "; expiration period = " << e.period().count() << std::endl;
}

int main(int argc, char** argv)
{
    Expirable<int> ei{10, std::chrono::seconds{2}};
    ei.setValue(20);
    printValueWithPeriod(ei);
    std::this_thread::sleep_for(std::chrono::seconds{1});
    printValueWithPeriod(ei);
    std::this_thread::sleep_for(std::chrono::seconds{2});
    printValueWithPeriod(ei);

    Expirable<std::string> es{std::string("default value"), std::string("hello world!!!"), std::chrono::seconds{2}};
    printValueWithPeriod(es);
    std::this_thread::sleep_for(std::chrono::seconds{1});
    printValueWithPeriod(es);
    std::this_thread::sleep_for(std::chrono::seconds{2});
    printValueWithPeriod(es);

    Expirable<std::string> unexpirable{std::string("default value"), std::string("unexpirable value"), std::chrono::seconds{0}};
    printValueWithPeriod(unexpirable);
    std::this_thread::sleep_for(std::chrono::seconds{1});
    printValueWithPeriod(unexpirable);
    std::this_thread::sleep_for(std::chrono::seconds{2});
    printValueWithPeriod(unexpirable);

    std::cout << "Done..." << std::endl;
    return 42;
}
```
