#pragma once
#include "EventClass.h"
#include "TimeClass.h"
#include "GraphicClass.h"
#include "Worm.h"
using namespace std;

//Maximum allowed number of worms.
#define MAXWORMS 2

//Default values for width, height, FPS and display creation.
/**************************************************/
#define defaultDisplay true
#define defaultWidth 1920
#define defaultHeight 900
#define defaultFPS 50.0
/**************************************************/
class Simulation {
public:

	//Simulation constructor.
	Simulation(unsigned int width_ = defaultWidth, unsigned int height_ = defaultHeight, double FPS_ = defaultFPS, int wormCount_ = MAXWORMS);

	GraphicClass* getGraphicControl(void);
	TimeClass* getTimeControl(void);
	EventClass* getEventControl(void);

	void setDefaultKeys(void);
	bool initializeAll(void);

	bool setSimulation(bool displayCreation = defaultDisplay);

	bool startMoving(int keyCode);

	bool timer(Worm * wrmptr);

	void stopMoving(int keyCode);

	void refresh(void);

	bool dispatch(void);
	int keyUp(Worm* wormptr);

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
