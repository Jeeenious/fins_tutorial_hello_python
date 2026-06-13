# -*- coding: utf-8 -*-
"""
HelloWorldPrinter 的 Python 实现：打印消息。
"""
import time as _time

_LAST_LOG = ""
_LOG_COUNT = 0

def print_msg(msg: str) -> None:
    """打印接收到的消息。"""
    global _LAST_LOG, _LOG_COUNT
    _LAST_LOG = msg
    _LOG_COUNT += 1
    # 每 1000 条输出一次统计
    if _LOG_COUNT % 1000 == 0:
        print(f"[Python] 已接收 {_LOG_COUNT} 条消息，最新: {msg}")
