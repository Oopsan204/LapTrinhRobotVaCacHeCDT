# 🤖 ROBOT FORWARD KINEMATICS VISUALIZATION

## 📋 Mô tả dự án
Chương trình tính toán và hiển thị **quỹ đạo 3D** của end-effector robot 3 khớp sử dụng:
- **Phương pháp Denavit-Hartenberg (DH)** để tính động học thuận
- **OpenGL/FreeGLUT** để vẽ quỹ đạo 3D tương tác

## 🎯 Tính năng

### 1. Tính toán động học thuận
- Giải bài toán Forward Kinematics cho robot 3 khớp
- Tính toán 101 điểm trên quỹ đạo
- Hiển thị chi tiết vị trí end-effector và giá trị các khớp

### 2. Visualization 3D tương tác
- ✅ Vẽ quỹ đạo 3D với đường cong mượt mà
- ✅ Hiển thị hệ trục tọa độ XYZ
- ✅ Đánh dấu điểm bắt đầu (xanh) và kết thúc (đỏ)
- ✅ Gradient màu sắc cho các điểm trung gian
- ✅ Xoay camera bằng chuột
- ✅ Zoom in/out
- ✅ Reset camera

## 🚀 Cài đặt nhanh

### Yêu cầu hệ thống:
- Windows 10/11
- Visual Studio 2019/2022
- Git (để cài vcpkg)

### Bước 1: Cài đặt FreeGLUT

#### Cách tự động (Khuyến nghị):
```powershell
# Chạy PowerShell với quyền Administrator
Set-ExecutionPolicy Bypass -Scope Process
.\Install-FreeGLUT.ps1
```

#### Cách thủ công:
Xem chi tiết trong file `HUONG_DAN_CAI_DAT_OPENGL.md`

### Bước 2: Build project
1. Mở `chapter2.sln` trong Visual Studio
2. Chọn **x64** và **Debug** (hoặc Release)
3. Build Solution (Ctrl+Shift+B)

### Bước 3: Chạy
- Start Without Debugging (Ctrl+F5)
- Cửa sổ console sẽ hiển thị kết quả tính toán
- Cửa sổ 3D OpenGL sẽ hiển thị quỹ đạo

## 🎮 Điều khiển

| Phím/Chuột | Chức năng |
|------------|-----------|
| Chuột trái + Kéo | Xoay camera |
| Phím `+` hoặc `=` | Zoom in |
| Phím `-` hoặc `_` | Zoom out |
| Phím `R` | Reset camera về vị trí mặc định |
| Phím `ESC` | Thoát chương trình |

## 📊 Thông tin hiển thị

### Màu sắc:
- 🔴 **Đỏ**: Trục X
- 🟢 **Xanh lá**: Trục Y
- 🔵 **Xanh dương**: Trục Z
- 🟡 **Vàng**: Đường quỹ đạo
- 🟢 **Điểm xanh lớn**: Điểm bắt đầu
- 🔴 **Điểm đỏ lớn**: Điểm kết thúc
- 🌈 **Gradient**: Các điểm trung gian (xanh → đỏ)

## 📐 Thông số Robot

### Bảng DH Parameters:
| Khớp | a | α | d | θ (biến) |
|------|---|---|---|----------|
| 0→1 | 0 | π/2 | 17487 | Q1 |
| 1→2 | 15440 | 0 | 0 | Q2 |
| 2→3 | 14431 | 0 | 0 | Q3 |

### Quỹ đạo (101 điểm):
- **Q1**: 0° → 90°
- **Q2**: 0° → 180°
- **Q3**: -90° → 90°

## 📁 Cấu trúc dự án

```
chapter2/
├── Ex2.1/
│   ├── CRobot.h              # Header file robot
│   ├── CRobot.cpp            # Implementation robot
│   ├── Clink.h               # Header file khớp
│   ├── Clink.cpp             # Implementation khớp
│   ├── RobotVisualization.h  # ✨ Header OpenGL visualization
│   ├── RobotVisualization.cpp# ✨ Implementation visualization
│   ├── Ex2.1.cpp             # Main program
│   └── Ex2.1.vcxproj         # Visual Studio project
├── matrix class/
│   ├── Matrix.h              # Thư viện ma trận
│   └── Matrix.cpp
├── Transformations/
│   ├── Transformations.h     # Các phép biến đổi 3D
│   └── Transformations.cpp
├── Install-FreeGLUT.ps1      # ✨ Script cài đặt tự động
├── HUONG_DAN_CAI_DAT_OPENGL.md # Hướng dẫn chi tiết
└── chapter2.sln              # Solution file
```

## 🔧 Xử lý lỗi

### Lỗi build:
```
Error: Cannot open include file: 'GL/glut.h'
```
**Giải pháp**: Chạy script `Install-FreeGLUT.ps1` hoặc cài FreeGLUT thủ công

### Lỗi khi chạy:
```
Error: freeglut.dll not found
```
**Giải pháp**: Copy `freeglut.dll` vào thư mục chứa file `.exe`

### Cửa sổ trắng:
**Giải pháp**: Thử zoom out bằng phím `-` nhiều lần

## 📸 Screenshot (Dự kiến)

Khi chạy thành công, bạn sẽ thấy:
- Hệ trục tọa độ 3D (đỏ-xanh-xanh dương)
- Đường quỹ đạo màu vàng
- Điểm bắt đầu (xanh lá) và kết thúc (đỏ)
- Các điểm trung gian với gradient màu

## 🎓 Tài liệu tham khảo

- [Denavit-Hartenberg Parameters](https://en.wikipedia.org/wiki/Denavit%E2%80%93Hartenberg_parameters)
- [FreeGLUT Documentation](http://freeglut.sourceforge.net/)
- [OpenGL Tutorial](https://www.opengl.org/)

## 📝 Ghi chú

- Quỹ đạo được tính toán dựa trên phương pháp DH chuẩn
- Tất cả code đã được comment chi tiết bằng tiếng Việt
- Có thể tùy chỉnh màu sắc và số điểm trong code

## 👨‍💻 Tác giả

Dự án học tập - Môn Lập trình Máy tính Phục vụ Cơ Điện Tử

---

**Chúc bạn thành công! 🎉**

Nếu gặp vấn đề, hãy xem file `HUONG_DAN_CAI_DAT_OPENGL.md` để biết thêm chi tiết.
