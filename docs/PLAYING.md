# N13 Poker — Windows portable

Giải nén toàn bộ thư mục, rồi mở `N13Poker.exe`. Không cần Visual Studio, GCC hoặc CMake để chơi.

Lần đầu: chọn Login → Register để tạo tài khoản, sau đó đăng nhập. Chọn Texas Hold’em (VS Player hoặc VS Bot), Poker 5 lá hoặc bài 3 lá và số người 2–6. PVP chơi luân phiên trên cùng một máy. Tiền trong game là điểm mô phỏng.

Giữ ảnh, font, âm thanh, `openal32.dll` và `resources.manifest` cạnh file exe. Đặt game trong thư mục có quyền ghi, chẳng hạn Documents.

Tài khoản và thống kê được lưu trong `users.txt`, `player.txt`, `Leaderboard.txt`. Gói phát hành bắt đầu bằng dữ liệu rỗng. Khi nâng cấp, sao lưu và giữ ba file dữ liệu cũ của bạn; không đưa chúng lên repo public.

Tài khoản này chỉ dùng cục bộ cho bản demo. Không dùng lại mật khẩu của tài khoản/dịch vụ khác.

Nhóm phát triển: Nguyen Gia, Nguyen Hoang Bao Long, Vo My Ngoc. Dự án môn học tại HCMUS.

Mã nguồn, hình ảnh và hướng dẫn build: https://github.com/nhbl-ai/n13-poker
