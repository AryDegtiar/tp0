#include "client.h"
#include <commons/txt.h>
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	if (logger == NULL) {
        printf("Error al iniciar el logger\n");
        return 1; // Salir con un código de error
    }
	log_info(logger, "Soy un log");
	log_info(logger, "Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	if (config == NULL) {
		// ¡No se pudo crear el config!
		// Terminemos el programa
		exit("error al cargar config");
	}

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	/*	De esta forma se puede verificar alguna clave
	bool existeClave = config_has_property(config, "CLAVE");
	if (existeClave){
		printf("EXISTE CLAVE\n");
	}else{
		printf("NO EXISTE CLAVE\n");
	}
	*/

	// Obtengo las variables
	valor = config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");

	// Loggeamos el valor de config
	log_info(logger, "%s", valor);
	log_info(logger, "%s", ip);
	log_info(logger, "%s", puerto);

	/* ---------------- LEER DE CONSOLA ---------------- */

	
	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("./tp0.log","TP0 cliente", true, LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	char *name_config = "cliente.config";

	t_config* nuevo_config;
	
	// obtengo el path actual y le agrego el nombre del archivo de conf (name_config)
	char *current_dir = getcwd(NULL, 0);
    	//printf("El directorio actual es %s\n", current_dir);
	char *full_path = malloc(strlen(current_dir) + strlen("/") + strlen(name_config) + 1); 
	strcpy(full_path, current_dir);
	strcat(full_path, "/");
	strcat(full_path, name_config);
		//printf("El directorio completa es %s\n", full_path);
	
	// Creo la nueva configuracion
	nuevo_config = config_create(full_path);
	
	// Libero la memoria asignada
    free(current_dir);
    free(full_path);

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// Leo la primera linea
	leido = readline("> ");
	// Itero hasta que se ingrese un string vacio
	while(strcmp(leido, "") > 0){
		log_info(logger, leido);
		leido = readline("> ");
	}

	// Libero memoria
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
}
