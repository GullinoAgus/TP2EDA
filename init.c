#include "init.h"


/*main(int argc, char*argv[]):
* pCallback_t p = &recieve_data
* data_t data = {.largo=0, .ancho=0, .modo=0 , .robots=0};
* data_t * userData = &data;
* 
* int var = parseCmdLine(argc, argv, p, userData) --> si esto da bien:
* init_floor(&floor, userData);
* robots = init_robot (data.robots, &floor);
* /



/************************************************************************************
*	Esta funcion se encarga de acomodar el numero recibido por linea de				*
*	comandos a un numero (ya que se recibe como char).								*
*************************************************************************************/
int set_number(char* value);

/************************************************************************************
*	Esta funcion es el callback llamado por parseCmdLine. Se encarga de	verificar	*
*	si las opciones ingresadas son correctas y llena la estructura.					*
*	En el caso de tener un error devuelve 0, sino devuelve 1.						*
*************************************************************************************/
int recieve_data(char* key, char* value, void* userData) //callback 
{
    int ret_value = 1;
    int number;
    if (key == NULL) //si hay un parametro suelto devuelve error
    {
        ret_value = 0;
    }
    else //es opcion
    {
        number = set_number(value);
        if ((number == -1)||(number==0))  //si se ingreso un valor invalido
        {
            ret_value = 0;
        }
        else if (!strcmp("largo", key))
        {
            if ((number > 70)||((data_t*)userData)->largo)      //si el valor recibido esta en el rango correcto continuamos
            {
                ret_value = 0;
            }
            else
            {
                ((data_t*)userData)->largo = number;
            }
        }
        else if (!strcmp("ancho", key))
        {
            if ((number > 100) || ((data_t*)userData)->ancho)   //si el valor recibido esta en el rango correcto continuamos
            {
                ret_value = 0;
            }
            else
            {
                ((data_t*)userData)->ancho = number;
            }
        }
        else if (!strcmp("modo", key))
        {
            if (((number != 1) && (number != 2))|| ((data_t*)userData)->modo)   //si el valor recibido esta en el rango correcto continuamos
            {
                ret_value = 0;
            }
            else
            {
                ((data_t*)userData)->modo = number;
            }
        }
        else if (!strcmp("robots", key))
        {
            if (((data_t*)userData)->robots)
            {
                ret_value = 0;
            }
            else
            {
                ((data_t*)userData)->robots = number;
            }
        }
        else //si la clave no existe
        {
            ret_value = 0;
        }
    }
    return ret_value;
}

/********************************************************************************
*	Esta funcion se encarga de acomodar el numero recibido por linea de			*
*	comandos a un numero (ya que se recibe como char). si devuele -1			*
*	es porque se ingreso un caracter invalido.									*
*********************************************************************************/
int set_number(char* value)
{
    int number = 0;
    int error = 0;
    int cifra = 0;
    while ((value[cifra] != 0) && (!error))  //mientras no sea el terminador del string
    {
        if ((value[cifra] < 48) || (value[cifra] > 57)) //caracter invalido (no es un numero)
        {
            error = 1;
        }
        else
        {
            number *= 10;
            number += (value[cifra] - 48); //acomodo de char a int
            cifra++;
        }
    }
    if (error)
    {
        number = -1;
    }
    return number;
}

/************************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para las baldosas		*
*	Las inicializa en 0, lo que indica que estan sucias.							*
*************************************************************************************/

void init_floor(piso_t* floor, data_t* userData)
{
    floor->h = userData->largo;
    floor->w = userData->ancho;
    int n_baldosas = floor->h * floor->w;
    floor->baldosas = (baldosa_t*)calloc(n_baldosas, sizeof(baldosa_t));
}

/************************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para los robots.		*
*	Crea la lista e inicializa las coordenadas de los robots en el medio			*
*	de la pantalla. 																*
*	Devuelve un puntero al arreglo que contiene a los robots.						*
*************************************************************************************/

robot_t* init_robot(int n_robots, piso_t* floor)
{
    robot_t* robot_list = (robot_t*)calloc(n_robots+1, sizeof(robot_t));
    int contador;
    for (contador = 0; contador < n_robots; contador++)
    {
        robot_list[contador].x = (double)(rand() % (floor->w * 10)) / 10.0;
        robot_list[contador].y = (double)(rand() % (floor->h * 10)) / 10.0;
        robot_list[contador].angle = (double)(rand() % 3599) / 10;   //grados
    }

    robot_list[n_robots].x = -1;

    return robot_list;
}



