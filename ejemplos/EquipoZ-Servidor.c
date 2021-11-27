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
   
    setuid(0);
    setgid(0);

    printf ("Content-type:text/html\n\n");
    printf("<HTML>\n");
    printf("<head><TITLE>Servidor</TITLE>\n");

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
    printf("<h1 style='margin-left: 36%'><b>SERVIDOR</b></h1>\n");
    printf("<h2 style='margin-left: 40%'><b>VSFTPDF</b></h2>\n");

    printf("<br><br>\n");

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
    
separar(r_opcion, inputBuffer, '=');
separar(r_opcion, inputBuffer, '&');

    printf("<form action='/cgi-bin/EquipoZ-AdministradorVSFTPD' method='POST'>\n");
    printf("<fieldset class='form-group'>\n");
    printf("<div class='row' style='margin-left: 5%;'>\n");
    printf("<h4>VSFTPD - Estado actual:</h4>\n");

    printf("<br><br>\n");

    printf("</div></fieldset>\n");

    //OPCION 1 -> Iniciar servidor VSFTPD | OPCION 2 -> Reiniciar servidor VSFTPD | opcion 3 -> Detener servidor VSFTPD
    if(strcmp(r_opcion,"option1") == 0){
        system("service vsftpd start");
        printf("<p style='color: green'> SERVIDOR VSFTPD INICIADO</p>\n");
    }
    else if(strcmp(r_opcion,"option2") == 0)
    {
        system("service vsftpd restart");
        printf("<p style='color: orange'> SERVIDOR VSFTPD REINICIADO</p>\n");
    }else{
        system("service vsftpd stop");
        printf("<p style='color: red'> SERVIDOR VSFTPD DETENIDO</p>\n");
    }

    printf("<input type='submit' style='margin-left: 5%' class='btn-primary' value='Retornar'>\n");
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
