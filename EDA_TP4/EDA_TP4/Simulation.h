#pragma once
#include "EventClass.h"
#include "TimeClass.h"
#include "GraphicClass.h"
#include "Worm.h"
using namespace std;

#define MAXWORMS 2

//Temporary values to check correct initialization.
/**************************************************/
#define defaultDisplay true

#define defaultWidth 900
#define defaultHeight 900
#define defaultFPS 50.0
/**************************************************/
class Simulation {
public:

	//Simulation constructor.
	Simulation(unsigned int width_ = defaultWidth, unsigned int height_ = defaultHeight, double FPS_ = defaultFPS, int wormCount_ = MAXWORMS);

	bool setSimulation(bool displayCreation = defaultDisplay);

	bool setAllegro(void);

	GraphicClass* getGraphicControl(void);
	TimeClass* getTimeControl(void);
	EventClass* getEventControl(void);

	bool initializeAll(void);

	void startMoving(void);

	void stopMoving(void);

	void refresh(void);

	void dispatch(void);

	bool initializeWorms(void);
	~Simulation();

private:

	//Datos miembro de Simulation.
	GraphicClass* graphicControl;
	TimeClass* timeControl;
	EventClass* eventControl;

	Worm* wormVector[MAXWORMS];

	int wormCount;
		
	unsigned int width, height;
	double FPS;
};