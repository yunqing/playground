#include <cstddef>
#include "singleton.h"
SimpleSingleton * SimpleSingleton::m_singleton = nullptr;
int SimpleSingleton::data_static = 0;
SimpleSingleton * SimpleSingleton::get_singleton() {
    if (SimpleSingleton::m_singleton == nullptr) {
        SimpleSingleton::m_singleton = new SimpleSingleton();
    }
    return SimpleSingleton::m_singleton;
}
void SimpleSingleton::release_singleton() {
    delete SimpleSingleton::m_singleton;
    SimpleSingleton::m_singleton = nullptr;
}
int SimpleSingleton::get_data() {
    return this->data;
}
void SimpleSingleton::set_data(int x) {
    this->data = x;
}
int SimpleSingleton::get_data_static() {
    return SimpleSingleton::data_static;
}
void SimpleSingleton::set_data_static(int x) {
    SimpleSingleton::data_static = x;
}
SimpleSingleton * SimpleSingleton::get_handle() {
    return SimpleSingleton::m_singleton;
}
