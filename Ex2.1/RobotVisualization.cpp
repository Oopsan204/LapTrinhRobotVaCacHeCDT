#include "RobotVisualization.h"
#include <cmath>
#include <string>

// Khởi tạo các biến static
CRobot* RobotVisualization::robot = nullptr;
float RobotVisualization::angleX = 30.0f;
float RobotVisualization::angleY = 45.0f;
float RobotVisualization::zoom = 50000.0f;
int RobotVisualization::lastMouseX = 0;
int RobotVisualization::lastMouseY = 0;
bool RobotVisualization::isRotating = false;

/**
 * Khởi tạo visualization với robot
 */
void RobotVisualization::Init(CRobot* rb)
{
    robot = rb;
}

/**
 * Bắt đầu hiển thị cửa sổ OpenGL
 */
void RobotVisualization::Start(int argc, char** argv)
{
    // Khởi tạo GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot End-Effector Trajectory Visualization");

    // Thiết lập OpenGL
    glEnable(GL_DEPTH_TEST);        // Bật depth test để vẽ 3D đúng
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Màu nền xanh đậm
    glEnable(GL_LINE_SMOOTH);       // Làm mượt đường line
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(2.0f);

    // Đăng ký các callback functions
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMotionFunc(MouseMotion);

    // In hướng dẫn sử dụng
    std::cout << "\n========================================\n";
    std::cout << "  HƯỚNG DẪN SỬ DỤNG\n";
    std::cout << "========================================\n";
    std::cout << "  Chuột trái + Kéo: Xoay camera\n";
    std::cout << "  Scroll/+/-: Zoom in/out\n";
    std::cout << "  R: Reset camera\n";
    std::cout << "  ESC: Thoát\n";
    std::cout << "========================================\n\n";

    // Bắt đầu vòng lặp render
    glutMainLoop();
}

/**
 * Hàm Display - Vẽ toàn bộ scene
 */
void RobotVisualization::Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Thiết lập camera
    gluLookAt(
        zoom * cos(angleY * PI / 180.0) * cos(angleX * PI / 180.0),  // Eye X
        zoom * sin(angleX * PI / 180.0),                              // Eye Y
        zoom * sin(angleY * PI / 180.0) * cos(angleX * PI / 180.0),  // Eye Z
        0.0, 0.0, 0.0,  // Center (nhìn vào gốc tọa độ)
        0.0, 1.0, 0.0   // Up vector
    );

    // Vẽ các thành phần
    DrawAxes();
    DrawTrajectory();

    // Swap buffers
    glutSwapBuffers();
}

/**
 * Hàm Reshape - Xử lý thay đổi kích thước cửa sổ
 */
void RobotVisualization::Reshape(int w, int h)
{
    if (h == 0) h = 1;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Thiết lập perspective projection
    gluPerspective(45.0, (double)w / (double)h, 100.0, 200000.0);
    
    glMatrixMode(GL_MODELVIEW);
}

/**
 * Hàm Keyboard - Xử lý phím bấm
 */
void RobotVisualization::Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC - Thoát
        exit(0);
        break;
    case 'r':
    case 'R': // Reset camera
        angleX = 30.0f;
        angleY = 45.0f;
        zoom = 50000.0f;
        glutPostRedisplay();
        break;
    case '+':
    case '=': // Zoom in
        zoom *= 0.9f;
        if (zoom < 5000.0f) zoom = 5000.0f;
        glutPostRedisplay();
        break;
    case '-':
    case '_': // Zoom out
        zoom *= 1.1f;
        if (zoom > 150000.0f) zoom = 150000.0f;
        glutPostRedisplay();
        break;
    }
}

/**
 * Hàm Mouse - Xử lý click chuột
 */
void RobotVisualization::Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            isRotating = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP)
        {
            isRotating = false;
        }
    }
}

/**
 * Hàm MouseMotion - Xử lý kéo chuột
 */
void RobotVisualization::MouseMotion(int x, int y)
{
    if (isRotating)
    {
        // Tính độ thay đổi
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;

        // Cập nhật góc
        angleY += dx * 0.5f;
        angleX += dy * 0.5f;

        // Giới hạn angleX
        if (angleX > 89.0f) angleX = 89.0f;
        if (angleX < -89.0f) angleX = -89.0f;

        // Cập nhật vị trí chuột
        lastMouseX = x;
        lastMouseY = y;

        // Yêu cầu vẽ lại
        glutPostRedisplay();
    }
}

/**
 * Vẽ hệ trục tọa độ XYZ
 */
void RobotVisualization::DrawAxes()
{
    glLineWidth(3.0f);
    glBegin(GL_LINES);

    // Trục X - Màu đỏ
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(15000.0f, 0.0f, 0.0f);

    // Trục Y - Màu xanh lá
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 15000.0f, 0.0f);

    // Trục Z - Màu xanh dương
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 15000.0f);

    glEnd();
    glLineWidth(2.0f);
}

/**
 * Vẽ quỹ đạo end-effector
 */
void RobotVisualization::DrawTrajectory()
{
    if (!robot || robot->pEx.empty()) return;

    // Vẽ đường quỹ đạo
    glLineWidth(2.5f);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 0.0f); // Màu vàng
    
    for (size_t i = 0; i < robot->pEx.size(); i++)
    {
        glVertex3f(
            static_cast<float>(robot->pEx[i]),
            static_cast<float>(robot->pEy[i]),
            static_cast<float>(robot->pEz[i])
        );
    }
    glEnd();

    // Vẽ các điểm trên quỹ đạo
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    
    for (size_t i = 0; i < robot->pEx.size(); i++)
    {
        // Gradient màu từ xanh lá (đầu) sang đỏ (cuối)
        float t = static_cast<float>(i) / static_cast<float>(robot->pEx.size() - 1);
        glColor3f(t, 1.0f - t, 0.3f);
        
        glVertex3f(
            static_cast<float>(robot->pEx[i]),
            static_cast<float>(robot->pEy[i]),
            static_cast<float>(robot->pEz[i])
        );
    }
    glEnd();

    // Đánh dấu điểm đầu và điểm cuối
    glPointSize(12.0f);
    glBegin(GL_POINTS);
    
    // Điểm đầu - Màu xanh lá sáng
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(
        static_cast<float>(robot->pEx[0]),
        static_cast<float>(robot->pEy[0]),
        static_cast<float>(robot->pEz[0])
    );
    
    // Điểm cuối - Màu đỏ sáng
    glColor3f(1.0f, 0.0f, 0.0f);
    size_t last = robot->pEx.size() - 1;
    glVertex3f(
        static_cast<float>(robot->pEx[last]),
        static_cast<float>(robot->pEy[last]),
        static_cast<float>(robot->pEz[last])
    );
    
    glEnd();

    // Hiển thị thông tin
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Thông tin số điểm
    std::string info = "Points: " + std::to_string(robot->pEx.size());
    glRasterPos3f(5000.0f, 12000.0f, 0.0f);
    for (char c : info) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Thông tin điểm đầu
    std::string startInfo = "Start (Green)";
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos3f(5000.0f, 11000.0f, 0.0f);
    for (char c : startInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Thông tin điểm cuối
    std::string endInfo = "End (Red)";
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f(5000.0f, 10000.0f, 0.0f);
    for (char c : endInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}
