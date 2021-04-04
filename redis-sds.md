## redis-sds结构

struct {

    int len;//标识具体的字符创的长，其中不包括最后一个'\0'
    
    int free;//没有使用的空间
    
    char* buf;//字节数据（包括不可显示的字符）的指针
};
其中数据的总长度包括：len + free + 1字节
##

