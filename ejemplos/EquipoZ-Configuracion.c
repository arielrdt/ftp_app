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
    char r_anonimo[80];
    char r_cuenta[80];
    char r_escritura[80];
    char r_chroot[80];
    char r_log[80];
    
    int nroLinea;
    char *linea_cambio;

    setuid(0);
    setgid(0);

    printf ("Content-type:text/html\n\n");
    printf("<HTML>\n");
    printf("<head><TITLE>Configuracion</TITLE>\n");

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
    printf("<h1 style='margin-left: 26%'><b>CONFIGURACION</b></h1>\n");
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

 separar(r_anonimo, inputBuffer, '=');
 separar(r_anonimo, inputBuffer, '&');

 separar(r_cuenta, inputBuffer, '=');
 separar(r_cuenta, inputBuffer, '&');

 separar(r_escritura, inputBuffer, '=');
 separar(r_escritura, inputBuffer, '&');

 separar(r_chroot, inputBuffer, '=');
 separar(r_chroot, inputBuffer, '&');

 separar(r_log, inputBuffer, '=');
 separar(r_log, inputBuffer, '&');


//-----------------------------------------------------------------------------------

    printf("<form action='/cgi-bin/EquipoZ-AdministradorVSFTPD' method='POST'>\n");
    printf("<fieldset class='form-group'>\n");
    printf("<div class='row' style='margin-left: 5%;'>\n");
    printf("<h4>VSFTPD - Configuracion actual:</h4>");

    printf("<br><br>");

    printf("</div></fieldset>\n");

    //COMBOBOX ANONYMOUS 1 - ANONYMOUS
    if(strcmp(r_anonimo,"option1") == 0){
	system("sed -i 's/anonymous_enable=NO/anonymous_enable=YES/g' /etc/vsftpd.conf");
	printf("<p style='color: green'>1.- ANONYMOUS:          HABILITADO");
    }
    else
    {
	system("sed -i 's/anonymous_enable=YES/anonymous_enable=NO/g' /etc/vsftpd.conf");
	printf("<p style='color: red'>1.- ANONYMOUS:          DESHABILITADO");
    }
    //FIN ANONYMOUS

    //COMBOBOX CUENTA 2 - CUENTA
    if(strcmp(r_cuenta,"option1") == 0){
	system("sed -i 's/local_enable=NO/local_enable=YES/g' /etc/vsftpd.conf");
	printf("<p style='color: green'>2.- CUENTAS LOCALES:    HABILITADO");
    }
    else
    {
	system("sed -i 's/local_enable=YES/local_enable=NO/g' /etc/vsftpd.conf");
	printf("<p style='color: red'>2.- CUENTAS LOCALES:    DESHABILITADO");
    }
    //FIN CUENTA

    //COMBOBOX CUENTA_ESCRITURA 3 - CUENTA_ESCRITURA
    if(strcmp(r_escritura,"option1") == 0){
	system("sed -i 's/write_enable=NO/write_enable=YES/g' /etc/vsftpd.conf");
	printf("<p style='color: green'>3.- ESCRITURA:          HABILITADO");
    }
    else
    {
	system("sed -i 's/write_enable=YES/write_enable=NO/g' /etc/vsftpd.conf");
	printf("<p style='color: red'>3.- ESCRITURA:          DESHABILITADO");
    }
    //FIN CUENTA_ESCRITURA

    //COMBOBOX CHROOT_USER 4 - CHROOT_USER
    system("sed -i 's!#chroot_local_user=YES!chroot_local_user=YES!g' /etc/vsftpd.conf");
    system("sed -i 's!#chroot_local_user=NO!chroot_local_user=NO!g' /etc/vsftpd.conf");

    system("sed -i 's!#chroot_list_enable=YES!chroot_list_enable=YES!g' /etc/vsftpd.conf");
    system("sed -i 's!#chroot_list_enable=NO!chroot_list_enable=NO!g' /etc/vsftpd.conf");

    system("sed -i 's!#chroot_list_file=/etc/vsftpd.chroot_list!chroot_list_file=/etc/vsftpd.chroot_list!g' /etc/vsftpd.conf");

    if(strcmp(r_chroot,"option1") == 0){
	system("sed -i 's/chroot_local_user=YES/chroot_local_user=NO/g' /etc/vsftpd.conf");
	system("sed -i 's/chroot_list_enable=NO/chroot_list_enable=YES/g' /etc/vsftpd.conf");
        printf("<p style='color: green'>4.- CHROOT:             HABILITADO");
    }
    else
    {
	system("sed -i 's/chroot_local_user=YES/chroot_local_user=NO/g' /etc/vsftpd.conf");
	system("sed -i 's/chroot_list_enable=YES/chroot_list_enable=NO/g' /etc/vsftpd.conf");
	printf("<p style='color: red'>4.- CHROOT:             DESHABILITADO");
    }
    //FIN CHROOT_USER

    //COMBOBOX LOG 5 - LOG
    system("sed -i 's!#log_ftp_protocol=YES!log_ftp_protocol=YES!g' /etc/vsftpd.conf");
    system("sed -i 's!#log_ftp_protocol=NO!log_ftp_protocol=NO!g' /etc/vsftpd.conf");

    system("sed -i 's!#xferlog_enable=YES!xferlog_enable=YES!g' /etc/vsftpd.conf");
    system("sed -i 's!#xferlog_enable=NO!xferlog_enable=NO!g' /etc/vsftpd.conf");

    if(strcmp(r_log,"option1") == 0){
	system("sed -i 's/log_ftp_protocol=NO/log_ftp_protocol=YES/g' /etc/vsftpd.conf");
	system("sed -i 's/syslog_enable=YES/syslog_enable=NO/g' /etc/vsftpd.conf");
	system("sed -i 's/xferlog_enable=NO/xferlog_enable=YES/g' /etc/vsftpd.conf");
	printf("<p style='color: green'>5.- LOG:                HABILITADO");
    }
    else
    {
	system("sed -i 's/log_ftp_protocol=YES/log_ftp_protocol=NO/g' /etc/vsftpd.conf");
	system("sed -i 's/syslog_enable=NO/syslog_enable=YES/g' /etc/vsftpd.conf");
	system("sed -i 's/xferlog_enable=YES/xferlog_enable=NO/g' /etc/vsftpd.conf");
	printf("<p style='color: red'>5.- LOG:                DESHABILITADO");
    }
    //FIN LOG
    printf("<br><br>");
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
