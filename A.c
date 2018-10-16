#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;

    }


    int fd = open(argv[1], O_RDWR);

    if (fd < 0) {
        return 1;
    }


    char a[sizeof(int)] = {};
    char b[sizeof(int)] = {};

    int offset = lseek(fd, -(long)sizeof(int), SEEK_END);

    if (offset < 4) {
        close(fd);
        return 1;
    }

    if (read(fd, &a, sizeof(a)) != sizeof(a)) {
        close(fd);
        return 1;
    }
    if (lseek(fd, 0, SEEK_SET) < 0) {
        close(fd);
        return 1;
    }

    if (read(fd, &b, sizeof(b)) != sizeof(b)) {
        close(fd);
        return 1;
    }
    
    if (lseek(fd, 0, SEEK_SET) < 0) {
        close(fd);
        return 1;
    }

    if (write(fd, &a, sizeof(a)) != sizeof(a)) {
        close(fd);
        return 1;
    }

    if (lseek(fd, -(long)sizeof(int), SEEK_END) < 0) {
        close(fd);
        return 1;
    }
    
    if (write(fd, &b, sizeof(b)) != sizeof(b)) {
        close(fd);
        return 1;
    }
    close(fd);

    return 0;
}
