# -*- coding: utf-8 -*-
"""
HelloWorldSource 的 Python 实现：生成消息。
"""
import time

_COUNT = 0

def generate() -> str:
    """生成一条 HelloWorld 消息。"""
    global _COUNT
    _COUNT += 1
    return f"Hello, World! #{_COUNT} from Python"
