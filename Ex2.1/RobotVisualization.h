#pragma once
#include "CRobot.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/**
 * Lớp RobotVisualization - Hiển thị quỹ đạo robot bằng OpenGL
 * Vẽ quỹ đạo 3D của end-effector và hệ trục tọa độ
 */
class RobotVisualization
{
private:
    static CRobot* robot;           // Con trỏ đến robot
    static float angleX;            // Góc quay quanh trục X để xoay camera
    static float angleY;            // Góc quay quanh trục Y để xoay camera
    static float zoom;              // Mức độ zoom
    static int lastMouseX;          // Vị trí chuột trước đó (X)
    static int lastMouseY;          // Vị trí chuột trước đó (Y)
    static bool isRotating;         // Đang xoay camera hay không

public:
    /**
     * Khởi tạo visualization với robot
     * @param rb: Con trỏ đến đối tượng robot
     */
    static void Init(CRobot* rb);

    /**
     * Bắt đầu hiển thị cửa sổ OpenGL
     * @param argc: Số lượng tham số dòng lệnh
     * @param argv: Mảng tham số dòng lệnh
     */
    static void Start(int argc, char** argv);

private:
    // Các hàm callback của OpenGL
    static void Display();           // Vẽ scene
    static void Reshape(int w, int h); // Xử lý thay đổi kích thước cửa sổ
    static void Keyboard(unsigned char key, int x, int y); // Xử lý bàn phím
    static void Mouse(int button, int state, int x, int y); // Xử lý chuột
    static void MouseMotion(int x, int y); // Xử lý di chuyển chuột

    // Các hàm vẽ
    static void DrawAxes();          // Vẽ hệ trục tọa độ XYZ
    static void DrawTrajectory();    // Vẽ quỹ đạo end-effector
    static void DrawRobot(int pointIndex); // Vẽ robot tại điểm cụ thể
    static void DrawText(float x, float y, float z, const char* text); // Vẽ text
};
