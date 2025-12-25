# Script tự động cài đặt FreeGLUT cho Windows
# Chạy script này với quyền Administrator

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  CÀI ĐẶT FREEGLUT TỰ ĐỘNG" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Kiểm tra quyền Administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
    Write-Host "LỖI: Script cần chạy với quyền Administrator!" -ForegroundColor Red
    Write-Host "Hãy click chuột phải vào script và chọn 'Run as Administrator'" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Nhấn phím bất kỳ để thoát..."
    $null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
    exit
}

Write-Host "Đang kiểm tra vcpkg..." -ForegroundColor Yellow

# Kiểm tra vcpkg đã cài chưa
$vcpkgPath = "C:\vcpkg\vcpkg.exe"
$vcpkgInstalled = Test-Path $vcpkgPath

if ($vcpkgInstalled) {
    Write-Host "✓ vcpkg đã được cài đặt" -ForegroundColor Green
} else {
    Write-Host "✗ vcpkg chưa được cài đặt" -ForegroundColor Red
    Write-Host ""
    Write-Host "Bạn có muốn cài đặt vcpkg không? (Y/N): " -NoNewline -ForegroundColor Yellow
    $response = Read-Host
    
    if ($response -eq "Y" -or $response -eq "y") {
        Write-Host "Đang cài đặt vcpkg..." -ForegroundColor Yellow
        
        # Clone vcpkg repository
        Set-Location C:\
        git clone https://github.com/Microsoft/vcpkg.git
        
        if ($?) {
            Set-Location C:\vcpkg
            .\bootstrap-vcpkg.bat
            
            if ($?) {
                Write-Host "✓ vcpkg đã được cài đặt thành công!" -ForegroundColor Green
                $vcpkgInstalled = $true
            } else {
                Write-Host "✗ Lỗi khi bootstrap vcpkg" -ForegroundColor Red
                exit
            }
        } else {
            Write-Host "✗ Lỗi khi clone vcpkg repository" -ForegroundColor Red
            Write-Host "Hãy kiểm tra kết nối internet và cài đặt Git" -ForegroundColor Yellow
            exit
        }
    } else {
        Write-Host "Bỏ qua cài đặt vcpkg" -ForegroundColor Yellow
        exit
    }
}

Write-Host ""
Write-Host "Đang cài đặt FreeGLUT..." -ForegroundColor Yellow

# Cài đặt FreeGLUT thông qua vcpkg
Set-Location C:\vcpkg
.\vcpkg install freeglut:x64-windows

if ($?) {
    Write-Host "✓ FreeGLUT đã được cài đặt!" -ForegroundColor Green
    Write-Host ""
    Write-Host "Đang tích hợp với Visual Studio..." -ForegroundColor Yellow
    .\vcpkg integrate install
    
    if ($?) {
        Write-Host "✓ Tích hợp thành công!" -ForegroundColor Green
    } else {
        Write-Host "✗ Lỗi khi tích hợp với Visual Studio" -ForegroundColor Red
    }
} else {
    Write-Host "✗ Lỗi khi cài đặt FreeGLUT" -ForegroundColor Red
    exit
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  CÀI ĐẶT HOÀN TẤT!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Bước tiếp theo:" -ForegroundColor Yellow
Write-Host "1. Mở Visual Studio" -ForegroundColor White
Write-Host "2. Build project Ex2.1" -ForegroundColor White
Write-Host "3. Chạy chương trình (Ctrl+F5)" -ForegroundColor White
Write-Host ""
Write-Host "Nhấn phím bất kỳ để thoát..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
