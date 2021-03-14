#include "init.h"

//evitar
int main (void)
{

	piso_t floor;
	int n_robots;
	robot_ t * robot_list;
	int mode = recieve_data (floor, &(n_robots));
	printf ("%d \n", mode);

}

/*******************************************************************************
*	Esta funcion se encarga de recibir parametros por linea de comandos		   *
*	en tiempo de ejecucion. 												   *
*	Guarda el numero de robots, el largo y ancho del tablero y devuelve 	   *
*	el modo del juego. 														   *
*	En caso de tener un error devuelve un -1.								   *
*******************************************************************************/
int recieve_data (piso_t floor, int * n_robots)
{
	int mode;
	printf("Ingrese el numero de filas: \n");
	scanf("%d", &(floor.h));
	printf("Ingrese el numero de columnas: \n");
	scanf("%d", &(floor.w));
	printf("Ingrese el numero de robots: \n");
	scanf("%d", n_robots);
	printf("Ingrese el modo de la simulacion: \n");
	scanf("%d", &(mode));	
	if((floor.h<1)||(floor.h>100)||(floor.w<1)||(floor.w>70)||((mode!=1)&&(mode!=2))) //se controla que no se ingrese un numero invalido
	{
		mode=-1;
	}
	return mode;
}

/*******************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para las baldosas. *
*	Las inicializa en 0, lo que indica que estan sucias.					   *
*******************************************************************************/

void init_floor (piso_t floor)
{
	int n_baldosas = floor.h * floor.w;
	floor.baldosas = (baldosas_t*) calloc (n_baldosas, sizeof(char)); 
} 	

/*******************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para los robots.   *
*	Crea la lista e inicializa las coordenadas de los robots en el medio 	   *
*	de la pantalla. 														   *
*******************************************************************************/

void init_robot (robot_ t * robot_list, int n_robots, piso_t floor)    //en modo 1 manda la variable y en modo 2 seria ir aumentando en 1
{ 
	robot_list = (robot_t*) calloc (n_robots, sizeof(robot_t));
	int contador;
	for (contador=0; contador<n_robots; contador++)
	{
		robot_list[contador].x= (double) floor.w/2;  //esto esta mal (ver como definir lo de las coordenadas)
		robot_list[contador].y=	(double) floor.h/2;  //no se si el double es al pedo o que 
		robot_list[contador].angle= (double) (rand()%3599)/10;   //grados
	}
	return; 
} 







