#include "AsioIOServicePool.h"
#include <iostream>
#include <thread>   // 确保 std::thread 可用

using namespace std;

AsioIOServicePool::AsioIOServicePool(std::size_t size)
    : _ioServices(size), _nextIOService(0) {
    // 为每个 io_context 创建 work_guard，防止 run() 在没有任务时退出
    for (std::size_t i = 0; i < size; ++i) {
        _works.emplace_back(boost::asio::make_work_guard(_ioServices[i]));
    }

    // 遍历多个 ioservice，创建多个线程，每个线程内部启动 ioservice
    for (std::size_t i = 0; i < _ioServices.size(); ++i) {
        _threads.emplace_back([this, i]() {
            _ioServices[i].run();
            });
    }
}

AsioIOServicePool::~AsioIOServicePool() {
    Stop();
    std::cout << "AsioIOServicePool destruct" << endl;
}

boost::asio::io_context& AsioIOServicePool::GetIOService() {
    auto& service = _ioServices[_nextIOService++];
    if (_nextIOService == _ioServices.size()) {
        _nextIOService = 0;
    }
    return service;
}

void AsioIOServicePool::Stop() {
    // 因为仅仅清除 work_guard 并不能让 io_context 从 run 的状态中退出
    // 当 io_context 已经绑定了读或写的监听事件后，还需要手动 stop 该服务。
    for (auto& ioService : _ioServices) {
        ioService.stop();   // 停止 io_context，让 run() 尽快返回
    }

    // 清除所有 work_guard，释放资源（实际上 stop 已使 run 返回，clear 是安全清理）
    _works.clear();

    // 等待所有线程结束
    for (auto& t : _threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}