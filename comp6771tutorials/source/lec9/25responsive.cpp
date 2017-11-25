#include <functional>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

// this is not a very good example, because we haven't covered ways to communicate properly between threads. We'll cover that next friday
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::mutex m;
    auto reset = false;
    std::function<double()> f = [] () { return 0; };

    std::thread t{[&] () {
        while (true) {
            long double total = 0;
            auto repeats = 0U;
            // note: this is a bit convoluted. We'll talk about the producer consumer problem next week for some better examples
            // perhaps a web server
            while (!reset) {
                std::lock_guard<std::mutex> l{m};
                // TODO: sleep
                total += f();
                ++repeats;
            }
            std::lock_guard<std::mutex> l{m};
            reset = false;
            std::cout << "Tried " << repeats << " times, got average of " << (static_cast<double>(total) / repeats) << '\n';
        }
    }};

    double i;
    std::normal_distribution<> distribution;
    while (std::cin >> i) {
        distribution = std::normal_distribution<>(i, 10000);
        std::lock_guard<std::mutex> l{m};
        f = [&distribution, &gen] () {
            return distribution(gen);
        };
        reset = true;
    }
}
