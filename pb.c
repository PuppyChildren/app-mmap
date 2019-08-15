#include <cstdlib>
#include <cstdio>
#include <string>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

const unsigned int FILE_LENGTH = 0x100;
const std::string FILE_NAME("./data.dat");

int main()
{
    /* データ交換ファイルオープン */
    int fd = open(FILE_NAME.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
    /* マッピングメモリ */
    char* const file_memory = reinterpret_cast<char*>(mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    close(fd);
    /* 内容を読み取って表示 */
    printf("%s\n", file_memory);

    /* 解放 */
    munmap(file_memory, FILE_LENGTH);

    return EXIT_SUCCESS;
}
