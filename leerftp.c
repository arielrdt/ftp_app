#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1024


void changeToRoot(){
	if((setuid(0)) < 0) printf("\n<br>setuid: operacion no permitida\n");
	if((setgid(0)) < 0) printf("\n<br>setgid: operacion no permitida\n");
}

void datosArchivoConfig(){
    FILE* fichero;
    fichero = fopen("/etc/vsftpd.conf", "rt");
    printf(fichero);
}

int main(void)
{
    changeToRoot();

    system("mkdir test");
    printf ("Content-type:text/html\n\n");
    printf("<TITLE>FTP CONFIG</TITLE>\n");
    return 0;
} 
