Player *makePlayer () {
	Player *poopGuy = (Player *)calloc(1, sizeof(Player));
	poopGuy->speed = 10;
	poopGuy->maxForce = 10;
	poopGuy->me = makeActor(makeForm(0.2, 1, 0.2));
	poopGuy->move = makeMove();
	Action *grav = makeGravity(poopGuy->move->vars);
	setFriction(grav, 10);
	poopGuy->jump = makeJump(poopGuy->move->vars, grav);
	poopGuy->eatPoop = makeStomach();
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
	printf("%c\n", input);
	controlVar *cv = (controlVar*)poopGuy->control->vars;
	switch (input) {
		case 97: //a
			ep->dir = 1;
			//if (poopGuy->lastInp == 97) {
				cv->moveLeft = 1;
			//}
			break;
		case 100: //d
			ep->dir = 3;
			//if (poopGuy->lastInp == 100) {
				cv->moveRight = 1;
				printf("time moveRight: %ld\n", clock());
			//} else {
			//	printf("1st press: %ld\n", clock());
			//}
			break;
		case 101:
			ep->eating = (ep->eating+1)%2;
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
