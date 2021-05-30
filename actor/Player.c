Player *makePlayer (int size) {
	Player *poopGuy = (Player *)calloc(1, sizeof(Player));
	poopGuy->speed = 10;
	poopGuy->maxForce = 10;
	poopGuy->me = makeActor(makeForm(0.2, 1, 0.2, size, size));
	poopGuy->move = makeMove();
	Action *grav = makeGravity(poopGuy->move->vars);
	setFriction(grav, 10);
	poopGuy->jump = makeJump(poopGuy->move->vars, grav);
	poopGuy->eatPoop = makeStomach(size);
	poopGuy->control = makeControl();
	getPlayer(poopGuy->control->vars, poopGuy);
	addAction(poopGuy->me, poopGuy->move);
	addAction(poopGuy->me, grav);
	addAction(poopGuy->me, poopGuy->jump);
	addAction(poopGuy->me, poopGuy->eatPoop);
	addAction(poopGuy->me, poopGuy->control);
	return poopGuy;
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
		case 97: //a
			changeDir(ep, 1);
				cv->moveLeft = 1;
			break;
		case 100: //d
			changeDir(ep, 3);
				cv->moveRight = 1;
			break;
		case 101:
			ep->eating = (ep->eating+1)%2;
			break;
		case 119:
			changeDir(ep, 0);
			break;
		case 115:
			changeDir(ep, 2);
			break;
		case 112:
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
		case 97:
			cv->moveLeft = 0;
			break;
		case 100:
			cv->moveRight = 0;
			break;
		case 112:
			ep->pooping = 0;
			break;
	}	
}
