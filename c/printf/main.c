#include <stdio.h>

// 1)d（或i）格式符。用来输出十进制整数，有以下几种用法：
//     ①%d，按整型数据的实际长度输出。
//     ②%md，m为指定的输出字段的宽度。如果数据的位数小于m，则左端补以空格，若大于m，则按实际位数输出。
//     ③%ld(%mld 也可)，输出长整型数据。
//     例如：long a=123456;
//     printf("%ld",a);
// (2)o格式符，以八进制数形式输出整数。格式：%o，%mo,%lo，%mlo都可。
// (3)x(或X)格式符，以十六进制数形式输出整数。格式：%x，%mx,%lx，%mlx都可。
// (4)u格式符，用来输出unsigned型数据，即无符号数，以十进制数形式输出。格式：%u，%mu,%lu都可。
//
// (5)c格式符，用来输出一个字符。格式：%c，%mc都可。
// (6)s格式符，用来输出一个字符串。格式：%s，%ms,%-ms，%m.ns，%-m.ns都可。
// (7)f格式符，用来输出实数（包括单、双精度），以小数形式输出。格式：%f，%m.nf，%-m.nf都可。
// 注意：单精度实数的有效位数一般为7位，双精度为16位。
// (8)e(或E)格式符，以指数形式输出实数。格式：%e，%m.ne，%-m.ne都可。
// (9)g(或G)格式符，用来输出实数，它根据数值的大小，自动选f格式或e格式（选择输出时占宽度较小的一种）。

int main() {

    char s[] = "this is a str";
    printf("[%20s]\n", s); // align right, fill with blank space
    printf("[%-20s]\n", s); // align left, fill with blank space

    printf("-------------------------\n");
    int d = 10;
    printf("[%d]\n", d);    // normal
    printf("[%10d]\n", d);  // align right, fill with blank space
    printf("[%010d]\n", d); // filll with 0 in front of number.
    printf("[%0*d]\n", 10, d);

    printf("-------------------------\n");
    unsigned u = 10;
    printf("[%u]\n", u);


}