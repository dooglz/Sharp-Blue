//
// Created by Sam Serrels on 01/04/2017.
//

#ifndef SHARP_BLUE_LEVEL_H
#define SHARP_BLUE_LEVEL_H
#include "Entity.h"

namespace sb {
void LoadLevel();
class Level {
protected:
	void(*gameUpdateFunc)(double);
	void(*gameLoadInFunc)(double);
	void(*gameLoadOutFunc)(double);
	std::vector<Entity*> scenelist;

};

}
#endif //SHARP_BLUE_LEVEL_H
