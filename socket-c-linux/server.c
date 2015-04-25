/**server**/
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
    char sTalk[100];
    int sfp,nfp;
    struct sockaddr_in s_add,c_add;
    int sin_size;
    unsigned short portnum=0x8888;
    printf("Hello,welcome to my server !\r\n");
    /* 服务器端开始建立socket描述符
    第一个参数指定应用程序使用的通信协议的协议族，对于TCP/IP协议族，该参数置AF_INET；
    第二个参数指定要创建的套接字类型，流套接字类型为SOCK_STREAM;
    第三个参数指定应用程序所使用的通信协议。此参数可以指定单个协议系列中的不同传输协议。在Internet通讯域中，此参数一般取值为0，系统会根据套接字的类型决定应使用的传输层协议。
    该函数如果调用成功就返回新创建的套接字的描述符，如果失败就返回INVALID_SOCKET。（Linux下失败返回-1）套接字描述符是一个整数类型的值。
    */
    sfp = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sfp)
    {
        printf("socket fail ! \r\n");
        return -1;
    }
    printf("socket ok !\r\n");

    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr=htonl(INADDR_ANY);
    s_add.sin_port=htons(portnum);

    if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        printf("bind fail !\r\n");
        return -1;
    }
    printf("bind ok !\r\n");

    if(-1 == listen(sfp,5))
    {
        printf("listen fail !\r\n");
        return -1;
    }
    printf("listen ok\r\n");
    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);

        nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);
        if(-1 == nfp)
        {
            printf("accept fail !\r\n");
            return -1;
        }
        //printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n",ntohl(c_add.sin_addr.s_addr),ntohs(c_add.sin_port));
        scanf("%s",sTalk);
        if(-1 == write(nfp,sTalk,strlen(sTalk)))
        {
            printf("write fail!\r\n");
            return -1;
        }
        //printf("write ok!\r\n");
        close(nfp);
    }
    close(sfp);
    return 0;
}