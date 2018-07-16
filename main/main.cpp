#include<stdio.h>
#include<iostream>
#include<pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>

#define STRIP_FLAG_HELP 1
#include <gflags/gflags.h>

#include "matrix_keymap.h"
#include "fib.h"

// glfags, parse argv 
DEFINE_bool(daemon, false, "run daemon in the background");
DEFINE_string(config_file, "/etc/rtshare/rtshare.conf", "rtshare configure file.");

std::string usage = "rtshare:  --config_file Configuration file\n" ;

#define _IOC_NRBITS      8
#define _IOC_TYPEBITS    8
#define _IOC_SIZEBITS   14	/* Actually 14, see below. */
#define _IOC_DIRBITS     2

#define _IOC_NRMASK      ((1 << _IOC_NRBITS)-1)
#define _IOC_TYPEMASK    ((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK    ((1 << _IOC_SIZEBITS)-1)
#define _IOC_XSIZEMASK   ((1 << (_IOC_SIZEBITS+1))-1)
#define _IOC_DIRMASK     ((1 << _IOC_DIRBITS)-1)

#define _IOC_NRSHIFT     0
#define _IOC_TYPESHIFT   (_IOC_NRSHIFT + _IOC_NRBITS)
#define _IOC_SIZESHIFT   (_IOC_TYPESHIFT + _IOC_TYPEBITS)
#define _IOC_DIRSHIFT    (_IOC_SIZESHIFT + _IOC_SIZEBITS)

#define _IOC_NONE        0U
#define _IOC_READ        1U
#define _IOC_WRITE       2U

#define _IOC(dir,type,nr,size) \
            (((dir)  << _IOC_DIRSHIFT) | \
	              ((type) << _IOC_TYPESHIFT) | \
	              ((nr)   << _IOC_NRSHIFT) | \
	              ((size) << _IOC_SIZESHIFT))

#define _IO(type,nr)        _IOC(_IOC_NONE,(type),(nr),0)
#define _IOR(type,nr,size)  _IOC(_IOC_READ,(type),(nr),sizeof(size))
#define _IOW(type,nr,size)  _IOC(_IOC_WRITE,(type),(nr),sizeof(size))
#define _IOWR(type,nr,size) _IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))

#define GYROSCOPE							0X86
#define GYROSCOPE_IOCTL_INIT				_IO(GYROSCOPE, 0x01)
#define GYROSCOPE_IOCTL_SMT_DATA			_IOR(GYROSCOPE, 0x02, int)


typedef struct  RequestInfo{
    int token;
    RequestInfo*p_next ;
}RequestInfo;


void  enqueue( int token,RequestInfo* &head ) {
    RequestInfo * node  = (RequestInfo *)malloc(sizeof(RequestInfo));
    node->token = token;
    if(!head){
        head = node;
        node->p_next = NULL;
    }else{
        node->p_next = head ;
        head = node;
    }
}

void requestEachRequestInfo(RequestInfo*head){
    while(head!=NULL){
        printf("RequestInfo token %d, %p\n", head->token,head );
        head = head->p_next;
    }
}
int checkAndDequeue(RequestInfo*&head, int token) {
    int ret = 0 ;
    RequestInfo *temp;
    for(RequestInfo **ppCur = &head; *ppCur != NULL; ppCur = &((*ppCur)->p_next)) {
        if (token == (*ppCur)->token ) {
            ret = 1;
            temp = *ppCur;
            *ppCur = (*ppCur)->p_next;
            free(temp);
            break;
        }
    }
    return ret;
}

class Example {
public:
    int total;
    void accumulate (int x) { total += x; }
    int getTotal(){
	return total; 
    }
};

int main(int argc, char*argv[])
{
    int mypid ;
    int rows = 5;
    int cols = 5;
    int row_shift = get_count_order(cols);
    std::string usage = "rtshare: \n" ;
    google::SetVersionString("rtshare:1.0.0");
    usage += "--config_file Configuration file\n";
    usage += "--daemon run daemon in the background \n";
    usage += "\n\n.......................................\n";
    usage += "gflags help";
    google::SetUsageMessage(usage);
    google::ParseCommandLineFlags(&argc, &argv, false);
    std::cout << "rtshare config file " << FLAGS_config_file << std::endl ;
    std::cout << "run daemon in the background " << FLAGS_daemon << std::endl ;
    printf("This is rtshare programming \n");
    printf("ioctl value GYROSCOPE_IOCTL_SMT_DATA %x\n", GYROSCOPE_IOCTL_SMT_DATA);
    printf("ioctl value GYROSCOPE_IOCTL_INIT 0x%x \n", GYROSCOPE_IOCTL_INIT);

    printf("row_shift %d max_keys %d\n", row_shift,rows << row_shift);
    printf("key row %d \n", ( (2 << row_shift) + 1 ));

    printf("RequestInfo List  \n");
    RequestInfo* head = NULL;
    enqueue(8,head);
    enqueue(10,head);
    enqueue(7,head);
    enqueue(6,head);
    requestEachRequestInfo(head);
    checkAndDequeue(head,7);
    printf("Dequeue requestInfo List  \n");
    requestEachRequestInfo(head);
    if( (mypid=fork()) > 0){
	std::cout<<"fib(6) = " << fib(6) << std::endl;
	std::cout<< "fib(5) = "  << fib(5) <<  std::endl;
	std::cout<< "fib(7)= " << fib(7) << std::endl;
    }else{
	std::cout<< "fib(1) = "  << fib(1) <<  std::endl;
    }

    Example EX;
    std::cout << EX.getTotal() <<  std::endl;
    return 0;
}
