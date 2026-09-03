$oldPath = [Environment]::GetEnvironmentVariable('Path', 'User')
if ($oldPath -notlike '*D:\java\jdk-21.0.11*') {
    $newPath = $oldPath.TrimEnd(';') + ';D:\java\jdk-21.0.11\bin'
    [Environment]::SetEnvironmentVariable('Path', $newPath, 'User')
    Write-Host 'JDK added to user PATH'
} else {
    Write-Host 'JDK already in PATH'
}
