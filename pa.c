#include <cstdlib>
#include <cstdio>
#include <string>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

const unsigned int FILE_LENGTH = 0x100;
const std::string FILE_NAME("./data.dat");

int main()
{
    /* UINTを保持するのに十分な大きさのファイルを準備します */
    int fd = open(FILE_NAME.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    lseek(fd, FILE_LENGTH+1, SEEK_SET);
    write(fd, "", 1);
    lseek(fd, 0, SEEK_SET);
    /* マッピングメモリ */
    char* const file_memory = reinterpret_cast<char*>(mmap(0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0));
    close(fd);
    /* 10回まわしてみる */
    for (unsigned int ui=0; ui < 10; ++ui){
      sprintf(file_memory, "%d\n", ui);
      sleep(1);
    }
    /* 終了 */
    sprintf(file_memory, "EOF\n");

    /* 解放 */
    munmap (file_memory, FILE_LENGTH);

    /* int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(-1);
    } else if (pid == 0){
        // 子プロセス
        printf("child process start\n");
        sleep(1);
        execl("./pa", "./pa &", NULL);
        printf("child process end\n");
        return 12;
    }
    int status;
    pid_t r = waitpid(pid, &status, 0); //子プロセスのプロセスIDを指定して、終了を待つ
    if (r < 0) {
        perror("waitpid");
        exit(-1);
    }
    if (WIFEXITED(status)) {
        // 子プロセスが正常終了の場合
        int exit_code = WEXITSTATUS(status); //子プロセスの終了コード
        printf("child exit-code=%d\n", exit_code);
    } else {
        printf("child status=%04x\n", status);
    }
    printf("parent process end\n");
    */

    execl("./pa", "./pa", NULL);
    perror("execl() failed");
    /* 到達しない */
    return EXIT_SUCCESS;
}
