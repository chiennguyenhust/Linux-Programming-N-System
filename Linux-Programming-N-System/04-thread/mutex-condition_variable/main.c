#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h> 

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;


typedef struct {
    char HoTen[30];
    char NamSinh[30];
    char QueQuan[30];
} thread_args_t;

static void *handle_th1(void *args) 
{
    thread_args_t *thr = (thread_args_t *)args;

    pthread_mutex_lock(&lock1);
    printf("Nhap ho va ten: ");
    scanf("%29[^\n]", thr->HoTen); // Đọc chuỗi có khoảng trắng và tối đa 29 ký tự
    getchar();
    printf("Nhap nam sinh: ");
    scanf("%29[^\n]", thr->NamSinh);
    getchar();
    printf("Nhap que quan: ");
    scanf("%29[^\n]", thr->QueQuan);
    getchar();

    pthread_cond_signal(&cond1);
    printf("Nhap xong thong tin\n");
    pthread_mutex_unlock(&lock1);

    pthread_exit(NULL);
}

static void *handle_th2(void *args) 
{
    thread_args_t *thr = (thread_args_t *)args;
    pthread_mutex_lock(&lock2);
    pthread_cond_wait(&cond1, &lock1);
        int fd = open("thongtinsinhvien.txt", O_RDWR | O_CREAT, 0667);         
        if (fd == -1) { 
            printf("open() thongtinsinhvien.txt failed\n");
        } else {
            write(fd, thr->HoTen, strlen(thr->HoTen)); 
            write(fd, "\n", 1); // Ghi kí tự xuống dòng
            write(fd, thr->NamSinh, strlen(thr->NamSinh)); 
            write(fd, "\n", 1); // Ghi kí tự xuống dòng
            write(fd, thr->QueQuan, strlen(thr->QueQuan));  
            write(fd, "\n", 1); // Ghi kí tự xuống dòng
        }
        close(fd); 
    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&lock2);
    pthread_exit(NULL);
}

static void *handle_th3(void *args) 
{   thread_args_t *thr = (thread_args_t *)args;
    pthread_mutex_lock(&lock3);
    pthread_cond_wait(&cond2, &lock2);
      int fd = open("thongtinsinhvien.txt", O_RDWR | O_CREAT, 0667);         
        if (fd == -1) { 
            printf("open() thongtinsinhvien.txt failed\n");
        } else {

        char buffer[30];
        while (read(fd, buffer, sizeof(buffer)-1))
        {
            buffer[29] = '\0';  // Đảm bảo chuỗi null-terminated
            printf("Thong tin sinh vien vua nhap:\n %s", buffer);  
        }

        }
        close(fd);

    pthread_mutex_unlock(&lock3);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int ret;
    thread_args_t thr;
    pthread_t thread_id1, thread_id2, thread_id3;

    if ((ret = pthread_create(&thread_id1, NULL, &handle_th1, &thr))) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if ((ret = pthread_create(&thread_id2, NULL, &handle_th2, &thr))) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if ((ret = pthread_create(&thread_id3, NULL, &handle_th3, &thr))) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL); // Chờ thread 1 hoàn thành
    pthread_join(thread_id2, NULL); // Chờ thread 2 hoàn thành
    pthread_join(thread_id3, NULL); // Chờ thread 3 hoàn thành

    return 0;
}
