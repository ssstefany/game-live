#include <environment.h>

Environment::Environment(const CoordXY & _size){
	size = _size;
}

Environment::Environment(){
	size = size_default;
}

Environment::~Environment(){
	
}


CoordXY Environment::getSize(){
	return(size);
}

void Environment::addAgent(Agent* _agent){
	agents.push_back(_agent);
}

uint32_t Environment::getCapacityAgents(){
	return(getSize().x * getSize().y);
}

uint32_t Environment::getTotalAgents(){
	return(agents.size());
}


// Retorna el agente por id
Agent* Environment::getAgent(uint32_t _id){	
	return(agents[_id]);
}

// Retorna el agente por coordenada x,y
Agent* Environment::getAgent(const CoordXY & _coordxy){
	
	return(agents[_coordxy.y * size.x + _coordxy.x]);
}

//Aplica las reglas de los agentes en el ambiente
void Environment::applyAgentsRules(uint32_t typeOfProc){
	for(uint32_t y = 0; y < getSize().y; y++){
		for(uint32_t x = 0; x < getSize().x; x++){
			CoordXY  cfoo;
			cfoo = {x, y};
			
			getAgent(cfoo)->applyRules(typeOfProc);

		}		
	}
}

//Actualiza los estados de los agentes
void Environment::updateAgents(){
	for(uint32_t y = 0; y < getSize().y; y++){
		for(uint32_t x = 0; x < getSize().x; x++){
			CoordXY  cfoo;
			cfoo = {x, y};
			
			getAgent(cfoo)->update();

		}		
	}
}

//Muestra en pantalla los agentes
void Environment::showAgents(int gen){
	uint32_t i,j;
	uint32_t liveAgents;

	liveAgents = 0;
	printf("\u2554");
	for(j=1; j<=size.x;j++){
		printf("\u2550");
	}
	printf("\u2557\n");
	for(i=0; i<size.y; i++){
		printf("\u2551");
		for(j=0; j<size.x;j++){
			CoordXY cfoo = {j,i};
			liveAgents += getAgent(cfoo)->getState();
			printf("%s", getAgent(cfoo)->getState() == 0 ? " ": "\u258A");
		}
		printf("\u2551\n");
	}
	printf("\u255A");
	for(j=1; j<=size.x;j++){
		printf("\u2550");
	}
	printf("\u255D\n");
	printf("Generación: %d, Células vivas: %d\n", gen, liveAgents);
	
}

uint32_t Environment::liveAgents(){
	uint32_t i,j;
	uint32_t liveAgents {0};
	
	for(i=0; i<size.y; i++){
		for(j=0; j<size.x;j++){
			CoordXY cfoo = {j,i};
			liveAgents += getAgent(cfoo)->getState();
		}
	}
	return (liveAgents);
}

// Una vez que el ambiente esta listo,
// se debe configurar los vecinos de cada 
// Agente
void Environment::setNeighborsAgents(){
	for(uint32_t id = 0; id < getTotalAgents(); id++){
		Agent* ag =  getAgent(id);
		setNeighborsOf(ag);
	}
}

//Retorna un vector de los vecinos de un agente determinado
//La ventaja de esto es que este método es llamado
//sólo una vez, cuando el ambiente esta listo. Luego
//de esto, el agente sabe quienes son sus vecinos, para
//deternimar quienes están LIVE o DEAD
void Environment::setNeighborsOf(Agent* _agent){
	CoordXY   agentCoord;
	Neighbors& agentNeighbors = _agent->getNeighbors();
	uint32_t  xMin, xMax, yMin, yMax;
	
	agentCoord = _agent->getCoordxy();
	
	xMin = agentCoord.x     == 0      ?  0           : agentCoord.x-1;
	xMax = (agentCoord.x+1) == size.x ? agentCoord.x : agentCoord.x+1;
	yMin = agentCoord.y     == 0      ?  0           : agentCoord.y-1;
	yMax = (agentCoord.y+1) == size.y ? agentCoord.y : agentCoord.y+1;

	agentNeighbors.reserve(8);
	for(uint32_t yy = yMin; yy <= yMax; yy++){
		for(uint32_t xx = xMin; xx <= xMax; xx++){
			CoordXY cfoo = {xx,yy};
			if( (xx!=agentCoord.x) || (yy!=agentCoord.y) ){
				agentNeighbors.emplace_back(&getAgent(cfoo)->getState());
			}
		}
	}

	//se agregan estados "muertos" en agentes que tienen menos de 8 vecinos
	auto diff = maxNeighbors-agentNeighbors.size();
	for(uint32_t i=0 ; i<diff ; i++){
		agentNeighbors.push_back(&deadState);
	}
}

	// Crear los agentes
	// Cada agente se agrega al ambiente, con sus respectivas
	// coordenadas (x,y) a partir de su id y el tamaño del universo
void Environment::initEnvironment(float probLive){
	srand(1);
	Agent::_myEnv = this;
	for(uint32_t id = 0; id < this->getCapacityAgents(); id++) {	
		this->addAgent( new Agent(id, probLive) );
	}
	this->setNeighborsAgents();
}

//imprimir tablero 
void Environment::displayBoard(uint32_t it){
	puts ("\033[H\033[J"); 
	this->showAgents(it);
}

//imprimir data de iteraciones + data secuencial (siempre deben mostrarse)
void Environment::printDataSec(uint32_t it){
	std::cout << "\n" << (it+1) << " : " << this->liveAgents();
}

//impimir data vectorial
void Environment::printDataVec(void){
	std::cout << " : "<< this->liveAgents();
}


std::ostream& operator<<(std::ostream& os,  Environment* _env)  {  
    os << "Env size  : "<< "(x: " << _env->size.x <<  ",y: "  << _env->size.y << ")" << std::endl;  
	os << "Env Agents: "<< _env->getTotalAgents() ;  
    return os;  
} 





 