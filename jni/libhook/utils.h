#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <vector>

using namespace std;

enum command
{
	FileSystem, 
	Network,
	Location,

	SendSms,
	ReadSms,
	ReadContacts,
	ReadCallLogs,
	ReadIMEI,
	ReadIMSI,
	ReadPhone
};

/**
get process name by pid
**/
string getNameByPid(pid_t pid);

/**
construct the command
**/
string getCommand(string data, int code);

/**
dump the data
**/
string hexdump(const void *_data, unsigned len);

#endif