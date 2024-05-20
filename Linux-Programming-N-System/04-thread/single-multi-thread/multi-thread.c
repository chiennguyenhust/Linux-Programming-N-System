#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4 // Số lượng luồng
#define ARRAY_SIZE 1000 // Kích thước mảng

int array[ARRAY_SIZE]; // Mảng chứa các số nguyên
int results[NUM_THREADS]; // Mảng chứa kết quả của mỗi luồng

// Hàm mà mỗi luồng sẽ chạy
void* sum_part(void* arg) {
    int thread_id = *(int*)arg; // Lấy ID của luồng

    // Tính toán điểm bắt đầu và kết thúc cho phần mảng của luồng này
    int start = thread_id * (ARRAY_SIZE / NUM_THREADS); // Điểm bắt đầu của phần mảng
    int end = (thread_id + 1) * (ARRAY_SIZE / NUM_THREADS); // Điểm kết thúc của phần mảng
    int total = 0;

    // Tính tổng của phần mảng được chỉ định
    for (int i = start; i < end; i++) {
        total += array[i];
    }

    results[thread_id] = total; // Lưu kết quả vào mảng kết quả
    pthread_exit(0); // Kết thúc luồng
}

int main() {
    // Khởi tạo mảng với các giá trị từ 0 đến 999
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    pthread_t threads[NUM_THREADS]; // Mảng chứa các luồng
    int thread_ids[NUM_THREADS]; // Mảng chứa ID của các luồng

    // Tạo các luồng
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i; // Gán ID cho từng luồng
        pthread_create(&threads[i], NULL, sum_part, &thread_ids[i]); // Tạo luồng và chạy hàm sum_part
    }

    // Đợi các luồng hoàn thành và thu thập kết quả
    int total = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Đợi luồng hoàn thành
        total += results[i]; // Cộng kết quả từ mỗi luồng vào tổng
    }

    // In tổng kết quả
    printf("Total sum (multi-threaded): %d\n", total);
    return 0;
}
