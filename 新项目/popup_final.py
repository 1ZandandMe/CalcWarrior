import time
import random
import tkinter as tk

# ---------- 可调参数 ----------
emojis = ["该喝水了 💧", "站起来走走 🚶", "看看窗外 🌳", "休息一下眼睛 👀",""]
interval_seconds = 1          # 每1秒弹一次
popup_duration_ms = 1000      # 每个窗口停留1秒（1000毫秒）
# -----------------------------

def create_popup():
    """创建一个带大号表情的弹窗，并设置定时关闭"""
    popup = tk.Tk()
    popup.title("嘿！你小子")
    popup.attributes('-topmost', True)   # 保持窗口在最前

    emoji = random.choice(emojis)
    label = tk.Label(popup, text=emoji, font=("Arial", 20))
    label.pack(padx=50, pady=50)

    # 调整窗口大小以适应内容
    popup.update_idletasks()
    width = popup.winfo_width()
    height = popup.winfo_height()
    # 可选：居中显示（如果不需要可以注释掉）
    x = (popup.winfo_screenwidth() // 2) - (width // 2)
    y = (popup.winfo_screenheight() // 2) - (height // 2)
    popup.geometry(f'{width}x{height}+{x}+{y}')

    # 定时关闭（单位：毫秒）
    popup.after(popup_duration_ms, popup.destroy)

    # 进入该窗口的事件循环（注意：这里会阻塞，但因为每个窗口都是独立的 Tk 实例，所以不影响后续循环）
    popup.mainloop()

# ---------- 主循环 ----------
print(f"🚀 弹窗程序已启动，每隔 {interval_seconds} 秒弹出一个随机表情。")
print("   按 Ctrl+C 终止程序（可能需要多按几次）。")
print("   注意：弹窗时会暂时阻塞终端，关闭窗口或等待自动关闭后继续循环。\n")

count = 0
try:
    while True:
        time.sleep(interval_seconds)
        count += 1
        print(f"🎈 弹出第 {count} 个窗口...")
        create_popup()
except KeyboardInterrupt:
    print("\n👋 程序已终止。")