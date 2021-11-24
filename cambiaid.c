#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(){

    printf ("Content-type:text/html\n\n");
    printf("<HTML><TITLE>Response</TITLE>\n");
    printf("<body>");
	// Variables para almacenar el ID de usuario y grupo
	int Uid, Gid, iUid, iGid;
	
	//Obtener el ID/GID
	Uid = getuid();
	Gid = getgid();
	
	printf("<br>UID: %d\n", Uid);
	printf("<br>GID: %d\n", Gid);
	
	system("ls -l > lista.txt");
	
	// Cambiando nuevo ID y GID
	if((setuid(0)) < 0) printf("\n<br>setuid: operacion no permitida\n");
	if((setgid(0)) < 0) printf("\n<br>setgid: operacion no permitida\n");

	iUid = getuid();
	iGid = getgid();
	
	printf("<br>Nuevo UID: %d\n", iUid);
	printf("<br>Nuevo GID: %d\n", iGid);
	system("ls -l > lista1.txt");
	system("/sbin/fdisk -l > particion.txt");
	system("/usr/sbin/useradd -d /home/nuevo40 -m nuevo40 2> error.txt");
	system("/usr/sbin/useradd -d /home/nuevo41 -m nuevo41 2> error.txt");
        printf("</body></html>\n");
}
