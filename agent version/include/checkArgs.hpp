#ifndef _CHECKARGS_H_
#define _CHECKARGS_H_

#include <unistd.h>

extern char *optarg;
extern int optind, opterr, optopt;

class checkArgs {
private:
	// 1) Modificar esta sección
	const std::string optString = "r:c:i:s:h";
	
	const std::string opciones = "-r NROWS -c NCOLS -i ITERATIONS -s PROBLIVE [-h]";

	const std::string descripcion  = "Descripción:\n"
								     "\t-r   Número de filas\n"
									 "\t-c   Número de columnas\n"
									 "\t-i   Número de iteraciones\n"
									 "\t-s   Probabilidad incial de que una célula esté viva\n";
	
	typedef struct args_t{
		int32_t NROWS;
		int32_t NCOLS;
		int32_t ITERATIONS;
		float   PROBLIVE;
	} args_t;
	
	// 2) Modificar constructor
	// 3) Modificar ciclo "getopt" en método checkArgs::getArgs()
	// 4) Recuerde que para compilar nuevamente, y por tratarse
	//    de un archivo header, debe hacer primero un make clean
	
	args_t  parametros;
	
	int argc;
	char **argv;

	
public:
	checkArgs(int _argc , char **_argv);
	~checkArgs();
	args_t getArgs();
	
private:
	void printUsage();
	
	
};

checkArgs::checkArgs(int _argc , char **_argv){
	parametros.NROWS        = 0;
	parametros.NCOLS        = 0;
	parametros.ITERATIONS   = 0;
	parametros.PROBLIVE     = 0.0;
	
	argc = _argc;
	argv = _argv;
	
}

checkArgs::~checkArgs(){
	
}

checkArgs::args_t checkArgs::getArgs(){
	int opcion;
	
	while ((opcion = getopt (argc, argv, optString.c_str())) != -1){
		switch (opcion) {
			case 'r':
					parametros.NROWS = atoi(optarg);
					break;
			case 'c':
					parametros.NCOLS = atoi(optarg);
					break;
			case 'i':
					parametros.ITERATIONS = atoi(optarg);
					break;
			case 's':
					parametros.PROBLIVE = atof(optarg);
					break;
			case 'h':
			default:
					printUsage();
					exit(EXIT_FAILURE);
		}
	}

	if ( parametros.NROWS <=0 ||
		 parametros.NCOLS <= 0 ||
		 parametros.ITERATIONS <= 0 ||
	     parametros.PROBLIVE <= 0.0 || parametros.PROBLIVE > 1.0) {
		printUsage();
		exit(EXIT_FAILURE);
	}
	
	return(parametros);
}

void checkArgs::printUsage(){
	std::cout << "Uso: " <<
		argv[0] << " " << opciones << " " << descripcion << std::endl;
}



#endif
