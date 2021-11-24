// Ecological Systems
//--------------------------------
// Rain - source saturating surface blocks
// Groundwater Flow
//  -- Sun ( pulls moisture upwards from surface blocks)
//  -- Gravity flow (pulls downwards, empties out of bottom of world?)
//  -- Lateral, capilariy ( pulls sideways maybe up)
//-------------------------------------------------- 
// Parameters
// 
// tHoldU - thresHold Upper, moisture level at which point block will pass water on, represeting block saturation.
//           - once moisture level in dirt hits threshold, block will start passing water via gravity, eventually capiliry
// 
// tHoldL - thresHold Lower, the lowest moisture level that a block can have and still review water, below tHoldL block is considered hydrophobic
// 
// sat - saturated value for dirt block, 100% = 1
// 
// sTake   - sun Take, increment as which sun pulls water out
// gPull - gravitational Pull, increment as which gravity pulls water down
// 
// wCtr - water Counter,  measures time until next excecution
// wInt - water Interval, amounts of ticks at which moisture in each block is checked
// rCtr - rain counter
// rInt - rain interval
//-------------------------------------------------- 
#include "../actor/Eco.h"
// 
//-------------------------------------------------- 
float tHoldU = 0.5;
float tHoldL = 0.01;
float sat = 1.0;
float sTake = 0.02;
float gPull = 0.10;
int wCtr = 0;
int wInt = 5;
int rCtr = 0;
int rInt = 200;


void groundWater(){
	wCtr ++; // counts time since last call
	rCtr ++; // counts time since last call
	if (wCtr >= wInt) {
		for (int x = 0; x < theWorld->x; x++) {
			for (int y = theWorld->y - 1; y >=0; y--){
				if (theWorld->map[x][y] !=NULL && theWorld->map[x][y]->id == 10) {
					eVap(x,y); // sunlight pulls water up
					gravPull(x,y); // gravity pull water down
					if (rCtr >= rInt) {
						rain(x,y);
					}
				} 
			}
		}
		// printf("---------------------------------------------------------------------- \n");
		if (rCtr >= rInt) {
		 	printf("\n it's rained! \n");
			rCtr = 0;
		}
		wCtr = 0;
	}
}

int chSky(int x, int y) {
	
	int sky = 1;
	for (int yi = theWorld->y - 1; yi > y; yi--) {
		if (theWorld->map[x][yi] != NULL) {
			sky = 0; //block is covered from sunlight
			return sky;
		} 
	}
	return sky;
}

void rain(int x, int y) {
	int skyy = chSky(x,y);
	if (skyy == 1) {
		theWorld->map[x][y]->stat = sat;
	}
}


void eVap(int x, int y){
	int sky = chSky(x,y);
	// printf("%i \n", sky);
 	if (sky == 1) {
	//block is uncovered
		int depth = 0; // measures depth of water coloumn

		for (int yi = y-1; yi >= 0; yi--) {
			if ( theWorld->map[x][yi] != NULL && theWorld->map[x][yi]->stat > 0.01) {
				depth += 1;
			}
		}

		if (theWorld->map[x][y - depth]->stat >= sTake) { 
			theWorld->map[x][y - depth]->stat -= sTake;
			// takes moisture from the lowest block
			// printf(" x:%i,y:%i, d:%i, mStat:%f  \n",x,y,depth,theWorld->map[x][y-depth]->stat);
		} else {
			theWorld->map[x][y - depth]->stat = 0;
		} 

	}
}

void gravPull(int x, int y){
// if block is at bottom of world, water drops outs into the ether
	if (y == 0 ){
		if (theWorld->map[x][y]->stat - gPull >= tHoldU) {
				theWorld->map[x][y]->stat -= gPull;
		}
		return;
	}
// if block is above tHoldU and above a block that is above tHoldL
	if ( theWorld->map[x][y]->stat > tHoldU && theWorld->map[x][y-1] !=NULL && theWorld->map[x][y-1]->stat >= tHoldL) {
	// printf(" x:%i,y:%i, mStat:%f  \n",x,y,theWorld->map[x][y]->stat);
		if ( theWorld->map[x][y]->stat - gPull >= tHoldU) {
			theWorld->map[x][y]->stat -= gPull;
		} else {
			theWorld->map[x][y]->stat = tHoldU;
		}

		if (theWorld->map[x][y-1]->stat + gPull <= 1) { 
			theWorld->map[x][y-1]->stat += gPull; // add to below block
		} else {
			theWorld->map[x][y-1]->stat = 1; // add to below block
		}
	}
}

