Action *makeControl() {
	controlVar *cv = (controlVar*)calloc(1, sizeof(controlVar));
	cv->moveLeft = 0;
	cv->moveRight = 0;
	cv->mrCount = 0;
	cv->mlCount = 0;
	cv->player = 0;
	Action *a = makeAction(&control, cv);
	return a;
}

void getPlayer(void *c, Player *n_player) {
	controlVar *cv = (controlVar*)c;
	cv->player = n_player;
}

void control(Form *f, Action *a) {
	controlVar *cv = (controlVar*)(a->vars);
	int moveX = cv->moveRight - cv->moveLeft; 
	if (cv->moveRight == 1) {
		cv->mrCount++;
	} else {
		cv->mrCount = 0;
	}
	if (cv->moveLeft == 1) {
		cv->mlCount++;
	} else {
		cv->mlCount = 0;
	}
	if (moveX != 0 && (cv->mrCount > 3 || cv->mlCount > 3)) {
		moveVar *mv = (moveVar*)(cv->player->move->vars);
		if (abs(mv->force[0] + (cv->player->speed * moveX)) <= cv->player->maxForce) {
			printf("time force added = %ld\n", clock());
			addForce(mv, cv->player->speed * moveX, 0);
		}
	} else if (cv->moveRight == 0 && cv->moveLeft == 0) {
		// no input reset last input character. Turning based on last inp, want to change direction w/o moving{
		//cv->player->lastInp = 0;
	}
}
