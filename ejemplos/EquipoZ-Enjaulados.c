#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1024

#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <unistd.h>

int main()
{
    char *lenstr;
    char inputBuffer[MAXLEN];
    int contentLength;
    int i;
    char x;
    char r_opcion[80];
    char * usuario[100];

    setuid(0);
    setgid(0);

    printf ("Content-type:text/html\n\n");
    printf("<HTML>\n");
    printf("<head><TITLE>Enjaulados</TITLE>\n");

    //Boostrap
    printf("<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css' integrity='sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh' crossorigin='anonymous'>\n");
    //FIN Boostrap

    printf("<style>\n");
    printf("body{\n");
    printf("background:#8ba987 url('https://wallpaperplay.com/walls/full/6/9/8/28163.jpg') no-repeat center center;\n");
    printf("background-size:100% 100%;\n");
    printf("}\n");
    printf("</style>\n");
    printf("</head>\n");

    printf("<body>\n");
    printf("<div class='container h-100'>\n");
    printf("<div class='row justify-content-center h-100'>\n");
    printf("<div class='col-sm-8'>\n");
    printf("<div class='card shadow'>\n");
    printf("<div class='card-body' style='position: relative; width: 100%; padding-right: 80px; padding-left: 52px;}'>\n");

    lenstr = getenv("CONTENT_LENGTH");

    if (lenstr!= NULL)
    {
	contentLength = atoi(lenstr);
    }
    else contentLength = 0;

    if (contentLength > sizeof(inputBuffer)-1)
	contentLength = sizeof(inputBuffer)-1;

    i = 0;

    while (i < contentLength){

	x = fgetc(stdin);
	if (x==EOF) break;
	inputBuffer[i] = x;
	i++;
    }

    inputBuffer[i] = '\0';
    contentLength = i;
	
//------------------------------------------------------------------------------   
    separar(usuario,inputBuffer,'=');
    separar(usuario,inputBuffer,'&');
    printf("<form action='/cgi-bin/EquipoZ-AdministradorVSFTPD' method='POST'>\n");
    printf("<fieldset class='form-group'>\n");

    printf("<div class>\n");
    printf("<h1> Usuarios Enjaulados</h1>");
    printf("<br></br>");
    printf("</div><fieldset>");
    FILE * fichero;
    FILE * ficheroCh;
    char  cadena; 

   
 
    system("ls /etc/vsftpd.chroot_list > /srv/www/cgi-bin/contenidousr.txt ");
    fichero = fopen("/srv/cgi-bin/contenidousr","r");
    system("rm /srv/www/cgi-bin/contenidousr.txt");
    //Escritura sobre el archivo de configuracion  
    ficheroCh = fopen("/etc/vsftpd.chroot_list","a");
    fputs("\n",ficheroCh);
    fputs(usuario,ficheroCh);
    fputs("\n",ficheroCh);
   
    // Mostrar los usuarios enjaulados

    cadena = fgetc(ficheroCh);
    printf("<h2>");
    printf(usuario);
    printf("</h2>");

    printf("<br></br>");
    printf("<input type='submit' class='btn-primary' value='Retornar'>\n");
    printf("</form>\n");
    printf("</div>\n");
    printf("</div>\n");
    printf("</div>\n");
    printf("</div>\n");
    printf("</div>\n");

    printf("<script src='https://code.jquery.com/jquery-3.4.1.slim.min.js' integrity='sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n' crossorigin='anonymous'></script>\n");
    printf("<script src='https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js' integrity='sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo' crossorigin='anonymous'></script>\n");
    printf("<script src='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js' integrity='sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6' crossorigin='anonymous'></script>\n");
    printf("</body></html>\n");
}

void separar(char *cadena, char *linea, char separador)
{
    int x, y;
    x = 0; y = 0;

    while ((linea[x]) && (linea[x] != separador))
    {
        cadena[x] = linea[x];
        x = x + 1;
    }
    cadena[x] = '\0';
    if (linea[x]) ++x;

    y = 0;

    while (linea[y] = linea[x])
    {
        linea[y] = linea[x];
        y++;
        x++;
    }
}
