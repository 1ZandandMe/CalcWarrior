# 导入所需库：schedule做定时任务，time控制循环，tkinter做弹窗（Python自带，无需安装）
import time
import sys
import tkinter as tk
from tkinter import messagebox

import schedule

# 在 Windows 下隐藏控制台窗口（运行 exe 时只显示弹窗）
if sys.platform == "win32":
    try:
        import ctypes

        hwnd = ctypes.windll.kernel32.GetConsoleWindow()
        if hwnd:
            ctypes.windll.user32.ShowWindow(hwnd, 0)  # 0 = SW_HIDE
    except Exception:
        pass

# ---------------------- 可修改配置项 ----------------------
TEST_DELAY_SECONDS = 0.01  # 测试用：运行后多少秒弹窗，默认60秒=1分钟，方便测试
REMINDER_TEXT = "到点啦，该睡觉了！晚安～"  # 弹窗显示内容
# ---------------------------------------------------------

# 定义弹窗函数：到时间自动执行，弹出提醒
def show_reminder():
    # 创建tkinter主窗口
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口，只显示提示框，不出现空白窗口
    root.attributes("-topmost", True)  # 窗口置顶，不会被其他软件挡住
    messagebox.showinfo("睡眠提醒", REMINDER_TEXT)  # 弹出带「确定」按钮的提示框
    root.destroy()  # 关闭窗口，释放资源

# 测试定时任务：启动后延迟指定时间触发弹窗
schedule.every(TEST_DELAY_SECONDS).seconds.do(show_reminder)

# 程序主循环：保持运行，持续检查定时任务
while True:
    schedule.run_pending()  # 执行所有到点的任务
    time.sleep(1)  # 每次检查暂停1秒，CPU占用几乎为0，不影响电脑性能