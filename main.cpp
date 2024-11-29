#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

class Cutie {
public:
    virtual std::string description() = 0;
    virtual int cuteness_rating() = 0;
    virtual ~Cutie() = default;
};

class CutieQueue {
private:
    static const int MAX_SIZE = 100;
    Cutie* queue[MAX_SIZE];
    int front;
    int rear;
    int currentSize;

public:
    CutieQueue() : front(0), rear(-1), currentSize(0) {}
    
    ~CutieQueue() {
        while (currentSize > 0) {
            dequeue();
        }
    }

    void enqueue(Cutie* cutie) {
        if (currentSize >= MAX_SIZE) {
            std::cout << "Queue is full! Cannot add more cuties." << std::endl;
            return;
        }

        rear = (rear + 1) % MAX_SIZE;
        queue[rear] = cutie;
        currentSize++;
    }

    Cutie* dequeue() {
        if (currentSize <= 0) {
            throw std::runtime_error("Queue is empty!");
        }

        Cutie* cutie = queue[front];
        front = (front + 1) % MAX_SIZE;
        currentSize--;
        return cutie;
    }

    int size() const {
        return currentSize;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    bool isFull() const {
        return currentSize == MAX_SIZE;
    }

    void clear() {
        while (currentSize > 0) {
            Cutie* cutie = dequeue();
            delete cutie;
        }
        front = 0;
        rear = -1;
        currentSize = 0;
    }
};

class Puppy : public Cutie {
public:
    std::string description() override {
        return "A little puppy with big, sad eyes";
    }

    int cuteness_rating() override {
        return 11;
    }
};

class Kitten : public Cutie {
public:
    std::string description() override {
        return "A tiny kitten that fits in your palm";
    }

    int cuteness_rating() override {
        return 10;
    }
};

int main() {
    CutieQueue cutieQueue;
    
    Puppy* puppy = new Puppy();
    Kitten* kitten = new Kitten();
    
    cutieQueue.enqueue(puppy);
    cutieQueue.enqueue(kitten);
    
    std::cout << "Queue size: " << cutieQueue.size() << std::endl;
    
    Cutie* cutie = cutieQueue.dequeue();
    std::cout << "Dequeued cutie: " << cutie->description() << 
                 " (Rating: " << cutie->cuteness_rating() << "/10)" << std::endl;
    
    delete cutie;
    
    return 0;
}
