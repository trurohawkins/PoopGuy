Player *makePlayer () {
	Player *poopGuy = (Player *)calloc(1, sizeof(Player));
	poopGuy->speed = 10;
	poopGuy->me = makeActor(makeForm(0.2, 1, 0.2));
	poopGuy->move = makeMove();
	Action *grav = makeGravity(poopGuy->move->vars);
	poopGuy->jump = makeJump(poopGuy->move->vars, grav);
	addAction(poopGuy->me, poopGuy->move);
	addAction(poopGuy->me, grav);
	addAction(poopGuy->me, poopGuy->jump);
	return poopGuy;
}

void deletePlayer(Player *poopGuy) {
	//deleteActor(poopGuy->me); //actorlist will deal with the actor
	free(poopGuy);
}

void keyPressPlayer(Player *poopGuy, char input) {
	switch (input) {
		case 97:
			addForce(poopGuy->move->vars, -poopGuy->speed, 0);
			break;
		case 100:
			addForce(poopGuy->move->vars, poopGuy->speed, 0);
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
