#include <agent.h>
#include <environment.h>

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

State Agent::getState() const{
	return(state[ACTUAL]);
}


void Agent::applyRules() {
	
	uint8_t livingNeighbors;
	
	livingNeighbors = getLivingNeighbors();	
	
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

uint8_t Agent::getLivingNeighbors(void) {
	// Consulta al ambiente cuantos vecinos vivos tiene
	
	//Recorrer el vector agentNeighbors y
	//Determinar los agentes LIVE
	uint8_t livingNeighbors;
	
	livingNeighbors = 0;
	for(auto const& fooAgent : agentNeighbors){
		livingNeighbors += fooAgent->getState();
	}
	return( livingNeighbors );
}

void Agent::setNeighbors( const Neighbors _agentNeighbors){
	agentNeighbors = _agentNeighbors;
}


std::ostream& operator<<(std::ostream& os,  Agent* _agent)  {  
    os << "ID:"<< _agent->id << ";(x: " << _agent->coordxy.x <<  ",y: "  << _agent->coordxy.y << ");" << _agent->state[ACTUAL] << "#";  
    return os;  
}  