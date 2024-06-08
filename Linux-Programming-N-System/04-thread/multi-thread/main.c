#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

typedef struct {
    char HoTen[30];
    char NamSinh[30];
    char SDT[30];
    char QueQuan[30];
} thr_data_t;

static void *thr_handle(void *args) 
{
    pthread_t tid = pthread_self();
    thr_data_t *data = (thr_data_t *)args;

    if (pthread_equal(tid, thread_id1)) {
        printf("I'm thread_id1\n\n");
    } else {
        printf("I'm thread_id2\n");
        printf("Ho Ten: %s\n", data->HoTen);
        printf("Nam Sinh: %s\n", data->NamSinh);
        printf("SDT: %s\n", data->SDT);
        printf("Que Quan: %s\n", data->QueQuan);
    }
}


int main(int argc, char const *argv[])
{
    /* code */
    int ret;
    thr_data_t data = {0};

    strncpy(data.HoTen, "Nguyen Dinh Chien", sizeof(data.HoTen));                 
    strncpy(data.NamSinh, "2002", sizeof(data.NamSinh));                 
    strncpy(data.SDT, "0826009929", sizeof(data.SDT));                 
    strncpy(data.QueQuan, "Ninh Binh", sizeof(data.QueQuan));

    if (ret = pthread_create(&thread_id1, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(2);

    if (ret = pthread_create(&thread_id2, NULL, &thr_handle, &data)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(2);

    return 0;
}
