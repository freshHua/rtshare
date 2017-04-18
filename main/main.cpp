#include<stdio.h>
#include<iostream>
#include<pthread.h>
#include <unistd.h>

#define STRIP_FLAG_HELP 1
#include <gflags/gflags.h>

// glfags, parse argv 
DEFINE_bool(daemon, false, "run daemon in the background");
DEFINE_string(config_file, "/etc/rtshare/rtshare.conf", "rtshare configure file.");

 std::string usage = "rtshare:  --config_file Configuration file\n" ;
int main(int argc, char*argv[])
{
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
    printf("This is rtshare programming\n");
    int count = 0;
    while(1){
	printf("@@@@%d@@@\r",count++);
	fflush(stdout);
	sleep(1);
    }
    return 0;
}
