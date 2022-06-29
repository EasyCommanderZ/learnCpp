

// 生产者数量
#include <CAS.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <ostream>
#include <system_error>
#include <thread>
#include <vector>

// 生产者数量
int producerWorks = 4;

// 消费者数量
int consumerWorks = 4;

// 每个生产者生产的个数
int producerNums = 1e3;

// 重复次数
int epochs = 10;

int all = producerWorks * producerNums;

//  记录物品的生产和消费
std::vector<std::atomic_int> in(all), out(all);

// 记录生产者和消费者的完成数目
std::atomic_int prodFinish{0};

LockFreeQueue<int> qu;

void produce(int _id) {
    int L = _id * producerNums, R = (_id + 1) * producerNums;
    for(int u = L; u < R; u ++) {
        qu.enqueue(u);
        in[u].fetch_add(1);
    }
    // 生产完毕，finish + 1；
    std::cout << "produce " << _id << " finish." << std::endl;
    prodFinish.fetch_add(1);
}

void benchmarkProduce(int _id) {
    int L = _id * producerNums, R = (_id + 1) * producerNums;
    for(int u = L; u < R; u ++) {
        qu.enqueue(u);
        // in[u].fetch_add(1);
    }
    // 生产完毕，finish + 1；
    std::cout << "produce " << _id << " finish." << std::endl;
    prodFinish.fetch_add(1);
}

void consume() {
    // 必须使用CAS操作判断，如果prodFinish的值不为produceWorks的数目，代表生产者还在生产
    int cur;
    while(prodFinish.compare_exchange_weak(producerWorks, producerWorks) == false) {
        while(qu.dequeue(cur)) {
            out[cur].fetch_add(1);
        }
    }
}

void benchmarkConsume() {
    // 必须使用CAS操作判断，如果prodFinish的值不为produceWorks的数目，代表生产者还在生产
    int cur;
    while(prodFinish.compare_exchange_weak(producerWorks, producerWorks) == false) {
        while(qu.dequeue(cur)) {
            // out[cur].fetch_add(1);
        }
    }
}

void lastConsume() {
    int cur;
    while(qu.dequeue(cur)) {
        out[cur].fetch_add(1);
    }
}

void benchmarkLastConsume() {
    int cur;
    while(qu.dequeue(cur)) {
        // out[cur].fetch_add(1);
    }
}

void check() {
    int inCnt = 0, outCnt = 0;
    for(int i = 0; i < all; i ++) {
        if(in[i].load() != 1) {
            std::cout << "produce object " << i << " error, val = " << in[i].load() << std:: endl;
            inCnt ++;
        }
    }
    
    for(int i = 0; i < all; i ++) {
        if(out[i].load() != 1) {
            std::cout << "consume object " << i << " error, val = " << out[i].load() << std::endl;
            outCnt ++;
        }
    }
    std::cout << "error in : " << inCnt << std::endl;
    std::cout << "error out : " << outCnt << std::endl;
}

void testCAS() {
    using tp = std::chrono::system_clock::time_point;
    tp start_time = std::chrono::system_clock::now();

    for(auto& c : in) {
        std::atomic_init(&c, 0);
    }

    for(auto& c : out) {
        std::atomic_init(&c, 0);
    }

    std::vector<std::thread> prod(producerWorks), cons(consumerWorks);
    for(int i = 0 ; i < producerWorks; i ++) {
        prod[i] = std::thread(produce, i);
    }
    for(auto& t : cons) {
        t = std::thread(consume);
    }

    for(auto& t : prod) {
        t.join();
    }

    for(auto& t : cons) {
        t.join();
    }

    lastConsume();

    check();

    tp end_time = std::chrono::system_clock::now();
    std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << all << " jobs, running time : " << time.count() << "ms" << std::endl;
}

void epochRunLockFree() {
    std::vector<std::thread> prod(producerWorks), cons(consumerWorks);

	for (int i = 0; i < producerWorks; i ++ )
		prod[i] = std::thread(benchmarkProduce, i);

	for (auto& t : cons)
		t = std::thread(benchmarkConsume);

	for (auto& t : prod)
		t.join();

	for (auto& t : cons)
		t.join();

	// 当生产者生产完毕后, 添加最后一个消费者, 该消费者保证能够将剩下的物品消费完毕
	benchmarkLastConsume();
}

void CASBenchmark() {
    std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now();

	for (int i = 0; i < epochs; i ++ )
		epochRunLockFree();

	std::chrono::time_point<std::chrono::system_clock> end_time = std::chrono::system_clock::now();
	std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

	std::cout << "\n" << epochs << " epoch cost total time = " << time.count() << "ms\nepoch cost average time = " << time.count() / epochs << " ms\n";
}