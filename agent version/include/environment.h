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

	State deadState { DEAD };
	

public:
    Environment(const CoordXY &);
	Environment(void);
    ~Environment(void);
	
	CoordXY getSize();
	
	void     addAgent(Agent* );
	uint32_t getCapacityAgents();
	uint32_t getTotalAgents();
	uint32_t liveAgents();
	Agent*   getAgent(uint32_t _id);
	Agent*   getAgent(const CoordXY & _coordxy);

	static constexpr uint32_t maxNeighbors = 8;
	
	void applyAgentsRules(uint32_t p);
	void updateAgents();
	void showAgents(int);
	
	void setNeighborsAgents();

	void initEnvironment(float probLive);
	void displayBoard(uint32_t it);
	void printDataSec(uint32_t it);
	void printDataVec(void);

	friend std::ostream& operator<<(std::ostream&,  Environment*);
	
private:
	void setNeighborsOf(Agent* );
};


#endif