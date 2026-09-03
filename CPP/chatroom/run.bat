@echo off
chcp 65001 > nul
:: ===== CalcWarrior 聊天室 — 启动脚本（双击运行） =====
title CalcWarrior Chat

:: 自动获取本机局域网 IP，方便局域网其他设备访问
for /f "tokens=2 delims=:" %%i in ('ipconfig ^| findstr /c:"IPv4" /c:"IP Address"') do (
    set IP=%%i
    goto :found
)
:found
set IP=%IP: =%

echo === CalcWarrior Chat Server ===
echo.
echo Starting...
echo.
echo Local:   http://localhost:8080    ← 本机打开
echo LAN:     http://%IP%:8080         ← 局域网其他设备打开
echo.
echo Share LAN address with others on your network.
echo Close this window to stop the server.
echo.

:: 后台启动服务器（不阻塞命令行）
start /b server.exe > nul 2>&1

:: 等服务器就绪再打开浏览器
timeout /t 2 /nobreak > nul

:: 自动打开浏览器
start http://localhost:8080

:: 保持窗口，按任意键停止服务器
echo Press any key to stop the server...
pause > nul

:: 清理：关闭服务器进程
taskkill /f /im server.exe > nul 2>&1
