#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define _TIME_


#include <gd.h>
#include <gdfonts.h>
#include "comun.h"
#include "utils.h"


using namespace std;

typedef char 	StringN[40];
typedef char 	StringF[20];
typedef char 	str_linea[255];
#define 	MAXLINEA 	225

typedef struct Retail
{
	StringN	sNombre;
	StringF sFecha;
	float Monto;
};

void graficar(StringN nombre,float monto, int cont) {

    gdImagePtr imagen;
    FILE *archivo;
    char titulo[513];
    int blanco, negro, color;
    gdFontPtr fuente = gdFontGetSmall();

    imagen = gdImageCreateTrueColor(IMG_WIDTH, IMG_HEIGHT);

    int y = 0;
    int mes = 0;
    int alto = 50;
    int ancho = 120;
    long maximo = 0;
    long paso = 0;
    double porcentaje = 0.0;

    if (imagen) {
        blanco = gdImageColorAllocate(imagen, 255, 255, 255);
        negro = gdImageColorAllocate(imagen, 0, 0, 0);


        // Pintamos el fondo Blanco
        gdImageFill(imagen, 0, 0, blanco);

        // Coloco el título
        memset(titulo, 0, 513);
        snprintf(titulo, 512, "VENTAS TIENDA %s:", nombre);
        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.4, 25, (unsigned char *) titulo, negro);


            // El alto máximo serán 500px que será el 100%
            alto = (int) (450 * porcentaje);


        // Monto
         gdImageString(imagen, fuente, ancho, IMG_HEIGHT - (BORDE_ALTO + alto + 60), (unsigned char *) longStr(monto), color);
         ancho += 75;


        // Pintamos Borde
        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO), BORDE_ALTO, negro);
        gdImageLine(imagen, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro);
        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), negro);
        gdImageLine(imagen, (IMG_WIDTH - BORDE_ANCHO), BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro);

          

        // Guardar imagen
        if(cont == 0)
	{
            archivo = fopen("grafico1.jpg", "wb");
	    if (archivo != NULL) {
            gdImageJpeg(imagen, archivo, 100);
            fclose(archivo);
            }
        }
	if(cont == 1)
	{
            archivo = fopen("grafico2.jpg", "wb");
	    if (archivo != NULL) {
            gdImageJpeg(imagen, archivo, 100);
            fclose(archivo);
            }
        }
	if(cont == 2)
	{
            archivo = fopen("grafico3.jpg", "wb");
	    if (archivo != NULL) {
            gdImageJpeg(imagen, archivo, 100);
            fclose(archivo);
            }
	}
	if(cont == 3)
	{
            archivo = fopen("grafico4.jpg", "wb");
	    if (archivo != NULL) {
            gdImageJpeg(imagen, archivo, 100);
            fclose(archivo);
            }
	}

        /*if (archivo != NULL) {
            gdImageJpeg(imagen, archivo, 100);
            fclose(archivo);
        }*/
        gdImageDestroy(imagen);
    }
}



void calcularM (StringN Nombre,StringF FechaI, StringF FechaT,int cont)
{
    int i=0;
    long  acum=0; 
    FILE		*pArchivo;
    str_linea   linea;
    char 		*token;
    int x=0;
    Retail 	vNombre[9999];
    StringF  fecha;
    pArchivo=fopen("ventas.csv","rt");
    
    while (!feof(pArchivo) && x==0)
	{
		fgets(linea,MAXLINEA,pArchivo);
        token = strtok(linea,"\"\";"); //primer avance    		
		if(strcmp(Nombre,token)==0)
		{
            strcpy(vNombre[i].sNombre,token);//compara nombre
            token = strtok(NULL,"; \"");//segundo avance valor mes
            
	        if(strcmp(FechaI,token)==0) //compara fecha de inicio
	        {
                token = strtok(NULL,"\";");//tercer avance valor hora 
                token = strtok(NULL,"\";");//cuarto avance monto
                
	        	acum=acum+atof(token); //monto inicial, se reinicia en caso de encontrar la fecha de inicio		          
            } 
            else //si no son iguales
            {                  
                
                if(strcmp(FechaT,token)==0)//pregunta si es el termino final por lo que avanza y guardara el ultimo monto y lo mostrara por pantalla
		        {     
                   
                     x=1; 
                     graficar(vNombre[i].sNombre,acum,cont);
                     cout<<"\nMONTO ACUMULADO: "<<acum<<endl; 
                                   
                } 
                
                
                token = strtok(NULL,"\";");//tercer avance valor hora 
                token = strtok(NULL,"\";");//cuarto avance correspondiente al monto    
                acum=acum+atof(token); //monto acumulado 
            }
             
        }  
        else // si los nombres no son iguales
        {
            token = strtok(NULL,"\";");//permiten que avance la lista
            token = strtok(NULL,"\";");
        }
   }
   
}

int main(int argc, char *argv[])
{
    StringN nombre;
    StringF fechai;
    StringF fechat;
    int op, entrada=0, i;

    for (i = 0; i < argc ; i++)
    {
        if(strcmp(argv[i],"-g")==0) entrada = 1;
        if(strcmp(argv[i],"-v")==0) entrada = 2;
    }

if(entrada == 1)
{
    /*for(size_t i = 0; i < argc; i++)
    {
        cout << i << " " << argv[i] << endl;
    }*/


    //cout<<"Ingrese fecha inicio:"<<endl;
    //cin>>fechai;
    //cout<<"Ingrese fecha de termino:"<<endl;
    //cin>>fechat;
    calcularM("CencoSux",argv[2],argv[3],0);
    calcularM("Falaferia",argv[2],argv[3],1);
    calcularM("Porahi",argv[2],argv[3],2);        
    calcularM("Replay",argv[2],argv[3],3);
}

else
{
	if(entrada == 2)
	{
 		cout<<"\nIntegrantes:\n\nDamaris Avila\nNicolas Rodriguez\nBarbara Rojas\n\n"<<endl;
 		cout<<"Fecha de compilacion: "<<endl;
        	puts(__DATE__); //Fecha de compilacion.
	}
}			
    system("pause");
}
