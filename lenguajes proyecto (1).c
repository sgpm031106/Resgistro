/*
Carrera: Ingeniería en Computación Inteligente
Materia: Lenguajes de computación
Semestre: Primero
Autores: Ángel Gerardo Luna Romo
        Erick Iván Ramírez Reyes
        Sergio Gabriel Perez Moreno
Fecha: 6/12/2021

Objetivo: Generar 10 registros de trabajadores, con clave, salario y nombre completo, para posteriormente poder ordenralos, modificarlos, eliminarlos e ingresar nuevos registros.
Datos de entrada: Opciones y datos ingresados por el usuario así como las claves, nombres, apellidos y sueldos generados aleatoriamente.
Datos de salida: Los registros modificados, ordenados, eliminados, ingresados.
*/
//Librerias utilizadas
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

//Constantes globales
#define MAX_COL 20
#define MAX_COLNOM 50
#define NUM_TRAB 10
const char nr[NUM_TRAB][MAX_COL]={"Sergio","Gabriel","Miguel","Angel","Martin","Rogelio","Erick","Alberto","Franco","Luis"};//Nombres aleatorios.
const char apr[NUM_TRAB][MAX_COL]={"Acosta","Jimenez","Moreno","Ramirez","Manriquez","Serna","Medina","Marin","Vallejo","De Leon"};//Apellidos paternos aleatorios.
const char amr[NUM_TRAB][MAX_COL]={"Mauricio","Navarro","Torres","Cruz","Villanueva","Quezada","Arevalo","Morales","Chavez","Valdez"};//Apellidos maternos aleatorios.

//Variables globales
int c[NUM_TRAB];//Arreglo de 10 registros con claves de los trabajadores de 4 digitos enteros.
float s[10]; //Arreglo de 10 registros con salarios
char n[NUM_TRAB][MAX_COL];//Solo nombre
char ap[NUM_TRAB][MAX_COL];//Solo apellido paterno
char am[NUM_TRAB][MAX_COL];//Solo apellido materno
char nomcom[NUM_TRAB][MAX_COLNOM]; //Arreglo de 10 registros con los nombres de los trabajadores.
int i,j;//Variables para los ciclos for.
int op=0;//Variable para menús.

//Declaración de funciones
void mostrartodo(); //Función que muestra clave, nombre y salario del trabajador.
int buscar(); //Busca la clave o el nombre de un trabajador.
void ordalf(int longitud);//Ordena los registros por orden alfabético.
void claveordenada();//Ordena los registros por la clave de manera ascendentente o descendente.
void modificar(int p);//Modifica un nombre u apellido del trabajador.
void salarioordenado();//Ordena los registros segun el salario.
void nuevoreg(int v);//Genera un nuevo registro.
void eliminarreg(int z);//Elimina un registro.

int main(){
	int random=0,randomm=0,randommm=0;//Variables para generar nombres aleatorios
	int pos=0,tam=0,cont=0;
	setlocale(LC_ALL, "");
	srand(time(NULL));
	for(i=0;i<NUM_TRAB;i++){ //Generación de clave y salario aleatoriamente
		c[i]=rand()%9000+999;
		s[i]=8000+rand()%20000;
	}
	for(i=0;i<NUM_TRAB;i++){//Generación de nombres de los trabajadores aleatoriamente.
		random=rand()%NUM_TRAB;
		randomm=rand()%NUM_TRAB;
		randommm=rand()%NUM_TRAB;
		strcpy(n[i],nr[random]);
		strcpy(ap[i],apr[randomm]);
		strcpy(am[i],amr[randommm]);
		sprintf(nomcom[i],"%s %s %s", n[i], ap[i], am[i]);
	}
	do{
		//Menu principal
		system("cls");
		printf ("MENÚ\n\n");
		printf ("¿Qué quieres hacer?\n\n");
		printf ("1) Mostrar registros\n");
		printf ("2) Buscar un registro\n");
		printf ("3) Ordenar registros alfabeticamente\n");
		printf ("4) Ordenar registros por clave\n");
		printf ("5) Ordenar registros por salario\n");
		printf ("6) Insertar un nuevo registro\n");
		printf ("7) Eliminar un registro existente\n");
		printf ("8) Modificar datos de algún trabajador\n");
		printf ("9) Salir del programa\n");
		printf ("\nIntroduzca una opción: ");
		scanf ("%d",&op);
		switch (op){
			case 1://Mostrar los registros de los trabajadores.
				mostrartodo(); //Llamado a la función mostrartodo().
				break;
			case 2://Buscar un registro
				buscar();//Llamado a la funcion buscar().
				break;
			case 3://Oordenar registros alfabeticamente.
				tam = sizeof(nomcom)/sizeof(nomcom[0]);
				ordalf(tam);
				break;
			case 4://Ordenar registros por clave.
				claveordenada();
				break;
			case 5://Odenar registros por salario.
				salarioordenado();
				break;
			case 6://Insertar un nuevo registro.
				cont=0;
				for(i=0; i<NUM_TRAB; i++){
					if (c[i]==0000){
						nuevoreg(i);//Llamado a la función nuevoreg().
						break;
					}
					cont++;
				}
				if (cont==NUM_TRAB){
					printf("\nNo hay espacio para agregar un nuevo registro. Elimina un registro existente para agregar uno nuevo.\n\n");
					system("pause");
				}
				break;
			case 7://Eliminar un registro.
				pos=buscar();//Registro que se eliminara.
				if (pos==500){
					break;
				}
				else{
					eliminarreg(pos);//Llamado a la función eliminar.
				}
				break;
			case 8://Modificar datos de algún trabajador.
				pos=buscar();//Trabajador que se modificará.
				if (pos==500){
					break;
				}
				else{
					modificar(pos);//Llamado a la funcion modificar().
				}
				break;
			case 9://Salida del programa.
				system ("cls");
				printf ("\nSaliendo\nGRACIAS POR PROBAR NUESTRO PROGRAMA\n");
				break;
			default://Regresa a pedir nuevamente la opción.
				printf ("\nOpción no válida\n");
				system("pause");
				break;
		}
	}while (op!=9);
	system("pause");
}

//Cuerpo de las funciones
void mostrartodo(){
	system ("cls");
	printf(" |Trabajadores| ");
	printf("\n\n");
	printf("   CLAVE      NOMBRE DEL TRABAJADOR\t\t      SALARIO MENSUAL	\n");
	printf("   ------     ---------------------\t\t      ---------------	\n");
	for(i=0;i<NUM_TRAB;i++){
		strupr(nomcom[i]);
		printf(" || %4d ||   %-30s\t||	$%.2f	||\n", c[i],nomcom[i],s[i]);
	}
	printf("\n");
	system ("pause");
}
int buscar(){
	char nombre [MAX_COLNOM];
	int clave,p,cont;
	do{
		p=0;
		system ("cls");
		printf ("\t¿Cómo deseas buscar al trabajador?\n");
		printf ("\t1) Clave de trabajador\n");
		printf ("\t2) Nombre de trabajador\n");
		printf ("\t3) Regresar al menú\n");
		printf ("\n\tIntroduzca una opción: ");
		scanf("%d",&op);
		switch (op){
			case 1:
				printf("\n\tIntroduce la clave del trabajador que deseas buscar: ");
				scanf("%d",&clave);
				cont=0;
				for (i=0; i<NUM_TRAB; i++){
					if (c[i]==clave){
						p=i;
						printf ("\n¡Registro encontrado!\n\n");
						printf("   CLAVE      NOMBRE DEL TRABAJADOR\t\t      SALARIO MENSUAL	\n");
						printf("   ------     ---------------------\t\t      ---------------	\n");
						printf(" || %d ||   %-30s\t||	$%.2f	||\n", c[i],nomcom[i],s[i]);
					}
					else{
						cont++;
					}
				}
				printf("\n");
				if (cont==NUM_TRAB){
					p=500;
					printf("\tClave no encontrada\n\n");
				}
				break;
			case 2:
				printf("\n\tIntroduce el nombre completo del trabajador que deseas buscar (sin acentos): ");
				fflush(stdin);
				gets(nombre);
				strupr(nombre);
				cont=0;
				for (i=0; i<NUM_TRAB; i++){
					if (strcmp(nombre,nomcom[i])==0){
						p=i;
						printf ("\n¡Registro encontrado!\n\n");
						printf("   CLAVE      NOMBRE DEL TRABAJADOR\t\t      SALARIO MENSUAL	\n");
						printf("   ------     ---------------------\t\t      ---------------	\n");
						printf(" || %d ||   %-30s\t||	$%.2f	||\n", c[i],nomcom[i],s[i]);
					}
					else{
						cont++;
					}
				}
				printf("\n");
				if(cont==NUM_TRAB){
					p=500;
					printf("\tNombre no encontrado\n\n");
				}
				break;
			case 3:
				printf("\tRegresando...\n\n");
				p=500;
				break;
			default:
				printf("\tOpción no válida\n\n");	
				break;
		}
		system ("pause");
	}while (op!=1 && op!=2 && op!=3);
	return p;
}
void ordalf(int longitud){
    char ntemp[MAX_COLNOM];
    int ctemp=0;
    float stemp=0;
    int sig=0;
    do{
    	system ("cls");
	    printf("\t¿Cómo deseas ordenar alfabéticamente los registros?\n");
	    printf("\t1) Ascendente A-Z\n");
	    printf("\t2) Descendente Z-A\n");
	    printf("\t3) Regresar al menú\n");
	    printf("\n\tIntroduzca una opción: ");
	    scanf("%d",&op);
	    switch (op){
	    	case 1:
			    for (i=0;i<longitud;i++){
			    	for (j=0;j<longitud-1;j++){
			    		sig=j+1;
			    		if (strcmp(nomcom[j],nomcom[sig])>0)
						{
							//Nombres
							memcpy(ntemp,nomcom[j],MAX_COLNOM);
							memcpy(nomcom[j],nomcom[sig],MAX_COLNOM);
							memcpy(nomcom[sig],ntemp,MAX_COLNOM);
							//Claves
							ctemp=c[j];
							c[j]=c[sig];
							c[sig]=ctemp;
							//Salarios
							stemp=s[j];
							s[j]=s[sig];
							s[sig]=stemp;
						} 
			    	}
			    }
			    printf ("\nLos registros se han ordenado alfabeticamente de manera ascendente\n\n");
			    break;
			case 2:
				for (i=0;i<longitud;i++){
			    	for (j=0;j<longitud-1;j++){
			    		sig=j+1;
			    		if (strcmp(nomcom[j],nomcom[sig])<0)
						{
							//Nombres
							memcpy(ntemp,nomcom[j],MAX_COLNOM);
							memcpy(nomcom[j],nomcom[sig],MAX_COLNOM);
							memcpy(nomcom[sig],ntemp,MAX_COLNOM);
							//Claves
							ctemp=c[j];
							c[j]=c[sig];
							c[sig]=ctemp;
							//Salarios
							stemp=s[j];
							s[j]=s[sig];
							s[sig]=stemp;
						} 
			    	}
			    }
			    printf ("\nLos registros se han ordenado alfabeticamente de manera descendente\n\n");
				break;
			case 3:
				printf ("\tRegresando...\n\n");
				break;
			default:
				printf ("\tOpción no válida\n\n");
	    }
	    system ("pause");
	}while(op!=1 && op!=2 && op!=3);
}
void claveordenada(){
	char ntemp[MAX_COLNOM];
    int ctemp=0;
    float stemp=0;
	do{
		system("cls");
		printf("\t¿Cómo quieres ordenar las claves de tu registro?\n");
		printf("\t1) En orden ascendente (0-9)\n");
		printf("\t2) En orden descendente (9-0)\n");
		printf("\t3) Regresar al menú\n");
		printf("\n\tIntroduzca una opción: ");
		scanf("%d", &op);
		switch(op){
			case 1:
				for(i=0;i<9;i++){
					for(j=i+1;j<NUM_TRAB;j++){
						if(c[j] < c[i]){
							//Claves
							ctemp=c[i];
							c[i]=c[j];
							c[j]=ctemp;
							//Nombres
							memcpy(ntemp,nomcom[i],MAX_COLNOM);
							memcpy(nomcom[i],nomcom[j],MAX_COLNOM);
							memcpy(nomcom[j],ntemp,MAX_COLNOM);
							//Salarios
							stemp=s[i];
							s[i]=s[j];
							s[j]=stemp;
						}
					}
				}
				printf ("\n\tLos registros se han ordenado por clave de manera ascendente\n\n");
				system("pause");
				break;
			case 2:
				for(i=0;i<9;i++){
					for(j=i+1;j<NUM_TRAB;j++){
						if(c[j] > c[i]){
							//Claves
							ctemp=c[i];
							c[i]=c[j];
							c[j]=ctemp;
							//Nombres
							memcpy(ntemp,nomcom[i],MAX_COLNOM);
							memcpy(nomcom[i],nomcom[j],MAX_COLNOM);
							memcpy(nomcom[j],ntemp,MAX_COLNOM);
							//Salarios
							stemp=s[i];
							s[i]=s[j];
							s[j]=stemp;
						}
					}
				}
				printf ("\n\tLos registros se han ordenado por clave de manera descendente\n\n");			
				system("pause");
				break;
			case 3:
				printf("\n\tRegresando...\n\n");
				break;	
			default:
				printf("\n\tOpción no válida\n\n");
				system("pause");
				break;
			}
	}while(op!=1 && op!=2 && op!=3);
}
void salarioordenado(){
	char ntemp[MAX_COLNOM];
    int ctemp=0;
    float stemp=0;
	do{
		system("cls");
		printf("\t¿Cómo quieres ordenar los salarios de tu registro?\n");
		printf("\t1) De mayor a menor salario\n");
		printf("\t2) De menor a mayor salario\n");
		printf("\t3) Regresar al menú\n");
		printf("\n\tIntroduzca una opción: ");
		scanf("%d", &op);
		switch(op){
			case 1:
				for(i=0;i<9;i++){
					for(j=i+1;j<NUM_TRAB;j++){
						if(s[j] > s[i]){
							//Salarios
							stemp=s[i];
							s[i]=s[j];
							s[j]=stemp;
							//Nombres
							memcpy(ntemp,nomcom[i],MAX_COLNOM);
							memcpy(nomcom[i],nomcom[j],MAX_COLNOM);
							memcpy(nomcom[j],ntemp,MAX_COLNOM);
							//Claves
							ctemp=c[i];
							c[i]=c[j];
							c[j]=ctemp;
						}
					}
				}
				printf ("\n\tLos registros se han ordenado del salario mayor al menor\n\n");
				break;
			case 2:
				for(i=0;i<9;i++){
					for(j=i+1;j<NUM_TRAB;j++){
						if(s[j] < s[i]){
							//Salarios
							stemp=s[i];
							s[i]=s[j];
							s[j]=stemp;
							//Nombres
							memcpy(ntemp,nomcom[i],MAX_COLNOM);
							memcpy(nomcom[i],nomcom[j],MAX_COLNOM);
							memcpy(nomcom[j],ntemp,MAX_COLNOM);
							//Claves
							ctemp=c[i];
							c[i]=c[j];
							c[j]=ctemp;
						}
					}
				}
				printf ("\n\tLos registros se han ordenado del salario menor al mayor\n\n");
				break;
			
			case 3:
				printf("\n\tRegresando...\n\n");
				break;
				
			default:
				printf("\n\tOpción no válida\n\n");
				break;
		}
		system("pause");
	}while(op!=1 && op!=2 && op!=3);
}
void nuevoreg(int v){
	int nueva=0,cont=0;
	float sln=0.0;
	do{
		system("cls");
		printf("\t¿Cómo quieres generar tu nuevo registro?\n");
		printf("\t1) Aleatoriamente\n");
		printf("\t2) Introducirlo por ti mismo\n");
		printf("\t3) Regresar al menú\n");
		printf("\n\tIntroduzca una opción: ");
		scanf("%d",&op);
		switch(op){
			case 1:
				for(i=0;i<NUM_TRAB;i++){ //Generación de clave y salario aleatoriamente
					c[v]=rand()%9000+999;
					s[v]=8000+rand()%20000;
				}
				//Generación de nombre aleatoriamente
				strcpy(n[v],nr[rand()%NUM_TRAB]);
				strcpy(ap[v],apr[rand()%NUM_TRAB]);
				strcpy(am[v],amr[rand()%NUM_TRAB]);
				sprintf(nomcom[v],"%s %s %s", n[v], ap[v], am[v]);
				strupr(nomcom[v]);
				printf ("\n¡Registro generado aleatoriamente\n\n");
				printf("   CLAVE      NOMBRE DEL TRABAJADOR\t\t      SALARIO MENSUAL	\n");
				printf("   ------     ---------------------\t\t      ---------------	\n");
				printf(" || %d ||   %-30s\t||	$%.2f	||\n", c[v],nomcom[v],s[v]);
				system ("pause");
				break;
			case 2:
				do{
					system("cls");
					printf("\tIntroduce una clave de 4 dígitos enteros: ");
					scanf("%d",&nueva);
					if (nueva==0){
						printf("\n\tClave inválida\n");
						system ("pause");
						continue;
					}
					else if (nueva>9999){
						printf("\n\tLa clave es demasiado grande\n\n");
						system ("pause");
						continue;
					}
					else if (nueva<1000){
						printf ("\n\tLa clave es demasiado corta\n\n");
						system ("pause");
						continue;
					}
					else{
						for (i=0; i<NUM_TRAB; i++){
							if (c[i]==nueva){
								printf ("\tLa clave ya existe\n\n");
								system ("pause");
								break;
							}
							cont++;
						}
					}
					if (cont!=NUM_TRAB){
						continue;
					}
					else{
						c[v]=nueva;
						printf("\n\tClave guardada\n\n");
						system ("pause");
						break;
					}
				}while (1);
				system ("cls");
				printf("\tIntroduce el nombre (sin apellidos ni acentos) del trabajador: ");
				fflush(stdin);
				gets (n[v]);
				printf("\tIntroduce el apellido paterno (sin acentos): ");
				fflush(stdin);
				gets (ap[v]);
				printf("\tIntroduce el apellido materno (sin acentos): ");
				fflush(stdin);
				gets (am[v]);
				sprintf(nomcom[v],"%s %s %s", n[v], ap[v], am[v]);
				strupr(nomcom[v]);
				printf("\tNombre guardado\n\n");
				system ("pause");
				do{
					printf("\n\tIntroduce el salario del trabajador: ");
					scanf("%f",&sln);
					if (sln<1000){
						printf("\n\tNo puedes establecer un salario menor a $1,000.00\n\n");
						system ("pause");
						continue;
					}
					else if (sln>100000){
						printf ("\n\tNo puedes establecer un salario mayor a $100,000.00\n\n");
						system ("pause");
						continue;
					}
					else{
						s[v]=sln;
						printf("\n\tSalario guardado\n\n");
						system ("pause");
						break;
					}
				}while(1);
				printf ("\n¡Registro Guardado\n\n");
				printf("   CLAVE      NOMBRE DEL TRABAJADOR\t\t      SALARIO MENSUAL	\n");
				printf("   ------     ---------------------\t\t      ---------------	\n");
				printf(" || %d ||   %-30s\t||	$%.2f	||\n", c[v],nomcom[v],s[v]);
				system ("pause");
				break;
			case 3:
				printf ("\n\tRegresando...\n\n");
				system ("pause");
				break;
			default:
				printf("\tOpción no válida\n\n");
				system ("pause");
				break;
		}
	}while(op!=1 && op!=2 && op!=3);
}
void eliminarreg(int z){
	printf("\n\tDeseas eliminar este registro\n\tIngresa 1 para SÍ y 2 para NO\n");
	printf("\n\tIntroduzca una opción: ");
	scanf("%d",&op);
	switch(op){
		case 1:
			c[z]=0000;
			s[z]=0.00;
			strcpy(n[z],"");
			strcpy(ap[z],"");
			strcpy(am[z],"");
			strcpy(nomcom[z],"");
			printf("\n\tEl registro a sido eliminado\n\n");
			break;
		case 2:
			printf ("\n\tEl registro no se eliminó\n\n");
			break;
		default:
			printf ("\n\tOpción no válida\n\n");
			break;
	}
	system ("pause");
}
void modificar(int p){
	int nueva=0,num,cont=0;
	float sln=0.0;
	do{
		printf ("\n\t¿Qué quieres modificar?\n\n");
		printf ("\t1) Modificar la clave del trabajador\n");
		printf ("\t2) Modificar el nombre del trabajador\n");
		printf ("\t3) Modificar el salario del trabajador\n");
		printf ("\t4) Regresar al menú\n");
		printf ("\n\tIntroduzca una opción: ");
		scanf ("%d",&op);
		switch (op){
			case 1:
				do{
					cont=0;
					printf ("\n\tModificar clave\n");
					printf("\tIntroduce una nueva clave de 4 dígitos enteros: ");
					scanf("%d",&nueva);
					if (nueva==0){
						printf("\n\tClave inválida\n");
						system ("pause");
						continue;
					}
					else if (nueva>9999){
						printf("\n\tLa clave es demasiado grande\n\n");
						system ("pause");
						continue;
					}
					else if (nueva<1000){
						printf ("\n\tLa clave es demasiado corta\n\n");
						system ("pause");
						continue;
					}
					else{
						for (i=0; i<NUM_TRAB; i++){
							if (c[i]==nueva){
								printf ("\tLa clave ya existe\n");
								system ("pause");
								break;
							}
							cont++;
						}
					}
					if (cont!=NUM_TRAB){
						continue;
					}
					else if (nueva==c[p]){
						printf ("\tLa clave seguirá siendo la misma\n");
						c[p]=nueva;
						printf("\tClave modificada con éxito\n");
						system ("pause");
						break;
					}
					else{
						c[p]=nueva;
						printf("\tClave modificada con éxito\n");
						system ("pause");
						break;
					}
				}while (1);
				break;
			case 2:
				printf("\n\tModificar nombre\n");
				printf("\t¿Qué deseas modificar?\n");
				printf("\t1) Nombre completo\n");
				printf("\t2) Solo el nombre\n");
				printf("\t3) Apellido paterno\n");
				printf("\t4) Apellido materno\n");
				printf ("\n\tIntroduzca una opción: ");
				scanf("%d",&num);
				if (num==1){
					printf("\tIntroduce el nombre: ");
					fflush(stdin);
					gets (n[p]);
					printf("\tIntroduce el apellido paterno: ");
					fflush(stdin);
					gets (ap[p]);
					printf("\tIntroduce el apellido materno: ");
					fflush(stdin);
					gets (am[p]);
					sprintf(nomcom[i],"%s %s %s", n[p], ap[p], am[p]);
					printf("\tNombre modificado con éxito\n\n");
					system ("pause");
				}
				if (num==2){ //Modificar nombre
					printf("\tIntroduce el nuevo nombre: ");
					fflush(stdin);
					gets (n[p]);
					strcpy(nomcom[p], n[p]);
					strcat(nomcom[p], " ");
					strcat(nomcom[p], ap[p]);
					strcat(nomcom[p], " ");
					strcat(nomcom[p], am[p]);
					strupr(nomcom[p]);
					printf("\t¡Nombre modificado con éxito!\n\n");
					system ("pause");
				}
				if (num==3){//Modificar apellido paterno
					printf("\tIntroduce el nuevo apellido paterno: ");
					fflush(stdin);
					gets (ap[p]);
					strcpy(nomcom[p],n[p]);
					strcat(nomcom[p], " ");
					strcat(nomcom[p], ap[p]);
					strcat(nomcom[p], " ");
					strcat(nomcom[p], am[p]);
					strupr(nomcom[p]);
					printf("\t¡Apellido modificado con éxito!\n\n");
				}
				if (num==4){//Modificar apellido materno
					printf("\tIntroduce el nuevo apellido materno: ");
					fflush(stdin);
					gets(am[p]);
					strcpy(nomcom[p],n[p]);
					strcat(nomcom[p], " ");
					strcat(nomcom[p], ap[p]);
					strcat(nomcom[p], " ");
					strcat(nomcom[p], am[p]);
					strupr(nomcom[p]);
					printf("\t¡Apellido modificado con éxito!\n\n");
				}
				getch();
				break;
			case 3:
				do{
					printf ("\n\tModificar salario\n");
					printf("\tIntroduce el nuevo salario del trabajador: ");
					scanf("%f",&sln);
					if (sln<1000){
						printf("\n\tNo puedes establecer un salario menor a $1,000.00\n\n");
						system ("pause");
						continue;
					}
					else if (sln>100000){
						printf ("\n\tNo puedes establecer un salario mayor a $100,000.00\n\n");
						system ("pause");
						continue;
					}
					else{
						s[p]=sln;
						printf("\n\tSalario modificado con éxito\n\n");
						system ("pause");
						break;
					}
				}while(1);
				break;
			case 4:
				printf("\tRegresando...\n\n");
				system ("pause");
				break;
			default:
				printf("\tOpción no válida\n\n");
				system ("pause");
				break;
		}
	}while(op!=1 && op!=2 && op!=3 && op!=4);
}
