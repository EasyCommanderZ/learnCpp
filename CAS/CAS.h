#ifndef __CAS_CAS_H_
#define __CAS_CAS_H_

#include <atomic>

template <class T>
class LockFreeQueue {
public:
    struct Node {
        T val;
        std::atomic<Node *> next;
        Node() :
            val(T()), next(std::atomic<Node *>{nullptr}){};
        Node(const T &_v) :
            val(_v), next(std::atomic<Node *>{nullptr}){};
        Node(const T &_v, std::atomic<Node *> _next) :
            val(_v), next(_next){};
    };

    LockFreeQueue() {
        Node *dummy = new Node;
        this->head.store(dummy);
        this->tail.store(dummy);
    }

    void enqueue(T _val) {
        Node *p = new Node(_val);
        Node *cur, *next;
        Node *null = nullptr;
        while (true) {
            cur = tail.load();
            next = cur->next;
            if (cur != tail.load()) {
                continue;
            }
            if (next != nullptr) {
				// 当next指针不为空时, 尝试移动tail指针, 防止出现死锁
				tail.compare_exchange_weak(cur, next);
				continue;
			}
            if (cur->next.compare_exchange_weak(null, p)) {
                break;
            }
        }
        tail.compare_exchange_weak(cur, p);
    }

    bool dequeue(T &_ret) {
        Node *nowHead, *nowTail, *next;
        while (true) {
            nowHead = this->head.load();
            nowTail = this->tail.load();
            next = nowHead->next;
            if (nowHead != head.load()) {
                // head was moved by other thread, get new snapshot
                continue;
            }
            if (nowHead == nowTail and next == nullptr) {
                // empty queue
                return false;
            }

            if (nowHead == nowTail and next != nullptr) {
                // wrong tail
                tail.compare_exchange_weak(nowTail, next);
                continue;
            }
            _ret = next -> val;
            if (head.compare_exchange_weak(nowHead, next)) {
                break;
            }
        }
        delete nowHead;
        return true;
    }

    LockFreeQueue(const LockFreeQueue &) = delete;
    LockFreeQueue operator=(const LockFreeQueue &) = delete;

private:
    std::atomic<Node *> head, tail;
};

void produce(int _id);
void consume();
void lastConsume();
void check();

void testCAS();
void epochRunLockFree();
void CASBenchmark();

#endif /* __CAS_CAS_H_ */
