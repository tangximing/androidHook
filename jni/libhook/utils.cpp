#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

/**
get process name by pid
**/

string getNameByPid(pid_t pid) {
    char proc_pid_path[1024];
    char buf[1024];
    string name = "";

    sprintf(proc_pid_path, "/proc/%d/status", pid);
    FILE* fp = fopen(proc_pid_path, "r");
    if(NULL != fp){
        if( fgets(buf, 1023, fp) != NULL ){
            name = strrchr( buf, ':' ) + 1;
        }
        fclose(fp);
    }

    if(name[name.length() - 1] == '\n')
    	return name.substr(0, name.length() - 1);
    return name;
}

/**
construct command
**/
vector<string> split(string s, string delim)  
{  
    vector<string> elems;  
    size_t pos = 0;  
    size_t len = s.length();  
    size_t delim_len = delim.length();  
    if (delim_len == 0) return elems;  
    while (pos < len)  
    {  
        int find_pos = s.find(delim, pos);  
        if (find_pos < 0)  
        {  
            elems.push_back(s.substr(pos, len - pos));  
            break;  
        }  
        elems.push_back(s.substr(pos, find_pos - pos));  
        pos = find_pos + delim_len;  
    }  
    return elems;  
}  

string getCommand(string data, int code){
    string result = getNameByPid(getpid());
    result += ";";
    vector<string> tmp = split(data, ":");
    if(data.find("com.android.internal.telephony.ISms") != string::npos){
        // send sms
        result += '0' + SendSms;
        result += ";";
        result += tmp[tmp.size() - 2];
        result += ":";
        result += tmp[tmp.size() - 1];
    }else if(data.find("android.content.IContentProvider") != string::npos){
    	if(data.find("com.android.contacts") != string::npos){
    		result += '0' + ReadContacts;
    		result += ";";
    	}else if(data.find("calllog") != string::npos){
    		result += '0' + ReadCallLogs;
    		result += ";";
    	}else if(data.find("sms") != string::npos){
    		result += '0' + ReadSms;
    		result += ";";
    	}else{
    		result = "";
    	}
    }else if(data.find("com.android.internal.telephony.IPhoneSubInfo") != string::npos){
    	if(code == 1){
    		result += '0' + ReadIMEI;
    		result += ";";
    	}else if(code == 5){
    		result += '0' + ReadIMSI;
    		result += ";";
    	}else if(code == 8){
    		result += '0' + ReadPhone;
    		result += ";";
    	}else
    		result = "";
    }else
    	result = "";
    return result;
}

/**
dump the data
**/
string hexdump(const void *_data, unsigned len){
    unsigned char *data = (unsigned char *)_data;
    char *dataAry = (char*)malloc(len*(sizeof(char)));
    char *dataTmp = dataAry;
    unsigned count;
    for (count = 0; count < len; count++) 
    {
        //HOOKLOG("%d: %c", *data, *data);
        // control char
        if((*data >= 1) && (*data <= 31))
        {
            if(count > 0 && *(dataAry - 1) != ':')
            {
                *dataAry = ':';
                dataAry++;
            }
        }
        // number, char, .
        if(((*data >= 48) && (*data <= 57)) || ((*data >= 65) && (*data <= 90)) || ((*data >= 97) && (*data <= 122)) || (*data == 46))
        {
            *dataAry = *data;
            dataAry++;  
        }
        data++;
    }
    *dataAry = '\0';

    string content(dataTmp);
    return content;
}