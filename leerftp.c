#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1024


void changeToRoot(){
	if((setuid(0)) < 0) printf("\n<br>setuid: operacion no permitida\n");
	if((setgid(0)) < 0) printf("\n<br>setgid: operacion no permitida\n");
}

int main(void)
{
    changeToRoot();
    
    system("mkdir test");
    printf ("Content-type:text/html\n\n");
    printf("<TITLE>Response</TITLE>\n");

    printf("<br>Datos Formulario: %s\n");
    printf("<br>Tama&ntildeo: %d\n");

    printf("<p> Mensaje: %s");
    printf("<p> Usuario: %s");
    printf("<p> Clave: %s");
    printf("<p> Shell: %s");

    return 0;
} 
