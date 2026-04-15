# 导入所需库
import schedule
import time
import tkinter as tk
from tkinter import messagebox
import pystray
from PIL import Image, ImageDraw
import threading
import sys

# ---------------------- 可修改配置项 ----------------------
REMINDER_TIME = "23:00"  # 每天提醒时间，24小时制，固定为晚上11点
REMINDER_TEXT = "到点啦，该睡觉了！晚安～"  # 弹窗内容
WINDOW_TITLE = "睡眠提醒"  # 弹窗标题
TRAY_TOOLTIP = "睡眠提醒小工具"  # 托盘图标悬停显示的名称
# ---------------------------------------------------------

# ---------------------- 1. 弹窗功能实现 ----------------------
def show_reminder():
    """到点弹出置顶提醒窗口，带确定按钮"""
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口，只显示提示框
    root.attributes("-topmost", True)  # 窗口置顶，不被遮挡
    messagebox.showinfo(WINDOW_TITLE, REMINDER_TEXT)
    root.destroy()

# ---------------------- 2. 定时任务设置 ----------------------
def setup_schedule():
    """配置每天固定时间执行提醒，循环保持运行"""
    # 设置每天指定时间执行弹窗函数
    schedule.every().day.at(REMINDER_TIME).do(show_reminder)
    print(f"睡眠提醒已启动！每天{REMINDER_TIME}准时提醒，程序已进入后台运行")
    
    # 持续检查定时任务，不占用系统资源
    while True:
        schedule.run_pending()
        time.sleep(1)

# ---------------------- 3. 托盘图标功能（后台运行核心） ----------------------
def create_default_icon():
    """自动生成托盘图标，无需额外准备图片"""
    width, height = 64, 64
    # 生成蓝色背景+白色月亮的简约图标
    image = Image.new('RGB', (width, height), color=(30, 144, 255))
    draw = ImageDraw.Draw(image)
    draw.ellipse((16, 16, 48, 48), fill=(255, 255, 255))
    draw.ellipse((24, 12, 52, 44), fill=(30, 144, 255))
    return image

def on_exit(icon, item):
    """右键托盘退出程序时执行，彻底关闭进程"""
    icon.stop()
    sys.exit(0)

def setup_tray():
    """配置托盘图标和右键菜单"""
    icon = pystray.Icon(
        "sleep_reminder",
        create_default_icon(),
        TRAY_TOOLTIP,
        menu=pystray.Menu(
            pystray.MenuItem("退出程序", on_exit)
        )
    )
    icon.run()

# ---------------------- 4. 程序主入口 ----------------------
if __name__ == "__main__":
    # 定时任务放到独立线程运行，避免和托盘图标冲突
    schedule_thread = threading.Thread(target=setup_schedule, daemon=True)
    schedule_thread.start()
    # 主线程运行托盘图标，保持程序常驻
    setup_tray()