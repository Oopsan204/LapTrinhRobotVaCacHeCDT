% Đọc và vẽ đồ thị quỹ đạo robot từ file CSV
clear all;
close all;
clc;

% Đọc dữ liệu từ file CSV
data = readmatrix('E:\hoctap\nam4_ky2\LTMPHCDT\BaiHocVoLong\chapter2\Ex2.1\robot_trajectory.csv');

% Kiểm tra số cột của dữ liệu
[rows, cols] = size(data);
fprintf('Số hàng: %d, Số cột: %d\n', rows, cols);

% Vẽ đồ thị dựa trên số cột
if cols == 2
    % Dữ liệu 2D (x, y)
    x = data(:, 1);
    y = data(:, 2);
    
    figure('Name', 'Robot Trajectory 2D', 'NumberTitle', 'off');
    plot(x, y, 'b-', 'LineWidth', 2);
    hold on;
    plot(x(1), y(1), 'go', 'MarkerSize', 10, 'MarkerFaceColor', 'g'); % Điểm bắt đầu
    plot(x(end), y(end), 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r'); % Điểm kết thúc
    grid on;
    xlabel('X (m)');
    ylabel('Y (m)');
    title('Quỹ đạo điểm cuối của Robot (2D)');
    legend('Quỹ đạo', 'Điểm bắt đầu', 'Điểm kết thúc');
    axis equal;
    
elseif cols == 3
    % Dữ liệu 3D (x, y, z)
    x = data(:, 1);
    y = data(:, 2);
    z = data(:, 3);
    
    figure('Name', 'Robot Trajectory 3D', 'NumberTitle', 'off');
    plot3(x, y, z, 'b-', 'LineWidth', 2);
    hold on;
    plot3(x(1), y(1), z(1), 'go', 'MarkerSize', 10, 'MarkerFaceColor', 'g'); % Điểm bắt đầu
    plot3(x(end), y(end), z(end), 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r'); % Điểm kết thúc
    grid on;
    xlabel('X (m)');
    ylabel('Y (m)');
    zlabel('Z (m)');
    title('Quỹ đạo điểm cuối của Robot (3D)');
    legend('Quỹ đạo', 'Điểm bắt đầu', 'Điểm kết thúc');
    axis equal;
    view(45, 30);
    
elseif cols >= 4
    % Dữ liệu có thời gian (time, x, y, z)
    time = data(:, 1);
    x = data(:, 2);
    y = data(:, 3);
    z = data(:, 4);
    
    % Vẽ quỹ đạo 3D
    figure('Name', 'Robot Trajectory 3D with Time', 'NumberTitle', 'off');
    subplot(2, 2, [1, 3]);
    plot3(x, y, z, 'b-', 'LineWidth', 2);
    hold on;
    plot3(x(1), y(1), z(1), 'go', 'MarkerSize', 10, 'MarkerFaceColor', 'g');
    plot3(x(end), y(end), z(end), 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
    grid on;
    xlabel('X (m)');
    ylabel('Y (m)');
    zlabel('Z (m)');
    title('Quỹ đạo điểm cuối của Robot (3D)');
    legend('Quỹ đạo', 'Điểm bắt đầu', 'Điểm kết thúc');
    axis equal;
    view(45, 30);
    
    % Vẽ toạ độ theo thời gian
    subplot(2, 2, 2);
    plot(time, x, 'r-', 'LineWidth', 1.5);
    hold on;
    plot(time, y, 'g-', 'LineWidth', 1.5);
    plot(time, z, 'b-', 'LineWidth', 1.5);
    grid on;
    xlabel('Thời gian (s)');
    ylabel('Vị trí (m)');
    title('Toạ độ theo thời gian');
    legend('X', 'Y', 'Z');
    
    % Vẽ quỹ đạo 2D (XY)
    subplot(2, 2, 4);
    plot(x, y, 'b-', 'LineWidth', 2);
    hold on;
    plot(x(1), y(1), 'go', 'MarkerSize', 8, 'MarkerFaceColor', 'g');
    plot(x(end), y(end), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
    grid on;
    xlabel('X (m)');
    ylabel('Y (m)');
    title('Quỹ đạo 2D (XY)');
    axis equal;
else
    error('Dữ liệu không hợp lệ!');
end

fprintf('Đã vẽ xong đồ thị quỹ đạo robot!\n');
