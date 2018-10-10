#include <iostream>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

#define STATUS_FAILURE -1
#define STATUS_SUCCESS 0
#define ARGS_LIMIT 3
#define STDERR 2
#define MATCH true
#define NOT_MATCH false
#define BUFFSIZE 1024
#define MAXNAME 255
#define INVALID_FD 0


class Accept
{
private:
	int iS_fd, iD_fd;
	char cS_file[MAXNAME], cD_file[MAXNAME];
public:
	Accept(const char*, const char*);
	~Accept();
	bool CheckEqual();
};

