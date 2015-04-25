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
    /* �������˿�ʼ����socket������
    ��һ������ָ��Ӧ�ó���ʹ�õ�ͨ��Э���Э���壬����TCP/IPЭ���壬�ò�����AF_INET��
    �ڶ�������ָ��Ҫ�������׽������ͣ����׽�������ΪSOCK_STREAM;
    ����������ָ��Ӧ�ó�����ʹ�õ�ͨ��Э�顣�˲�������ָ������Э��ϵ���еĲ�ͬ����Э�顣��InternetͨѶ���У��˲���һ��ȡֵΪ0��ϵͳ������׽��ֵ����;���Ӧʹ�õĴ����Э�顣
    �ú���������óɹ��ͷ����´������׽��ֵ������������ʧ�ܾͷ���INVALID_SOCKET����Linux��ʧ�ܷ���-1���׽�����������һ���������͵�ֵ��
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