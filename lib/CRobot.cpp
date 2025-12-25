#include "../lib/CRobot.h"
#include "../lib/NumMethod.h"
#include "../lib/Matrix.h"
#include <cmath>
#include <cstddef>
#include <functional>
#include <type_traits>
CRobot* pRobot = NULL; // Con trỏ toàn cục đến đối tượng robot





/**
 * Constructor - Khởi tạo robot
 * Tự động gọi initRobot() để cấu hình các tham số DH ban đầu
 */
CRobot::CRobot()
{
    initRobot();
    pRobot = this; // Gán con trỏ toàn cục đến đối tượng hiện tại
}

/**
 * Khởi tạo các tham số Denavit-Hartenberg cho robot
 * 
 * Cấu hình theo bảng DH:
 * ------------------------------------------------
 * | Khớp | a    | α    | d    | θ (biến)    |
 * ------------------------------------------------
 * | 0→1 | 0    | π/2  | L1   | Q1           |
 * | 1→2 | L2   | 0    | 0    | Q2           |
 * | 2→3 | L3   | 0    | 0    | Q3           |
 * ------------------------------------------------
 * 
 * Giá trị chiều dài:
 * - L1 = 17487 (chiều cao khớp đếu tiên)
 * - L2 = 15440 (chiều dài khớp thứ 2)
 * - L3 = 14431 (chiều dài khớp thứ 3)
 */
void CRobot::initRobot()
{
    // Initialize robot links with DH parameters according to DH table
    // Định nghĩa các chiều dài khớp
    double L1 = 17487;  // Chiều dài d của khớp 1
    double L2 = 15440;  // Chiều dài a của khớp 2
    double L3 = 14431;  // Chiều dài a của khớp 3

    // Link 0 (0→1): a=0, alpha=π/2, d=L1, theta=Q1 (biến)
    links[0].SetConstants(0, PI/2, 0, L1);
    
    // Link 1 (1→2): a=L2, alpha=0, d=0, theta=Q2 (biến)
    links[1].SetConstants(0, 0, L2, 0);
    
    // Link 2 (2→3): a=L3, alpha=0, d=0, theta=Q3 (biến)
    links[2].SetConstants(0, 0, L3, 0);
    
    // Link 3: không sử dụng trong bảng DH này
    links[3].SetConstants(0, 0, 0, 0);
    
    LTool = 0;  // Chiều dài công cụ đầu robot

}

/**
 * Giải bài toán Động học Thuận (Forward Kinematics)
 * 
 * MỤC ĐÍCH:
 * Tính toán vị trí end-effector (x, y, z) dựa trên các giá trị khớp đã cho
 * 
 * THUẬT TOÁN:
 * 1. Đặt vị trí end-effector trong hệ tọa độ local: pEn = [0, 0, -LTool, 1]^T
 * 2. Với mỗi điểm thời gian j:
 *    a. Đặt biến khớp cho các link dựa trên q[i][j]
 *    b. Tính ma trận biến đổi tích lũy: A0n = A0 * A1 * A2 * A3 * ... * An
 *    c. Biến đổi vị trí end-effector về hệ tọa độ gốc: pEx0 = A0n * pEn
 *    d. Lưu tọa độ (x, y, z) vào các mảng pEx, pEy, pEz
 * 3. In kết quả ra màn hình
 * 
 * KẾT QUẢ:
 * Các mảng pEx, pEy, pEz chứa tọa độ end-effector tại mỗi điểm thời gian
 */
void CRobot::solvingForwardKinematics()
{
// Khai báo các ma trận cần thiết
smatrix A0n,Ai;           // A0n: Ma trận biến đổi tích lũy từ gốc đến khớp n
                          // Ai: Ma trận biến đổi từ khớp i-1 đến khớp i
vectorm pEx0,pEn(4);      // pEn: Vị trí end-effector trong hệ tọa độ local
                          // pEx0: Vị trí end-effector trong hệ tọa độ gốc

// Định nghĩa vị trí end-effector trong hệ tọa độ local
// End-effector nằm dưới trục Z một khoảng bằng LTool
pEn[0]=0;        // X = 0 (nằm trên trục Z)
pEn[1]=0;        // Y = 0 (nằm trên trục Z)
pEn[2]=-LTool;   // Z = -LTool (chiều dài công cụ hướng xuống)
pEn[3]=1;        // Thành phần đồng nhất        // Thành phần đồng nhất

// Vòng lặp qua tất cả các điểm thời gian trong quỹ đạo
for(int j=0;j<q[0].size();j++)
{
// ==== BƯỚC 1: ĐẶT BIẾN KHỚP CHO TỪ NG LINK ====
// Đặt các biến khớp theo bảng DH (theta là biến)
// Set joint variables according to DH table
// Link 0 (0→1): theta = Q1 (variable)
links[0].SetParameters(q[0][j], 0, 0, 0);

// Link 1 (1→2): theta = Q2 (variable)
links[1].SetParameters(q[1][j], 0, 0, 0);

// Link 2 (2→3): theta = Q3 (variable)
links[2].SetParameters(q[2][j], 0, 0, 0);

// Link 3: not used but kept for compatibility
links[3].SetParameters(0, 0, 0, 0);

// ==== BƯỚC 2: TÍNH MA TRẬN BIẾN ĐỔI TÍCH LŨY ====
// Lấy ma trận DH của link đầu tiên (link 0)
A0n = links[0].GetDHmatrix();

// Nhân dồn các ma trận DH của các link tiếp theo
// A0n = A0 * A1 * A2 * ... * An
for (int i=1;i<NUMBER_LINKS;i++)
{
    Ai=links[i].GetDHmatrix();  // Lấy ma trận DH của link i
    A0n=A0n*Ai;                 // Nhân tích lũy: A0n = A0n * Ai                 // Nhân tích lũy: A0n = A0n * Ai

}

// ==== BƯỚC 3: BIẾN ĐỔI VỊ TRÍ END-EFFECTOR ====
// Biến đổi vị trí end-effector từ hệ local sang hệ gốc
pEx0=A0n*pEn;  // pEx0 = A0n * pEn = [x, y, z, 1]^T

// Lưu tọa độ (x, y, z) vào mảng
pEx[j]=pEx0[0];  // Tọa độ X
pEy[j]=pEx0[1];  // Tọa độ Y
pEz[j]=pEx0[2];  // Tọa độ Z  // Tọa độ Z

}  // Kết thúc vòng lặp qua các điểm

// ==== BƯỚC 4: HIỂN THỊ KẾT QUẢ ====
// In các mảng tọa độ ra màn hình
std::cout<<"\nPosition of end-effector: "<<std::endl;
std::cout<<"px= ";
for(size_t i = 0; i < pEx.size(); i++) {
    std::cout << pEx[i] << " ";
}
std::cout << std::endl;
std::cout<<"py= ";
for(size_t i = 0; i < pEy.size(); i++) {
    std::cout << pEy[i] << " ";
}
std::cout << std::endl;
std::cout<<"pz= ";
for(size_t i = 0; i < pEz.size(); i++) {
    std::cout << pEz[i] << " ";
}
std::cout << std::endl;

}  // Kết thúc hàm solvingForwardKinematics

/**
 * Thiết lập số lượng điểm cho quỹ đạo
 * Cấp phát bộ nhớ cho các mảng lưu tọa độ và biến khớp
 * 
 * @param n: Số lượng điểm trên quỹ đạo
 */
void CRobot::SetNumPoint(const int& n)
{
    // Cấp phát bộ nhớ cho mảng tọa độ end-effector
    pEx.resize(n);  // Mảng tọa độ X
    pEy.resize(n);  // Mảng tọa độ Y
    pEz.resize(n);  // Mảng tọa độ Z
    
    // Cấp phát bộ nhớ cho mảng biến khớp của từng link
    for (int i = 0; i < NUMBER_LINKS; i++) {
        q[i].resize(n);  // Mỗi link có n giá trị khớp theo thời gian
    }
}

/**
 * Xóa toàn bộ dữ liệu đã lưu
 * Giải phóng bộ nhớ của các mảng tọa độ và biến khớp
 */
void CRobot::Clear()
{
    // Xóa mảng tọa độ end-effector
    pEx.clear();
    pEy.clear();
    pEz.clear();
    
    // Xóa mảng biến khớp của từng link
    for (int i = 0; i < NUMBER_LINKS; i++) {
        q[i].clear();
    }
}

/**
 * Thiết lập các biến khớp cho toàn bộ quỹ đạo
 * 
 * Tạo quỹ đạo với 101 điểm, các khớp thay đổi tuyến tính:
 * - Q1 (khớp 0): Từ 0° đến 90°
 * - Q2 (khớp 1): Từ 0° đến 180°
 * - Q3 (khớp 2): Từ -90° đến +90°
 */
void CRobot::SetVariable()
{
    // Set joint variables for trajectory with 101 points
    int NumberPoints=101;
    SetNumPoint(NumberPoints);
    
    for (int j=0; j<NumberPoints; j++) {
        // Q1: Joint 1 rotates from -150 to 150 (-150° to 150°)
        q[0][j] = -150 * PI/180 + j * 300 * PI/180 / (NumberPoints-1);
        
        // Q2: Joint 2 rotates from 10 to 45 (10° to 45°)
        q[1][j] = 10 * PI/180 + j * 35 * PI/180 / (NumberPoints-1);
        
        // Q3: Joint 3 rotates from 0 to -30 (0° to -30°)
        q[2][j] = 0 * PI/180 + j * -30 * PI/180 / (NumberPoints-1);
        
        // q[3]: not used in DH table but kept for compatibility
        q[3][j] = 0;
    }
}

/**
 * Xuất quỹ đạo robot ra file CSV
 * File CSV có thể được mở bằng Excel hoặc sử dụng để vẽ đồ thị
 * 
 * Định dạng file:
 * Point,X,Y,Z,Q1_deg,Q2_deg,Q3_deg,Q1_rad,Q2_rad,Q3_rad
 * 0,x0,y0,z0,q1_0,q2_0,q3_0,...
 * 
 * @param filename: Tên file CSV cần xuất
 */
void CRobot::ExportTrajectoryToCSV(const std::string& filename)
{
    // Mở file để ghi
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Lỗi: Không thể tạo file " << filename << std::endl;
        return;
    }
    
    // Ghi header (tiêu đề các cột)
    file << "Point,X,Y,Z,Q1_deg,Q2_deg,Q3_deg,Q1_rad,Q2_rad,Q3_rad\n";
    
    // Ghi dữ liệu từng điểm
    for(size_t i = 0; i < pEx.size(); i++) {
        file << i << ","                           // Số thứ tự điểm
             << pEx[i] << ","                       // Tọa độ X
             << pEy[i] << ","                       // Tọa độ Y
             << pEz[i] << ","                       // Tọa độ Z
             << (q[0][i] * 180.0 / PI) << ","      // Q1 (độ)
             << (q[1][i] * 180.0 / PI) << ","      // Q2 (độ)
             << (q[2][i] * 180.0 / PI) << ","      // Q3 (độ)
             << q[0][i] << ","                      // Q1 (radian)
             << q[1][i] << ","                      // Q2 (radian)
             << q[2][i] << "\n";                    // Q3 (radian)
    }
    
    file.close();
    
    // Thông báo thành công
    std::cout << "\n========================================\n";
    std::cout << "✓ Đã xuất quỹ đạo ra file: " << filename << std::endl;
    std::cout << "✓ Tổng số điểm: " << pEx.size() << std::endl;
    std::cout << "========================================\n";
    std::cout << "\nBạn có thể:\n";
    std::cout << "- Mở file bằng Excel để xem dữ liệu\n";
    std::cout << "- Vẽ đồ thị 3D bằng Python/MATLAB\n";
    std::cout << "- Phân tích quỹ đạo chuyển động\n";
}

// Hàm tính Jacobian cho phương pháp Newton-Raphson
void funcJacobi(const smatrix & F,vectorm& F,const vectorm& x)
{
    F.SetSize(GetSize(x));
    F.SetSize(GetSize(x));

    double c2 = cos(x[1]);
    double s2 = sin(x[1]);
    double c23 = cos(x[1]+x[2]);
    double s23 = sin(x[1]+x[2]);

    double a2 = pRobot->links[2].a; // Chiều dài khớp 2
    double a3 = pRobot->links[3].a; // Chiều dài khớp 3

    F(0,0) = 0;
    F(0,1) = -a2*s2 - a3*s23;
    F(0,2) = -a3*s23;

    F(1,0) = 0;
    F(1,1) = a2*c2 + a3*c23;
    F(1,2) = a3*c23;

    F(2,0) = 1;
    F(2,1) = 0;
    F(2,2) = 0;

    F(0) = a2*c2 + a3*c23 - pRobot->pEx[pRobot->idCurrentPoint];
    F(1) = a2*s2 + a3*s23 - pRobot->pEy[pRobot->idCurrentPoint];
    F(2) = x[0] - pRobot->LTool-pRobot->pEz[pRobot->idCurrentPoint];

}


void CRobot::SetEndPoint()
{
    // TODO: Add your implementation code here.
    int numSegments = 100;
    SetNumPoint(numSegments);

    double x0 = 400;
    double y0 = 400;
    double r = 100;

    for (int j = 0; j< numSegments+1; j++) 
    {
    //toa do diem cuoi
        pEx[j] = x0 + r * sin(2 * PI * j / numSegments);
        pEy[j] = y0 + r * cos(2 * PI * j / numSegments);
        pEz[j] = 100+ j*100/numSegments;
    }
}

void CRobot::SolvingInverKinematicPosition()
{
    // TODO: Add your implementation code here.
    vectorm x(NUMBER_LINKS-1);
    x(0)=100;
    x(1)=PI/4;
    x(2)=PI/6;

    double eps=0.0001;
    int maxloop=500;
    for (int j=0; j<pEx.size(); j++) 
    {
        idCurrentPoint=j;
        if (Newton_Raphson(x, funcJacobi,eps, maxloop)==0) {
        q[0][j]=0;
        for(int i=1;i<NUMBER_LINKS;i++)
            q[i][j]=x(i-1);
        }
    }
}
