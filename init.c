#include "init.h"

/*evitar
int main (void)
{

	piso_t floor;
	piso_t * floor_pointer = &floor;
	int n_robots;
	int mode = recieve_data (floor_pointer, &(n_robots));
	init_floor (floor_pointer);
	robot_t * robot_list = init_robot (n_robots, floor_pointer);
	printf ("EL MODO: %d \n", mode);
	printf("ALTURA Y ANCHO: %d , %d \n", floor.h, floor.w);
	printf("PRUEBA BALDOSA: %d \n", (int)floor.baldosas[0]);
	printf("PRUEBA ROBOT, x y y angle: %f, %f, %f \n", robot_list[0].x, robot_list[0].y, robot_list[0].angle);

}*/
/*******************************************************************************
*	Esta funcion se encarga de recibir parametros por linea de comandos		   *
*	en tiempo de ejecucion. 												   *
*	Guarda el numero de robots, el largo y ancho del tablero y devuelve 	   *
*	el modo del juego. 														   *
*******************************************************************************/
int recieve_data (piso_t * floor, int * n_robots)
{
	int mode;
	printf("Ingrese el numero de filas: ");
	scanf("%d", &(floor->h));
	while ((floor->h<1)||(floor->h>100))
	{
		printf("Este numero no esta permitido.\nIngrese el numero de filas: ");
		scanf("%d", &(floor->h));
	}	
	printf("Ingrese el numero de columnas: ");
	scanf("%d", &(floor->w));
	while ((floor->w<1)||(floor->w>70))
	{
		printf("Este numero no esta permitido.\nIngrese el numero de columnas: ");
		scanf("%d", &(floor->w));
	}
	printf("Ingrese el numero de robots: ");
	scanf("%d", n_robots);
	printf("Ingrese el modo de la simulacion: ");
	scanf("%d", &(mode));	
	while((mode!=1)&&(mode!=2))
	{
		printf("Este numero no esta permitido.\nIngrese el modo de la simulacion: ");
		scanf("%d", &(mode));
	}
	return mode;
}

/*******************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para las baldosas. *
*	Las inicializa en 0, lo que indica que estan sucias.					   *
*******************************************************************************/

void init_floor (piso_t * floor)
{
	int n_baldosas = floor->h * floor->w;
	floor->baldosas = (baldosa_t*) calloc (n_baldosas, sizeof(baldosa_t)); 
} 	

/*******************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para los robots.   *
*	Crea la lista e inicializa las coordenadas de los robots en el medio 	   *
*	de la pantalla. 														   *
*	Devuelve un puntero al arreglo que contiene a los robots				   *
*******************************************************************************/

robot_t * init_robot (int n_robots, piso_t * floor)    //en modo 1 manda la variable y en modo 2 seria ir aumentando en 1
{ 
	robot_t* robot_list = (robot_t*) calloc (n_robots + 1, sizeof(robot_t));
	int contador;
	for (contador=0; contador<n_robots; contador++)
	{
		robot_list[contador].x = (double) (rand()%(floor->w * 10))/10.0;			//esto esta mal (ver como definir lo de las coordenadas)
		robot_list[contador].y =	(double)(rand() % (floor->h * 10)) / 10.0;  //no se si el double es al pedo o que 
		robot_list[contador].angle = (double) (rand()%3600)/10.0;					//grados
	}
	robot_list[n_robots].x = -1;
	return robot_list; 
} 



