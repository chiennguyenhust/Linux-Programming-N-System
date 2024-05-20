BT10. Cung một ví dụ mà multi-thread không cung cấp hiệu suất tốt hơn các giải pháp single-thread
- Single-thread.c: tính tổng các phần từ của mảng sử dụng single-thread thông thường.
- Multi-thread.c: chia mảng thành các phần nhỏ rồi tính tổng các phần nhỏ đó bởi các thread sau đó cộng tổng lại.