#pragma once
#include <vector>
#include <boost/asio.hpp>
#include "Singleton.h"

class AsioIOServicePool : public Singleton<AsioIOServicePool>
{
    friend Singleton<AsioIOServicePool>;

public:
    using IOService = boost::asio::io_context;
    // 使用 executor_work_guard 替代弃用的 io_context::work
    using WorkGuard = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;

    ~AsioIOServicePool();
    AsioIOServicePool(const AsioIOServicePool&) = delete;
    AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;

    // 使用 round-robin 的方式返回一个 io_service
    boost::asio::io_context& GetIOService();
    void Stop();

private:
    AsioIOServicePool(std::size_t size = std::thread::hardware_concurrency());

    std::vector<IOService> _ioServices;
    std::vector<WorkGuard> _works;          // 直接存储 WorkGuard 对象
    std::vector<std::thread> _threads;
    std::size_t _nextIOService;
};