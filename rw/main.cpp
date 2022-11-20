#include <atomic>
#include <mutex>
#include <thread>
#include <fstream>
#include <iostream>
#include <string>
using std::string, std::mutex, std::lock_guard, std::scoped_lock, std::cout, std::endl;


string resource {"BASIC STRING"};
int thread_num {0};

mutex m_resource_r; //read
mutex m_resource_w; //write
mutex m_cout; //console output, also locks thread_num

void read()
{
    lock_guard<mutex> g_resource_r (m_resource_r);
    lock_guard<mutex> g_cout (m_cout);

    cout << "thread " << thread_num << " (" << std::this_thread::get_id() << ")" << " reads: " << resource << endl;
    thread_num++;
}

void write()
{
    scoped_lock write_lock (m_resource_r, m_resource_w);
    lock_guard<mutex> g_cout (m_cout);
    resource = resource + " after thread " + std::to_string (thread_num);
    cout << "thread " << thread_num << " (" << std::this_thread::get_id() << ")" << " writes: " << resource << endl;
    thread_num++;
    std::thread::id a;
}

int main()
{
    std::thread r1 (read), r2 (read), r3(read), w1 (write), w2 (write), w3 (write);

    r1.join();
    r2.join();
    r3.join();
    w1.join();
    w2.join();
    w3.join();
}
