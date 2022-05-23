#pragma once

#include "GameObject.h"

class Shooter: public GameObject
{
public:
	Shooter(const ObjectParams* params);
	virtual ~Shooter() {};

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void collision() {};

	virtual std::string type() { return "Shooter"; };
	
protected:
	virtual void doDyingAnimation(); 
	virtual void handleAnimation() {};

	//Handling bullets
	int m_recoilCounter;
	int m_recoilSpeed;
	
	//Handling dying animation
	int m_dyingCounter;
	int m_dyingTime;

	//bool m_dead; //Check if the shooter is dead	
	//bool m_dying; //Check if dying animation is being displayed
};