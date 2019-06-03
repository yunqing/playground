#ifndef __SINGLETON__
#define __SINGLETON__
// thread unsafe version
class SimpleSingleton {
public:
    static SimpleSingleton * get_singleton();
    static void release_singleton();
    int get_data();
    void set_data(int);
    int get_data_static();
    void set_data_static(int);
    SimpleSingleton * get_handle();
private:
    static SimpleSingleton * m_singleton;
    static int data_static;
    int data;
    SimpleSingleton() {
        this->data = 0;
    }
};
#endif
