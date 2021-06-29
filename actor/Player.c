Player *curPlayer;

Player *makePlayer (int sx, int sy) {
	Player *poopGuy = (Player *)calloc(1, sizeof(Player));
	poopGuy->speed = 10;
	poopGuy->maxForce = 10;
	poopGuy->me = makeActor(makeForm(0.2, 1, 0.2, sx, sy));
	poopGuy->me->body->id = 69;
	poopGuy->move = makeMove();
	Action *grav = makeGravity(poopGuy->move->vars);
	setFriction(grav, 10);
	poopGuy->jump = makeJump(poopGuy->move->vars, grav);
	poopGuy->eatPoop = makeStomach(poopGuy->me->body, sx, sy);
	poopGuy->control = makeControl();
	setPlayer(poopGuy->control->vars, poopGuy);
	addAction(poopGuy->me, poopGuy->move);
	addAction(poopGuy->me, grav);
	addAction(poopGuy->me, poopGuy->jump);
	addAction(poopGuy->me, poopGuy->eatPoop);
	addAction(poopGuy->me, poopGuy->control);
	//changeDir(poopGuy->eatPoop poopGuy->me->body, 3);
	//cv->moveRight = 1;
	curPlayer = poopGuy;
	return poopGuy;
}

Player *getPlayer() {
	return curPlayer;
}

void deletePlayer(Player *poopGuy) {
	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
	freeList(&(ep->stomach));
	free(poopGuy);
}

void keyPressPlayer(Player *poopGuy, char input) {
	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
	moveVar *mv = (moveVar*)poopGuy->move->vars;
	//printf("%c\n", input);
	controlVar *cv = (controlVar*)poopGuy->control->vars;
	switch (input) {
		case 65: //a
			changeDir(ep, poopGuy->me->body, 1);
			cv->moveLeft = 1;
			break;
		case 68: //d
			changeDir(ep, poopGuy->me->body, 3);
			cv->moveRight = 1;
			break;
		case 69:
			ep->eating = (ep->eating+1)%2;
			break;
		case 87://w
			changeDir(ep, poopGuy->me->body,0);
			break;
		case 83://s
			changeDir(ep, poopGuy->me->body,2);
			break;
		case 80:
			ep->pooping = 1;
			break;
		case 32:
			startJump(poopGuy->me->body, poopGuy->jump);
			break;
	}
	if (input == 97 || input == 100) {
		poopGuy->lastInp = input;
	}
}

void keyReleasePlayer(Player *poopGuy, char input) {
	eatPooVar *ep = (eatPooVar*)(poopGuy->eatPoop->vars);
	controlVar *cv = (controlVar*)poopGuy->control->vars;
	switch(input) {
		case 65:
			cv->moveLeft = 0;
			break;
		case 68:
			cv->moveRight = 0;
			break;
		case 80:
			ep->pooping = 0;
			break;
	}	
}
