#include <iostream>
#include <string>
#include "singleton.h"

template<typename T>
bool check_same(std::string name_a, T data_a, std::string name_b, T data_b) {
    if (data_a == data_b) {
        std::cout << "Same! " << name_a << " and " << name_b
            << " are both: " << data_a << std::endl;
        return true;
    } else {
        std::cout << "NOT same! " << name_a << " is "  << data_a
            << ", and " << name_b << " is " << data_b << std::endl;
        return false;
    }
}

int try_simple_singleton() {
    // get singleton
    std::cout << "Get singleton" << std::endl;
    auto singleton_a = SimpleSingleton::get_singleton();
    auto singleton_b = SimpleSingleton::get_singleton();
    check_same(
            "singleton_a", singleton_a,
            "singleton_b", singleton_b);
    check_same(
            "singleton_a->get_handle()", singleton_a->get_handle(),
            "singleton_b->get_handle()", singleton_b->get_handle());
    check_same(
            "singleton_a->data", singleton_a->get_data(),
            "singleton_b->data", singleton_b->get_data());
    check_same(
            "singleton_a->data_static", singleton_a->get_data_static(),
            "singleton_b->data_static", singleton_b->get_data_static());

    // modify singleton_a
    std::cout << std::endl;
    std::cout << "Set data to 10" << std::endl;
    std::cout << "Set data_static to 100" << std::endl;
    singleton_a->set_data(10);
    singleton_a->set_data_static(100);
    check_same(
            "singleton_a->data", singleton_a->get_data(),
            "singleton_b->data", singleton_b->get_data());
    check_same(
            "singleton_a->data_static", singleton_a->get_data_static(),
            "singleton_b->data_static", singleton_b->get_data_static());

    // modify singleton_b
    std::cout << std::endl;
    std::cout << "Set data to 16" << std::endl;
    std::cout << "Set data_static to 160" << std::endl;
    singleton_b->set_data(16);
    singleton_b->set_data_static(160);
    check_same(
            "singleton_a->data", singleton_a->get_data(),
            "singleton_b->data", singleton_b->get_data());
    check_same(
            "singleton_a->data_static", singleton_a->get_data_static(),
            "singleton_b->data_static", singleton_b->get_data_static());

    // release singleton
    std::cout << std::endl;
    SimpleSingleton::release_singleton();
    std::cout << "Release singleton" << std::endl;
    std::cout << "singleton_a: " << singleton_a << std::endl;
    std::cout << "singleton_b: " << singleton_b << std::endl;
    // delete is called, but the memory is still there
    check_same(
            "singleton_a->get_handle()", singleton_a->get_handle(),
            "singleton_b->get_handle()", singleton_b->get_handle());
    check_same(
            "singleton_a->data", singleton_a->get_data(),
            "singleton_b->data", singleton_b->get_data());
    check_same(
            "singleton_a->data_static", singleton_a->get_data_static(),
            "singleton_b->data_static", singleton_b->get_data_static());
    singleton_a = nullptr;
    singleton_b = nullptr;
    // won't cause segmentation fault. get_handle return static member;
    singleton_b->get_handle();
    // won't cause segmentation fault. get_data_static return static member;
    check_same(
            "singleton_a->data_static", singleton_a->get_data_static(),
            "singleton_b->data_static", singleton_b->get_data_static());
    // // will cause segmentation fault!
    // check_same(
    //         "singleton_a->data", singleton_a->get_data(),
    //         "singleton_b->data", singleton_b->get_data());
    return 0;
}

int main() {
    return try_simple_singleton();
}
