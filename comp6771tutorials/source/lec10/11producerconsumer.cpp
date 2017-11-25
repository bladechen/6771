#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


class ManufacturingPlant {
public:
  ManufacturingPlant() : materialsCount{0} {}
  
  void receiveMaterials(int i);
  int produceProduct();
private:
  int materialsCount;
  std::mutex materialsCountMutex;
  const int capacity = 100;
  std::condition_variable hasMaterials;
  std::condition_variable hascapacity;
};

class Truck {
public:
  Truck(ManufacturingPlant& m) : mp{m} {}
  void deliverMaterials() {
    mp.receiveMaterials(10);
  }
private:
  ManufacturingPlant& mp;
};

class Train {
public:
  Train(ManufacturingPlant& m) : mp{m} {}
  void getProduct() {
    mp.produceProduct();
  }
private:
  ManufacturingPlant& mp;
};  

void ManufacturingPlant::receiveMaterials(int i) {
  {
    using namespace std::chrono_literals;
    // NOTE: in producer-consumer systems, we can only really improve performance if we do all the expensive calculations outside of the lock
    std::this_thread::sleep_for(100ms);

    std::unique_lock<std::mutex> lg(materialsCountMutex);
    hascapacity.wait(lg, [this, &i] {
      return materialsCount + i <= capacity;
    });
    std::cout << std::this_thread::get_id() << " adding materials " << materialsCount << " -> " << materialsCount + i << '\n';
    materialsCount += i;
  }
  hasMaterials.notify_one();
}

int ManufacturingPlant::produceProduct() {
  {
    // NOTE: this global lock is a detriment to performance at the moment. Will it still be if we uncomment out these lines?
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);

    std::unique_lock<std::mutex> lg(materialsCountMutex);
    hasMaterials.wait(lg, [this] {
      return materialsCount - 10 >= 0;
    });
    std::cout << std::this_thread::get_id() << " consuming materials " << materialsCount << " -> " << materialsCount - 10 << '\n';
    materialsCount -= 10;
  }
  hascapacity.notify_one();
  return 10;
}

int main() {
  ManufacturingPlant plant;

  std::vector<std::thread> threads;

  auto nthreads = 10;
  auto deliveries_per_thread = 100;
  for (auto i = 0; i < nthreads; ++i) {
    // create a thread to make truck delieveries.
    threads.emplace_back([&]{
      for (int i = 0; i < deliveries_per_thread; ++i) {
        Truck t{plant};
        t.deliverMaterials();
      }
    });

    // create a thread to make trains arrive.
    threads.emplace_back([&]{
      for (int i = 0; i < deliveries_per_thread; ++i) {
        Train t{plant};
        t.getProduct();
      }
    });
  }

  // wait for threads to finish... 
  for (auto& thread: threads)
    thread.join();
}
