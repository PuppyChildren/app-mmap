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
    /* �f�[�^�����t�@�C���I�[�v�� */
    int fd = open(FILE_NAME.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
    /* �}�b�s���O������ */
    char* const file_memory = reinterpret_cast<char*>(mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    close(fd);
    /* ���e��ǂݎ���ĕ\�� */
    printf("%s\n", file_memory);

    /* ��� */
    munmap(file_memory, FILE_LENGTH);

    return EXIT_SUCCESS;
}
