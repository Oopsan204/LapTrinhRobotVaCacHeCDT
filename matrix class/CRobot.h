#pragma once
#include "Clink.h"
#include <vector>
#include <fstream>
#include <string>

// Định nghĩa số lượng khớp (links) của robot
#define NUMBER_LINKS 4

/**
 * Lớp CRobot - Đại diện cho một cánh tay robot
 * Robot bao gồm 4 khớp (links) và một công cụ (tool) ở đầu
 */
class CRobot
{
    public:
    // Mảng chứa 4 khớp (links) của robot
    Clink links[NUMBER_LINKS];
    
    // Chiều dài của công cụ gắn ở đầu robot (end-effector)
    double LTool; // length of tool
    
    // Vector lưu trữ tọa độ x, y, z của đầu robot (end-effector) theo thời gian
    vector<double> pEx,pEy,pEz; // position of end-effector
    
    // Mảng vector lưu trữ các biến khớp (joint variables) của từng link theo thời gian
    vector<double> q[NUMBER_LINKS]; // joint variables

    /**
     * Constructor - Hàm khởi tạo robot
     * Tự động gọi initRobot() để khởi tạo các thông số ban đầu
     */
    CRobot();
    
    /**
     * Khởi tạo các thông số ban đầu của robot
     * Thiết lập các tham số DH (Denavit-Hartenberg) cho từng khớp
     */
    void initRobot();
    
    /**
     * Giải bài toán động học thuận (Forward Kinematics)
     * Tính toán vị trí của đầu robot dựa trên các góc khớp đã cho
     * Sử dụng ma trận biến đổi DH để tính toán
     */
    void solvingForwardKinematics();
    
    /**
     * Thiết lập số lượng điểm cần tính toán cho quỹ đạo
     * @param n: số lượng điểm trên quỹ đạo
     */
    void SetNumPoint(const int& n);
    
    /**
     * Xóa tất cả dữ liệu đã lưu trữ
     * Làm sạch các vector chứa vị trí và biến khớp
     */
    void Clear();
    
    /**
     * Thiết lập các giá trị biến khớp cho toàn bộ quỹ đạo
     * Định nghĩa chuyển động của từng khớp theo thời gian
     */
    void SetVariable();
    
    /**
     * Xuất quỹ đạo robot ra file CSV
     * File chứa: điểm, tọa độ (x,y,z), góc các khớp (Q1,Q2,Q3)
     * @param filename: Tên file CSV cần xuất (ví dụ: "trajectory.csv")
     */
    void ExportTrajectoryToCSV(const std::string& filename);
};

