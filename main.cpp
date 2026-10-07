#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <climits>

using namespace std;

const int READ_END = 0;
const int WRITE_END = 1;

int editDistance(const string& word1, const string& word2);
bool readCode(int fd, string& code);
void writeCode(int fd, const string& code);
int filterProcess(int inFd);

int main(int argc, char* argv[])
{
    cout << "\nFinding maximally distinct codes..." << endl;

    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {   // child
        close(fd[WRITE_END]);
        int count = filterProcess(fd[READ_END]);
        close(fd[READ_END]);
        exit(count);
    }
    else
    {   // parent
        close(fd[READ_END]);
        for (int i = 1; i < argc; i++)
        {
            writeCode(fd[WRITE_END], argv[i]);
        }
        close(fd[WRITE_END]);

        int status;
        waitpid(pid, &status, 0);

        // I don't like transmitting count through status codes, it just seemed like the cleanest way to do it to me
        cout << "\n" << (status >> 8) << " distinct codes found (no two are one edit apart)" << endl; // status divided by 256
    }

    return 0;
}
//--
bool readCode(int fd, string& code)
{
    code.clear();
    char c;
    while (read(fd, &c, 1) > 0)
    {
        if (c == '\0')
        {
            return true;
        }
        code += c;
    }
    return false;
}
//--
void writeCode(int fd, const string& code)
{
    if (write(fd, code.c_str(), code.size() + 1) < 0)
    {
        perror("write");
        exit(1);
    }
}
//--
int editDistance(const string& word1, const string& word2)
{
    if (word1.size() != word2.size())
    {   // "codes of different lengths automatically pass through"
        return INT_MAX;
    }

    int count = 0;
    for (size_t i = 0; i < word1.size(); i++)
    {
        if (word1[i] != word2[i])
        {
            count++;
        }
    }
    return count;
}
//--
int filterProcess(int inFd)
{
    string myCode;
    if (!readCode(inFd, myCode))
    {
        return 0;
    }

    int nextFd = -1;
    pid_t nextPid = -1;
    string code;

    while (readCode(inFd, code))
    {
        if (editDistance(myCode, code) <= 1)
        {
            continue;
        }

        if (nextFd == -1)
        {   // this code survived every filter, so spawn a filter for it
            int new_fd[2];
            if (pipe(new_fd) < 0)
            {
                perror("pipe");
                exit(1);
            }

            nextPid = fork();
            if (nextPid < 0)
            {
                perror("fork");
                exit(1);
            }

            if (nextPid == 0)
            {   // child
                close(inFd);
                close(new_fd[WRITE_END]);
                int count = filterProcess(new_fd[READ_END]);
                close(new_fd[READ_END]);
                exit(count);
            }

            close(new_fd[READ_END]);
            nextFd = new_fd[WRITE_END];
        }

        writeCode(nextFd, code);
    }

    cout << "Process: " << getpid() << " my code is \"" << myCode << "\"" << endl;

    int count = 1;
    if (nextFd != -1) // true when this process has spawned a filter process
    {
        close(nextFd);

        int status;
        waitpid(nextPid, &status, 0);
        count += status >> 8; // status divided by 256
    }
    return count;
}
