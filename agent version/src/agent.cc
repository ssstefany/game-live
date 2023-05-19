#include <agent.h>
#include <environment.h>

#include <immintrin.h>
#include <xmmintrin.h>

Environment* Agent::_myEnv;


Agent::Agent(const uint32_t& _id , const float _probLive){
	id      = _id;
	
	float probLive = (float)rand() / (float)RAND_MAX;
	state[ACTUAL] = probLive <= _probLive ? LIVE : DEAD;
	state[FUTURE] = DEAD;
	
	CoordXY coordxy = { id % _myEnv->getSize().x, id / _myEnv->getSize().x };
	this->setCoordxy(coordxy);
}

Agent::~Agent(void) {
   ;
}

CoordXY  Agent::getCoordxy(void) const {
    return(coordxy);
}

void Agent::setCoordxy(const CoordXY& _coordxy){
	coordxy.x = _coordxy.x;
	coordxy.y = _coordxy.y;
}

uint32_t Agent::getId(void) const {
    return(this->id);
}

State& Agent::getState() {
	return state[ACTUAL];
}

//Aplicar reglas según el tipo de procesamiento ingresado, 0: secuencial, 1: vectorial
void Agent::applyRules(uint32_t typeOfProc) {
	float livingNeighbors;

	switch (typeOfProc)
	{
	case 0:
		livingNeighbors = getLivingNeighbors();	
		break;
	case 1:
		livingNeighbors = getLivingNeighborsVectorial();
	}

	if ( ((livingNeighbors == 2) || (livingNeighbors == 3)) &&
	      getState() == LIVE) {
		state[FUTURE] = state[ACTUAL];
	}
	else if ( livingNeighbors == 3 ) {
		state[FUTURE] = LIVE;
	}
	else  {
		state[FUTURE] = DEAD;
	}
}

void Agent::update(){
	state[ACTUAL] = state[FUTURE];
}

//obtener cantidad de vecinos vivos secuencialmente
float Agent::getLivingNeighbors(void) {
	// Consulta al ambiente cuantos vecinos vivos tiene
	
	//Recorrer el vector agentNeighbors y
	//Determinar los agentes LIVE
	float livingNeighbors {0};
	
	livingNeighbors = 0;
	for(auto const& fooAgent : agentNeighbors){
		livingNeighbors += *fooAgent;
	}
	return( livingNeighbors );
}

void Agent::setNeighbors( const Neighbors _agentNeighbors){
	agentNeighbors = _agentNeighbors;
}

//obtener cantidad de vecinos vivos vectorialmente
float Agent::getLivingNeighborsVectorial(void){
	float livingNeighbors;
	__m128 a,b,c,d,e,f,g,h,i,j,k,l,m,n,o;
	//carga de datos de memoria principal a memoria vectorial
	//pasos 1,2,3,4,5,6,7,8
	a = _mm_load_ss(agentNeighbors[0]);
	b = _mm_load_ss(agentNeighbors[1]);
	c = _mm_load_ss(agentNeighbors[2]);
	d = _mm_load_ss(agentNeighbors[3]);
	e = _mm_load_ss(agentNeighbors[4]);
	f = _mm_load_ss(agentNeighbors[5]);
	g = _mm_load_ss(agentNeighbors[6]);
	h = _mm_load_ss(agentNeighbors[7]);

	//sumas
	//pasos 9,10,11,12
	i = _mm_add_ss(a,b);
	j = _mm_add_ss(c,d);
	k = _mm_add_ss(e,f);
	l = _mm_add_ss(g,h);
	//pasos 13,14
	m = _mm_add_ss(i,j);
	n = _mm_add_ss(k,l);
	//paso 15
	o = _mm_add_ss(m,n);

	//almacenamiento de datos de memoria vectorial a memoria principal
	//paso 16
	_mm_store_ss(&livingNeighbors,o);

	return( livingNeighbors );
}

std::ostream& operator<<(std::ostream& os,  Agent* _agent)  {  
    os << "ID:"<< _agent->id << ";(x: " << _agent->coordxy.x <<  ",y: "  << _agent->coordxy.y << ");" << _agent->state[ACTUAL] << "#";  
    return os;  
}  