#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(){

    // Cambiando nuevo ID y ID PERMISOS!!!
    int Uid, Gid, iUid, iGid;
    FILE * fichero;
    int contadorLineas = 0;
    char caracter;

    setuid(0);
    setgid(0);

    printf("Content-type:text/html\n\n");
    printf("<HTML>\n");
    printf("<head><TITLE>Administrador VSFTPD</TITLE>\n");

    //Boostrap
    printf("<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css' integrity='sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh' crossorigin='anonymous'>\n");
    //FIN Boostrap

    printf("<style>\n");
    printf("body{\n");
    printf("background:#8ba987 url('https://wallpaperplay.com/walls/full/6/9/8/28163.jpg') no-repeat center center;\n");
    printf("background-size:2000px 5000px;\n");
    printf("}\n");
    printf("</style>\n");
    printf("</head>\n");

    printf("<body>\n");
    printf("<div class='container h-100'>\n");
    printf("<div class='row justify-content-center h-100'>\n");
    printf("<div class='col-sm-8'>\n");
    printf("<div class='card shadow'>\n");
    printf("<div class='card-body' style='position: relative; width: 100%; padding-right: 80px; padding-left: 52px;}'>\n");
    printf("<h1 style='margin-left: 25%'><b>ADMINISTRADOR</b></h1>\n");
    printf("<h2 style='margin-left: 42%'><b>VSFTPDF</b></h2>\n");

    printf("<br><br>\n");

    printf("<form action='/cgi-bin/EquipoZ-Servidor' method='POST'>\n");
    printf("<fieldset class='form-group'>\n");
    printf("<div class='row' style='margin-left: 5%;'>\n");
    printf("<legend class='col-form-label  pt-0'><b>Vsftpd</b></legend>\n");

    //Verificar vsftpd instalado
    system("rpm -qa | grep vsftpd > /srv/www/cgi-bin/vsftpd.txt"); //Buscando todo lo relacionado con vsftpd.
    fichero = fopen( "/srv/www/cgi-bin/vsftpd.txt","r" );
    if (NULL != fichero) {
    	fseek (fichero, 0, SEEK_END);
    	int size = ftell(fichero);

    	if (0 >= size) {
        	printf("<p style='color: red'>Vsftpd no instalado</p>\n");
    	}else{
		printf("<p style='color: green'>Vsftpd instalado</p>\n");
	}
    }
    system("rm /srv/www/cgi-bin/vsftpd.txt");
    //FIN Verificar vsftpd instlado

    printf("<div class='col-sm-10'>\n");

    //Verificar si vsftpd esta inicializado
    system("ps ax | grep vsftpd > /srv/www/cgi-bin/vsftpd.txt"); //Buscando todo lo relacionado con vsftpd.
    fichero = fopen( "/srv/www/cgi-bin/vsftpd.txt","r" );
    if (fichero != NULL){
    	// Extract characters from file and store in character c
    	for (caracter = getc(fichero); caracter != EOF; caracter = getc(fichero))
        if (caracter == '\n') // Increment count if this character is newline
            contadorLineas = contadorLineas + 1;
       	fclose(fichero);
        if (contadorLineas-1 <= 1) {
                printf("<p style='color: red'>Vsftpd no inicializado</p>\n");
        }else{
                printf("<p style='color: green'>Vsftpd inicializado</p>\n");
        }
    }
    system("rm /srv/www/cgi-bin/vsftpd.txt");
    //FIN Verificar si vsftpd esta inicializado

    printf("<div class='form-check' style='margin-left: 20%;'>\n");
    printf("<input class='form-check-input' type='radio' name='r_servidor' value='option1' checked>\n");
    printf("<label class='form-check-label' for='gridRadios1'>Iniciar el servidor</label></div>\n");

    printf("<div class='form-check' style='margin-left: 20%;'>\n");
    printf("<input class='form-check-input' type='radio' name='r_servidor' value='option2'>\n");
    printf("<label class='form-check-label' for='gridRadios2'>Reiniciar el servidor</label></div>\n");

    printf("<div class='form-check' style='margin-left: 20%;'>\n");
    printf("<input class='form-check-input' type='radio' name='r_servidor' value='option3'>\n");
    printf("<label class='form-check-label' for='gridRadios3'>Detener el servidor</label></div>\n");

    printf("</div>\n");
    printf("</div>\n");
    printf("</fieldset>\n");
    printf("<input type='submit' style='margin-left: 5%' class='btn-primary' value='confirmar'>\n");
    printf("</form>\n");

    printf("<br>\n");

    printf("<form action='/cgi-bin/EquipoZ-Configuracion' method='POST'>\n");
    printf("<fieldset class='form-group'>\n");
    printf("<div class='row' style='margin-left: 5%;'>\n");
    printf("<div class='form-group'>\n");

    //Estado Anonymous
    system("grep 'anonymous_enable=YES' /etc/vsftpd.conf > /srv/www/cgi-bin/tempo.txt");
    FILE * fichero1;
    char cadArchivo1[1024];
    fichero1 = fopen("/srv/www/cgi-bin/tempo.txt","r");
    if(fgets(cadArchivo1,100,fichero1)!=NULL){
		printf("<p style='color: green' style='font-size:10px' > Anonymous Esta Habilitado</p>\n");
   	 }else{
		printf("<p style='color: red' style='font-size:10px' > Anonymous Esta Deshabilitado</p>\n");
	}
    fclose(fichero1);
    system("rm /srv/www/cgi-bin/tempo.txt");
   //Fin estado Anonymous
    //printf("<br>\n");
    printf("<label for='exampleFormControlSelect1'><b>Anonymous</b></label>\n");
    printf("</br>\n");
    printf("<select class='form-control' id='exampleFormControlSelect1' name='r_anonimo'>\n");
    printf("<option value='option1' selected>Habilitar Anonymous</option>\n");
    printf("<option value='option2'>Deshabilitar Anonymous</option>\n");
    printf("</select></div></fieldset>\n");

    printf("<fieldset class='form-group'>\n");
    printf("<div class='row' style='margin-left: 5%;'>\n");
    printf("<div class='form-group'>\n");
        //Estado Cuentas Locales
    system("grep 'local_enable=YES' /etc/vsftpd.conf > /srv/www/cgi-bin/tempo1.txt");
    FILE * fichero2 = fopen("/srv/www/cgi-bin/tempo1.txt","r");
    char cadArchivo2[1024];
	if(fgets(cadArchivo2,100,fichero2)!=NULL){
		printf("<p style='color: green' style='font-size:10px' > Cuentas Locales Habilitado</p>\n");
	}else{
		printf("<p style='color: red' style='font-size:10px' > Cuentas Locales Deshabilitado</p>\n");
	}
    system("rm /srv/www/cgi-bin/tempo1.txt");
    //Fin Cuentas Locales
    printf("<label for='exampleFormControlSelect1'><b>Cuentas Locales</b></label>\n");
    printf("<select class='form-control' id='exampleFormControlSelect1' name='r_cuenta'>\n");
    printf("<option value='option1' selected>Habilitar cuentas locales</option>\n");
    printf("<option value='option2'>Deshabilitar cuentas locales</option>\n");
    printf("</select></div></fieldset>\n");

    printf("<fieldset class='form-group'>\n");
    printf("<div class='row' style='margin-left: 5%;'>\n");
    printf("<div class='form-group'>\n");
    //Inicio Estado Escritura
        system("grep 'write_enable=YES' /etc/vsftpd.conf > /srv/www/cgi-bin/tempo2.txt");
        FILE *  fichero3 = fopen("/srv/www/cgi-bin/tempo2.txt","r");
        char cadArchivo3[1024];
        if(fgets(cadArchivo3,100,fichero3)!=NULL){
            printf("<p style='color: green' style='font-size:10px' > Escritura Habilitada</p>\n");
        }else{
            printf("<p style='color: red' style='font-size:10px' > Escritura Deshabilitada</p>\n");
        }
        system("rm /srv/www/cgi-bin/tempo2.txt");
    //Fin Escritura
    printf("<label for='exampleFormControlSelect1'><b>Escritura</b></label>\n");
    printf("<select class='form-control' id='exampleFormControlSelect1' name='r_escritura'>\n");
    printf("<option value='option1' selected>Habilitar escritura</option>\n");
    printf("<option value='option2'>Deshabilitar escritura</option>\n");
    printf("</select></div></fieldset>\n");

    printf("<fieldset class='form-group'>\n");
    printf("<div class='row' style='margin-left: 5%;'>\n");
    printf("<div class='form-group'>\n");
        //Estado Chroot
    system("grep 'chroot_list_enable=YES' /etc/vsftpd.conf > /srv/www/cgi-bin/tempo3.txt");
    FILE * fichero4 = fopen("/srv/www/cgi-bin/tempo3.txt","r");
    char cadArchivo4[1024];
	if(fgets(cadArchivo4,100,fichero4)!=NULL){
		printf("<p style='color: green' style='font-size:10px' > Chroot Esta Habilitado</p>\n");
	}else{
		printf("<p style='color: red' style='font-size:10px' > Chroot Esta Deshabilitado</p>\n");
	}
    system("rm /srv/www/cgi-bin/tempo3.txt");
    //Fin estado Chroot
    printf("<label for='exampleFormControlSelect1'><b>Chroot</b></label>\n");
    printf("<select class='form-control' id='exampleFormControlSelect1' name='r_chroot'>\n");
    printf("<option value='option1' selected>Habilitar escritura</option>\n");
    printf(" <option value='option2'>Deshabilitar escritura</option>\n");
    printf("</select></div></fieldset>\n");

    printf("<fieldset class='form-group'>\n");
    printf("<div class='row' style='margin-left: 5%;'>\n");
    printf("<div class='form-group'>\n");
    //Estado Log
            system("grep 'log_ftp_protocol=YES' /etc/vsftpd.conf > /srv/www/cgi-bin/tempo4.txt");
            FILE * fichero5 = fopen("/srv/www/cgi-bin/tempo4.txt","r");
            char cadArchivo5[1024];
            if(fgets(cadArchivo5,100,fichero5)!=NULL){
                printf("<p style='color: green' style='font-size:10px' > Log Habilitado</p>\n");
            }else{
                printf("<p style='color: red' style='font-size:10px' > Log Deshabilitado</p>\n");
            }
            
            system("rm /srv/www/cgi-bin/tempo4.txt");
    //Fin estado Log
    printf("<label for='exampleFormControlSelect1'><b>Log</b></label>\n");
    printf("<select class='form-control' id='exampleFormControlSelect1' name='r_log'>\n");
    printf("<option value='option1' selected>Habilitar log</option>\n");
    printf("<option value='option2'>Deshabilitar escritura</option>\n");
    printf("</select></div></fieldset>\n");

    printf("<br>\n");

    printf("<input type='submit' class='btn-primary' value='Modificar' style='margin-left: 5%;width: 40%;'>\n");
	
    printf("<br><br>");
    printf("</form>");
    //Inicio listar usuarios
    
    system("awk -F: '$3 >= 1000 {print $1}' /etc/passwd > /srv/www/cgi-bin/users.txt");
    
    FILE * archUser;
    char cadUser;
    archUser = fopen("/srv/www/cgi-bin/users.txt","r");

    printf("<div class>");
    printf("<label style='color:purple'> Usuarios</label>\n ");	
    printf("<br></br>");
    printf("<textarea readonly name='usr' rows='5' cols='8'>\n");
    cadUser = fgetc(archUser);
    	while(cadUser != EOF){
		printf("%c",cadUser);
		cadUser = fgetc(archUser);
	}
	fclose(archUser);
    printf("</textarea>");
    system("rm /srv/www/cgi-bin/users.txt");
    printf("</div>\n");

    printf("<form action='/cgi-bin/EquipoZ-Enjaulados' method='POST'>");

    //Fin listar usuarios
    //Inicio enjaular usuarios
    printf("<div class>");
    printf("<label style='color:purple'> Usuario a Enjaular</label>\n");
    printf("<br></br>");
    printf("<input type='text' name='enjaulado'>");
    printf("<br></br>");
    printf("<input type='submit' value='Enjaular'>");
    
   
    printf("</form>");

    printf("<br></br>") ;  
    //Inicio estado total
    system("grep '=' /etc/vsftpd.conf > /srv/www/cgi-bin/temporal.txt");
    FILE * estadoActual;
    char cadAct;
    estadoActual = fopen("temporal.txt","r");
    
    printf("<div class>");
    printf("<label style='color:blue'> Estado de configuracion actual</label>\n ");
    printf("<textarea readonly name='Estado Actual' rows='50' cols='56' style='background:#AFEEEE'>");
    cadAct = fgetc(estadoActual);
    while(cadAct != EOF){
     printf("%c",cadAct);
     cadAct = fgetc(estadoActual);
    }   
    fclose(estadoActual);
    printf("</textarea>");
    system("rm /srv/www/cgi-bin/temporal.txt");
    //Fin Estado Actual Total
    system("</div>");
    //printf("</form>\n");
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

//Funcion para separar cadenas de texto
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
