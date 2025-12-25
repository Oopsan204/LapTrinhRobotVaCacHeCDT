# HƯỚNG DẪN CÀI ĐẶT VÀ CHẠY OPENGL VISUALIZATION

## Yêu cầu:
- Visual Studio 2019/2022
- FreeGLUT library cho Windows

## BƯỚC 1: Tải và cài đặt FreeGLUT

### Cách 1: Tải FreeGLUT từ website chính thức
1. Tải FreeGLUT từ: https://www.transmissionzero.co.uk/software/freeglut-devel/
2. Giải nén file zip
3. Copy các file:
   - `freeglut/include/GL/*` → `C:\Program Files (x86)\Windows Kits\10\Include\<version>\um\GL\`
   - `freeglut/lib/x64/*` → `C:\Program Files (x86)\Windows Kits\10\Lib\<version>\um\x64\`
   - `freeglut/bin/x64/freeglut.dll` → `C:\Windows\System32\`

### Cách 2: Sử dụng vcpkg (Khuyến nghị)
```bash
# Cài đặt vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Cài đặt FreeGLUT
.\vcpkg install freeglut:x64-windows

# Tích hợp với Visual Studio
.\vcpkg integrate install
```

## BƯỚC 2: Cấu hình Project trong Visual Studio

1. **Mở project Ex2.1.vcxproj**

2. **Thêm các file mới vào project:**
   - Right-click project → Add → Existing Item
   - Chọn: `RobotVisualization.h` và `RobotVisualization.cpp`

3. **Cấu hình Linker:**
   - Right-click project → Properties
   - Configuration: **All Configurations**
   - Platform: **x64**
   
   Đi đến: **Linker → Input → Additional Dependencies**
   - Thêm: `opengl32.lib;glu32.lib;freeglut.lib`

4. **Cấu hình Include Directories (nếu không dùng vcpkg):**
   - Đi đến: **C/C++ → General → Additional Include Directories**
   - Thêm đường dẫn đến thư mục `include` của FreeGLUT

5. **Cấu hình Library Directories (nếu không dùng vcpkg):**
   - Đi đến: **Linker → General → Additional Library Directories**
   - Thêm đường dẫn đến thư mục `lib/x64` của FreeGLUT

## BƯỚC 3: Build và chạy

1. **Build project:**
   - Chọn **x64** và **Debug** hoặc **Release**
   - Build → Build Solution (Ctrl+Shift+B)

2. **Chạy chương trình:**
   - Debug → Start Without Debugging (Ctrl+F5)

## BƯỚC 4: Sử dụng Visualization

Khi chương trình chạy:
- **Chuột trái + Kéo**: Xoay camera quanh quỹ đạo
- **Phím +/-**: Zoom in/out
- **Phím R**: Reset camera về vị trí mặc định
- **ESC**: Thoát

## Màu sắc trong Visualization:
- **Đỏ**: Trục X
- **Xanh lá**: Trục Y
- **Xanh dương**: Trục Z
- **Vàng**: Đường quỹ đạo
- **Xanh lá sáng**: Điểm bắt đầu
- **Đỏ sáng**: Điểm kết thúc
- **Gradient xanh-đỏ**: Các điểm trung gian

## Xử lý lỗi thường gặp:

### Lỗi 1: "Cannot open include file: 'GL/glut.h'"
**Giải pháp:** 
- Cài đặt FreeGLUT theo BƯỚC 1
- Kiểm tra Additional Include Directories trong Project Properties

### Lỗi 2: "unresolved external symbol __imp_glutInit"
**Giải pháp:**
- Thêm `opengl32.lib;glu32.lib;freeglut.lib` vào Linker Input
- Kiểm tra Additional Library Directories

### Lỗi 3: "freeglut.dll not found"
**Giải pháp:**
- Copy `freeglut.dll` vào thư mục chứa file .exe
- Hoặc copy vào `C:\Windows\System32\`

### Lỗi 4: Cửa sổ mở nhưng không hiển thị gì
**Giải pháp:**
- Kiểm tra dữ liệu robot đã được tính toán chưa
- Thử zoom out bằng phím `-`

## Tùy chỉnh:

Để thay đổi màu sắc, kích thước, hoặc tốc độ xoay camera, chỉnh sửa file `RobotVisualization.cpp`:
- Dòng 11-13: Góc và zoom mặc định
- Dòng 215-240: Màu sắc quỹ đạo và điểm
- Dòng 134-135: Giới hạn zoom

## Video demo:
Chương trình sẽ hiển thị:
1. Kết quả tính toán trong console
2. Cửa sổ 3D với quỹ đạo robot
3. Có thể xoay và zoom để xem từ nhiều góc độ

---
**Chúc bạn thành công!**
