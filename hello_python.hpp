/*******************************************************************************
 * hello_pybind.hpp — Python 驱动的 HelloWorld FINS 节点
 *
 * 节点结构与原始 hello-world 完全一致，
 * 只有业务逻辑（生成消息、打印消息）改调 Python。
 ******************************************************************************/

#pragma once

#include <atomic>
#include <chrono>
#include <string>
#include <thread>

#include <fins/node.hpp>
#include "py_bridge.hpp"

// ──────────────── HelloPythonSource ────────────────

class HelloPythonSource : public fins::Node {
public:
  HelloPythonSource() = default;

  void define() override {
    set_name("HelloPythonSource");
    set_description("通过 Python 产生 HelloPython 消息");
    set_category("Tutorials");
    register_output<std::string>("str");
  }

  void initialize() override {
    logger->info("Source 初始化.");
    running_ = false;
  }

  void run() override {
    if (running_) return;
    running_ = true;

    worker_ = std::thread([this]() {
      logger->info("Source 线程已启动 (调 Python generate).");

      while (running_) {
        // ── 核心：调 Python 生成消息 ──
        std::string msg = py_bridge::generate_message();

        // ── 通过 FINS 管道发送 ──
        this->send("str", msg);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    });
  }

  void pause() override {
    running_ = false;
    if (worker_.joinable()) worker_.join();
    logger->info("Source 已暂停.");
  }

  void reset() override { logger->info("Source 重置."); }

private:
  std::thread worker_;
  std::atomic<bool> running_{false};
};

EXPORT_NODE(HelloPythonSource)

// ──────────────── HelloPythonPrinter ────────────────

class HelloPythonPrinter : public fins::Node {
public:
  HelloPythonPrinter() = default;

  void define() override {
    set_name("HelloPythonPrinter");
    set_description("通过 Python 打印接收到的消息");
    set_category("Tutorials");

    register_input<std::string>("str", &HelloPythonPrinter::receive_msg);
  }

  void initialize() override { logger->info("Printer 初始化."); }
  void run() override    { logger->info("Printer 运行."); }
  void pause() override  { logger->info("Printer 暂停."); }
  void reset() override  { logger->info("Printer 重置."); }

  void receive_msg(const std::string &msg, fins::AcqTime acq_time) {
    static size_t count = 0;
    static uint64_t total_latency = 0;

    total_latency += fins::latency_us(acq_time);

    // ── 核心：调 Python 处理消息 ──
    py_bridge::print_message(msg);

    if (++count >= 1000) {
      logger->info("收到: {}. 平均框架延迟: {:.1f} us",
                   msg, total_latency / 1000.0);
      count = 0;
      total_latency = 0;
    }
  }
};

EXPORT_NODE(HelloPythonPrinter)
