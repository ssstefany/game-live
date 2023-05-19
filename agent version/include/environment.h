#ifndef _ENV_H_
#define _ENV_H_

#include <global.h>
#include <agent.h>


class Environment {

private:
	//Vector de agentes en el ambiente
	std::vector<Agent*> agents;
	
	CoordXY size;
	CoordXY size_default = {20,10};

public:
    Environment(const CoordXY &);
	Environment(void);
    ~Environment(void);
	
	CoordXY getSize();
	
	void     addAgent(Agent* );
	uint32_t getCapacityAgents();
	uint32_t getTotalAgents();
	Agent*   getAgent(uint32_t _id);
	Agent*   getAgent(const CoordXY & _coordxy);
	
	void applyAgentsRules();
	void updateAgents();
	void showAgents(int );
	
	void setNeighborsAgents();
	
	friend std::ostream& operator<<(std::ostream&,  Environment*);
	
private:
	Neighbors getNeighborsOf(Agent* );
};


#endif