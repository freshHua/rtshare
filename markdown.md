Ｍarkdown使用手册
==================
### 标题
＃一级标题 ## 二级标题　### 三级标题　#### 四级标题　#####五级标题 ######六级标题
### 公式
$$一行开始，并以$$一行结束，中间是符合Mathjax要求的数学公式如:

$
f(x) = \sqrt{3x-1}
$

### 流程图
Haroopad支持mermaid扩展。
Haroopad中mermaid绘图以mermaid单独一行开始，以单独一行结束。
如
~~~mermaid
graph RL
A[Hard edge] --> | Link text | B[Round edge] 
~~~


### 代码区域
代码区域需要以 \~~~ 加上编程语言标识符的单独一行开始，以 \~~~ 单独一行结束。
~~~ cpp
#include <cstdio>
int main(int argc, char*argv[])
{
	printf("hello world\n");
    return 0;
}
~~~


