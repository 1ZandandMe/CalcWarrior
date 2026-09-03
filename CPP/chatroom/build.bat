@echo off
chcp 65001 > nul
echo === CalcWarrior Encrypted Chat Builder ===
echo.

echo [1/1] Compiling server.cpp + crypto_utils.cpp...
g++ -std=c++17 -O2 server.cpp crypto_utils.cpp -o server.exe ^
  -I D:/msys64/ucrt64/include ^
  -L D:/msys64/ucrt64/lib ^
  -lsodium ^
  -lws2_32 -lpthread

if %errorlevel% neq 0 (
    echo [ERR] Compilation failed.
    pause
    exit /b 1
)
echo   ^> server.exe
echo.
echo === Build done! ===
echo Run: .\server.exe   ^(or double-click run.bat^)
echo Browser: http://localhost:8080
echo.
echo All messages end-to-end encrypted. Server never sees plaintext.
echo.
pause
