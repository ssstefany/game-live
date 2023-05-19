#include <global.h>
#include <checkArgs.hpp>
#include <clock.h>
#include <agent.h>
#include <environment.h>

int main(int argc, char *argv [])
{
	uint32_t filas;
	uint32_t columnas;
	uint32_t iteraciones;
	float    probLive;
	uint32_t typeOfProc;			//tipo de procesamiento, 0: secuencial, 1: vectorial
	uint32_t display;
	
	uint32_t sequentialProc {0};
	uint32_t vectorialProc {1};
	float sumSeq {}, sumVec {}, avgSeq {}, avgVec {};

	checkArgs* argumentos = new checkArgs(argc, argv);

	filas       = argumentos->getArgs().NROWS;
	columnas    = argumentos->getArgs().NCOLS;
	iteraciones = argumentos->getArgs().ITERATIONS;
	probLive    = argumentos->getArgs().PROBLIVE;
	typeOfProc	= argumentos->getArgs().TYPEOFPROC;
	display		= argumentos->getArgs().DISPLAY;

	//Crear tamaño del ambiente
	CoordXY  size_env = {columnas, filas};
	// Crear el ambiente
	Environment* sequentialUniverse = new Environment(size_env);
	Environment* vectorUniverse{nullptr};

	// Inicializar ambiente: crear los agentes (celulas), añadirlos al ambiente y establecer vecinos 

	// Sequiential Universe: procesamiento secuencial	
	sequentialUniverse->initEnvironment(probLive);
	// Vector Universe : procesamiento vectorial
	if (typeOfProc == 1) {
		vectorUniverse = new Environment(size_env);
		vectorUniverse->initEnvironment(probLive);
	};

	for(uint32_t it = 0; it < iteraciones; it++) {
		
		//Si se activa display mostrar el tablero
		if (display) sequentialUniverse->displayBoard(it);

		//Aplicar reglas a la generacion actual
		//imprimir generación y el tiempo de procedimiento secuencial
		//actualizar los estados de los agentes
		sumSeq += measureTime([&](){sequentialUniverse->applyAgentsRules(sequentialProc);});
		sequentialUniverse->printDataSec(it);
		sequentialUniverse->updateAgents();
		
		//Mismo procedimiento a universo vectorial en caso de ser activado
		if (typeOfProc) {
			sumVec += measureTime([&](){vectorUniverse->applyAgentsRules(vectorialProc);});
			vectorUniverse->printDataVec();
			vectorUniverse->updateAgents();
		}

		usleep(100000);
	};

	
	auto calculateAvg = [&] (float sum){
		float avg {};
		avg = sum/iteraciones;
		return avg;
	};
	
	avgSeq = calculateAvg(sumSeq);
	std::cout <<"\n" << avgSeq << " ms";

	if (typeOfProc) {
		avgVec = calculateAvg(sumVec);
		std::cout << " : " <<avgVec << " ms\n";
	}

	/*
	============PRUEBAS DE CONCEPTO BEGIN============
	//Crear ambiente de 20 columnas y 10 filas
	CoordXY  size_env = {20, 10};
	Environment* universe = new Environment(size_env);

	uint32_t total_agentes;
	total_agentes = universe->getTotalAgents();
	std::cout << total_agentes << std::endl;

	//Mostrar info del ambiente
	std::cout << universe << std::endl;

	//Acceder al agente id=6
	std::cout << universe->getAgent(6) << std::endl;

	//Acceder al agente (x,y)=(1,4)
	CoordXY  cfoo = {1,4};
	std::cout << universe->getAgent(cfoo) << std::endl;

	//Determinar cantidad de vecinos vivos del
	//agente (x,y)=(1,4)
	CoordXY  cfoo;
	uint32_t vecinos;

	cfoo = {1,4};
	vecinos = universe->livingNeighborsOf( universe->getAgent(cfoo) );

	std::cout << universe->getAgent(cfoo) << std::endl;
	std::cout << vecinos << std::endl;

	============PRUEBAS DE CONCEPTO END  ============
	*/

	delete argumentos;
	delete sequentialUniverse;
	delete vectorUniverse;

	return(EXIT_SUCCESS);
}
