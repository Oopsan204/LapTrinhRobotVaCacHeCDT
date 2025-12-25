
#include <iostream>
#include "Clink.h"
#include "CRobot.h"
// #include "RobotVisualization.h"  // Tắt OpenGL visualization

int main(int argc, char** argv)
{
    std::cout << "=========================================\n";
    std::cout << "  Forward Kinematics Calculation\n";
    std::cout << "=========================================\n\n";
    
    // Bước 1: Tạo đối tượng robot và khởi tạo tham số DH
    CRobot rb;
    
    // Bước 2: Thiết lập quỹ đạo chuyển động (101 điểm)
    // Các biến khớp sẽ thay đổi tuyến tính theo thời gian
    rb.SetVariable();
    
    // Bước 3: Giải bài toán động học thuận
    // Tính toán vị trí end-effector cho tất cả các điểm
    rb.solvingForwardKinematics();
    
    // Bước 4: Hiển thị kết quả chi tiết cho từng điểm
    std::cout << "\n=========================================\n";
    std::cout << " ket qua cho tung diem\n";
    std::cout << "=========================================\n";
    
    for (int j = 0; j < rb.q[0].size(); j++) {
        std::cout << "\nPoint " << (j + 1) << ":\n";
        
        // Hiển thị giá trị các biến khớp (Joint variables)
        std::cout << "  Joint values: ";
        for (int i = 0; i < NUMBER_LINKS; i++) {
            std::cout << "q" << i << "=" << rb.q[i][j];
            if (i < NUMBER_LINKS - 1) std::cout << ", ";
        }
        
        // Hiển thị vị trí end-effector tương ứng
        std::cout << "\n  End-effector: "
                  << "(" << rb.pEx[j] << ", " 
                  << rb.pEy[j] << ", " 
                  << rb.pEz[j] << ")" << std::endl;
    }
    
    std::cout << "\n=========================================\n";
    std::cout << " done!\n";
    std::cout << "=========================================\n";
    
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
