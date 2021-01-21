Player *makePlayer () {
	Player *poopGuy = (Player *)calloc(1, sizeof(Player));
	poopGuy->speed = 10;
	poopGuy->me = makeActor(makeForm(0.2, 1, 0.2));
	poopGuy->move = makeMove();
	Action *grav = makeGravity(poopGuy->move->vars);
	poopGuy->jump = makeJump(poopGuy->move->vars, grav);
	poopGuy->eatPoop = makeStomach();
	addAction(poopGuy->me, poopGuy->move);
	addAction(poopGuy->me, grav);
	addAction(poopGuy->me, poopGuy->jump);
	addAction(poopGuy->me, poopGuy->eatPoop);
	return poopGuy;
}

void deletePlayer(Player *poopGuy) {
	//deleteActor(poopGuy->me); //actorlist will deal with the actor
	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
	freeList(&(ep->stomach));
	free(poopGuy);
}

void keyPressPlayer(Player *poopGuy, char input) {
	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
	switch (input) {
		case 97: //a
			ep->dir = 1;
			addForce(poopGuy->move->vars, -poopGuy->speed, 0);
			break;
		case 100: //d
			ep->dir = 3;
			addForce(poopGuy->move->vars, poopGuy->speed, 0);
			break;
		case 119:
			ep->dir = 0;
			break;
		case 115:
			ep->dir = 2;
			break;
		case 112:
			ep->pooping = 1;
			break;
		case 32:
			startJump(poopGuy->jump);
			break;
	}
}

void keyReleasePlayer(Player *poopGuy, char input) {
	switch(input) {
		case 97:
			addForce(poopGuy->move->vars, poopGuy->speed, 0);
			break;
		case 100:
			addForce(poopGuy->move->vars, -poopGuy->speed, 0);
			break;
	}	
}
