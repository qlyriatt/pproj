#include <memory>
#include <mutex>
#include <iostream>


template <typename T>
class CircularBuffer
{
public:
    CircularBuffer(int s) : size (s), buf (std::unique_ptr<T[]>(new T(s))) {};

    int getHead()
    {
        return head;
    }

    int getTail()
    {
        return tail;
    }

    bool isEmpty()
    {
        return head == tail;
    }

    bool isFull()
    {
        if (tail)
            return (head + 1) == tail;
        else 
            return head == (size - 1);
    }

    void clear()
    {
        std::lock_guard<std::mutex> g_buf (m_buf);
        head = tail;
    }

    void write(T element)
    {
        std::lock_guard<std::mutex> g_buf (m_buf);

        if (isFull())
        {
            tail = (tail + 1) % size;
        }
        buf [head] = element;
        head = (head + 1) % size;
    }

    //returns the same elem at head if empty
    T read()
    {
        std::lock_guard<std::mutex> g_buf (m_buf);
        auto element = buf [tail];
        if (!isEmpty())
            tail = (tail + 1) % size;
        return element;
    }

private:
    std::mutex m_buf;
    std::unique_ptr<T[]> buf;
    int head {0};
    int tail {0};
    const int size;    
};

int main()
{
    int N = 8;
    CircularBuffer<int> buf(N);

    using std::cout, std::endl;

    //watch write
    for (int i = 0; i < N + 1; i++)
    {
        buf.write (i);
        cout << "tail: " << buf.getTail() << " head: " << buf.getHead() << " latest elem: " << i << " isFull: " << buf.isFull() << endl;
    }

    //watch read
    for (int i = N + 2; i >= 0; i--) 
    {
        cout << buf.read() << endl;
    }
}