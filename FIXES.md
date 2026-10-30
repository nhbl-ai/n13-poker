# Thay đổi trong phiên bản 1.1

- Chọn tên người chơi trong phạm vi dữ liệu hiện có; bổ sung ghế Guest/Bot nếu thiếu tài khoản.
- Dùng `WinnerResult` có kích thước cố định để loại lỗi ghi ngoài buffer khi hòa.
- Hủy chọn người an toàn, không vào bàn với số người không hợp lệ.
- Nhận đúng sảnh, thùng, sảnh thùng, royal flush, sảnh A–5 và cù lũ từ hai bộ ba.
- So đủ lá phụ; Texas chỉ so 5 lá tốt nhất trong 7 lá.
- Hiển thị đầy đủ người hòa ở PVP và PVE.
- Xử lý đóng cửa sổ trong hoạt ảnh, đếm giờ, lượt chơi và màn kết quả.
- Ghi thống kê một lần mỗi ván; cập nhật tổng số trận trong PVE.
- Tách bảng kết quả để chữ và nút không bị lá bài che.
- Build bằng CMake/GCC và đóng gói bản Windows không phụ thuộc Visual Studio.

Giữ thứ tự chia bài, cách xáo, cách tính điểm bài 3 lá, các mức cược và các nhánh quyết định bot. Không suy đoán hoặc ghi lại các trận lịch sử mà phiên bản cũ đã bỏ sót.
