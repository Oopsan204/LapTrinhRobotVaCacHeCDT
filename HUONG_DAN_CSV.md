# HƯỚNG DẪN SỬ DỤNG FILE CSV

## 📋 Đã tạo thành công!

### ✅ Các file đã được tạo:
1. **CRobot.h** - Đã thêm hàm `ExportTrajectoryToCSV()`
2. **CRobot.cpp** - Implementation hàm xuất CSV
3. **Ex2.1.cpp** - Gọi hàm xuất CSV sau khi tính toán
4. **plot_trajectory.py** - Script Python vẽ đồ thị 3D

---

## 🚀 CÁCH SỬ DỤNG

### Bước 1: Build và chạy chương trình C++
```bash
# Trong Visual Studio
1. Build → Rebuild Solution (Ctrl+Shift+B)
2. Debug → Start Without Debugging (Ctrl+F5)
```

**Kết quả:** File `robot_trajectory.csv` sẽ được tạo trong thư mục:
```
e:\hoctap\nam4_ky2\LTMPHCDT\BaiHocVoLong\chapter2\x64\Debug\robot_trajectory.csv
```
hoặc
```
e:\hoctap\nam4_ky2\LTMPHCDT\BaiHocVoLong\chapter2\x64\Release\robot_trajectory.csv
```

### Bước 2: Xem file CSV bằng Excel
1. Mở file `robot_trajectory.csv` bằng Excel
2. Xem dữ liệu quỹ đạo với các cột:
   - **Point**: Số thứ tự điểm (0-100)
   - **X, Y, Z**: Tọa độ end-effector (mm)
   - **Q1_deg, Q2_deg, Q3_deg**: Góc các khớp (độ)
   - **Q1_rad, Q2_rad, Q3_rad**: Góc các khớp (radian)

### Bước 3: Vẽ đồ thị 3D bằng Python

#### Cài đặt Python packages (chỉ cần làm 1 lần):
```bash
pip install pandas matplotlib
```

#### Chạy script:
```bash
# Di chuyển file CSV vào thư mục chapter2
copy x64\Debug\robot_trajectory.csv .

# Chạy script Python
python plot_trajectory.py
```

**Kết quả:** 
- Cửa sổ hiển thị 2 đồ thị:
  1. **Quỹ đạo 3D** của end-effector
  2. **Góc các khớp** theo thời gian
- File ảnh `robot_trajectory_plot.png` được lưu

---

## 📊 Định dạng file CSV

```csv
Point,X,Y,Z,Q1_deg,Q2_deg,Q3_deg,Q1_rad,Q2_rad,Q3_rad
0,1234.56,789.01,2345.67,-150.00,10.00,0.00,-2.618,0.175,0.000
1,1240.12,792.34,2340.12,-147.00,10.35,-0.30,-2.566,0.181,-0.005
...
100,5678.90,1234.56,3456.78,150.00,45.00,-30.00,2.618,0.785,-0.524
```

---

## 🎨 Tùy chỉnh script Python

### Thay đổi màu sắc:
```python
# Trong plot_trajectory.py, dòng 24
ax1.plot(df['X'], df['Y'], df['Z'], 'r-', ...)  # r=đỏ, b=xanh, g=xanh lá
```

### Thay đổi kích thước điểm:
```python
# Dòng 27
ax1.scatter(..., s=50, ...)  # s=kích thước điểm
```

### Lưu với độ phân giải cao hơn:
```python
# Dòng 75
plt.savefig('robot_trajectory_plot.png', dpi=600, ...)  # dpi=600 thay vì 300
```

---

## 📈 Phân tích dữ liệu trong Python

Thêm code này vào `plot_trajectory.py` để phân tích thêm:

```python
# Tính khoảng cách giữa các điểm liên tiếp
df['Distance'] = np.sqrt(
    (df['X'].diff())**2 + 
    (df['Y'].diff())**2 + 
    (df['Z'].diff())**2
)

print(f"Tổng chiều dài quỹ đạo: {df['Distance'].sum():.2f} mm")
print(f"Khoảng cách trung bình: {df['Distance'].mean():.2f} mm")
```

---

## 🔧 Xử lý lỗi

### Lỗi: "Không tìm thấy file robot_trajectory.csv"
**Giải pháp:**
1. Kiểm tra file đã được tạo trong `x64\Debug\` hoặc `x64\Release\`
2. Copy file vào thư mục `chapter2` trước khi chạy Python script

### Lỗi: "ModuleNotFoundError: No module named 'pandas'"
**Giải pháp:**
```bash
pip install pandas matplotlib
# Hoặc nếu dùng conda:
conda install pandas matplotlib
```

### Lỗi: "tkinter not found"
**Giải pháp:** Cài Python đầy đủ từ python.org (có tkinter built-in)

---

## 📝 Ví dụ sử dụng trong MATLAB (tùy chọn)

```matlab
% Đọc file CSV
data = readtable('robot_trajectory.csv');

% Vẽ quỹ đạo 3D
figure;
plot3(data.X, data.Y, data.Z, 'b-', 'LineWidth', 2);
hold on;
scatter3(data.X(1), data.Y(1), data.Z(1), 100, 'g', 'filled');
scatter3(data.X(end), data.Y(end), data.Z(end), 100, 'r', 'filled');
xlabel('X (mm)'); ylabel('Y (mm)'); zlabel('Z (mm)');
title('Quỹ đạo Robot');
grid on;
```

---

## ✨ Ưu điểm của phương pháp CSV

✅ Không cần cài OpenGL/FreeGLUT  
✅ Dễ dàng chia sẻ và phân tích dữ liệu  
✅ Có thể mở bằng Excel, Python, MATLAB  
✅ Dễ tích hợp vào báo cáo  
✅ Có thể xuất nhiều lần với các cấu hình khác nhau  

---

**Chúc bạn thành công! 🎉**

Nếu có thắc mắc, hãy kiểm tra file CSV đã được tạo chưa bằng cách xem trong thư mục `x64\Debug\` sau khi chạy chương trình.
