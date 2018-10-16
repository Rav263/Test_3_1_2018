#include <time.h>
#include <stdlib.h>
#include <stdio.h>

enum 
{
    YEAR_OFFSET = 1900
};


int
main(int argc, char *argv[]){
    if (argc < 3) {
        return 1;
    }

    long year = strtol(argv[1], NULL, 10);
    long month = strtol(argv[2], NULL, 10);


    struct tm *now_time = calloc(1, sizeof(struct tm));

    now_time->tm_year = year - YEAR_OFFSET;
    now_time->tm_mon = month - 1;
    now_time->tm_mday = 1;
    now_time->tm_isdst = -1;
    int work_hours = 0;
    time_t some = mktime(now_time);
    while (1) {
        localtime_r(&some, now_time);
        if (now_time->tm_mon != month - 1) {
            break;
        }

        if (now_time->tm_wday >= 1 && now_time->tm_wday <= 4) {
            work_hours += 8;
        } else if (now_time->tm_wday == 5) {
            work_hours += 6;
        }
        now_time->tm_mday += 1;

        some = mktime(now_time);
    }
    free(now_time);

    printf("%d\n", work_hours);
}
