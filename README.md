# rtshd

ubuntu 
依赖 clang

依赖库
命令行解析 google gflags 


### 实现Ｃ语言刷新覆盖输出
如实现进度 extract 90%
``` cpp
int main(int argc, char*argv[]){
    int percent = 0;
    while( percent <= 100){
        printf("extract %d%\r",percent); // \r　光标移动到本行的开始处
        fflush(stdout);　//输出刷新
        sleep(1);
    }
    return 0;
}
```
tv,tvfm友元类sample
