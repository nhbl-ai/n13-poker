# Kiểm thử phiên bản 1.1

Nền tảng kiểm thử: Windows x64; GCC 8.1.0/MinGW-w64; CMake 3.31.6; SFML 2.6.2.

## Kiểm thử tự động

| CTest | Phạm vi |
|---|---|
| `logic_regression` | Bộ bài 52 lá, thứ tự chia, điểm bài 3 lá, phân hạng, thắng/hòa và xáo bài |
| `bug_regression` | Các bộ bài từng chấm sai, nhiều đôi/hai bộ ba, lá phụ, buffer có trang nhớ bảo vệ, ghế Guest/Bot và đầu vào hủy/thiếu bài |
| `poker_exhaustive` | Duyệt 2.598.960 tổ hợp 5 lá; đối chiếu số lượng từng phân hạng bằng phép đếm tổ hợp độc lập |
| `packaged_resources` | Tìm tài nguyên theo vị trí `.exe` khi working directory khác |

Cả bốn kiểm thử đã đạt trên bản Windows đã kiểm thử. Chạy lại bằng:

```powershell
ctest --test-dir build --output-on-failure
```

## Kiểm thử giao diện

75 kịch bản đã xác minh trong sandbox với tài khoản minh họa:

- PVP 3 lá / 5 lá và Texas Hold’em PVP/PVE với 2–6 người.
- CALL, RAISE 20/30/50, FOLD, hết giờ và kết quả thắng/hòa.
- Bốn luồng đầy đủ từ menu qua đăng nhập đến hết ván, về menu và thoát.
- Chơi lại hai ván ở mỗi chế độ; số trận không bị ghi lặp.
- Hòa bàn 2 người và nhiều người, hiển thị đủ tên và đóng cửa sổ bình thường.
- Hủy chọn người; đóng trong hoạt ảnh, đếm giờ, lượt chơi và màn kết quả.
- Ít tài khoản; chơi hết ván với một tài khoản và không tạo tài khoản từ ghế Guest/Bot.
- Kiểm tra file leaderboard sau ván và sau chơi lại.

Sau khi chỉnh bố cục kết quả, bốn luồng đầy đủ và tám ca hòa/đóng cửa sổ đã được chạy lại.

Bộ quan sát UI và sự kiện giả chỉ được liên kết trong bản QA, không nằm trong exe phát hành. Các ca hòa dùng bộ bài định trước trong bản QA; cách xáo của game phát hành không đổi. Ảnh README được chụp với dữ liệu minh họa, không chứa tài khoản thật.

## Giới hạn

Đã kiểm thử Windows x64; chưa xác minh trên mọi nền tảng hoặc mọi tổ hợp 7 lá. Việc các ca kiểm thử đạt không phải bảo đảm game không thể có lỗi khác. Dữ liệu lịch sử được giữ nguyên; không đoán lại số trận đã bị phiên bản cũ bỏ sót.
