#include "Cloud.h"

Actor *makeCloud(int x, int y) {
	Form *f = makeForm(1,1,1,0,0);
	placeForm(x, y, f);

	char **sheets = (char**)calloc(sizeof(char*), 1);
	*sheets = "resources/cloud.png";
	Anim *h = makeAnim(sheets, 0, false, 1, 1);
	f->roto = 3;
	setDrawOrder(h, -1);
	setScale(h, 10, 10);
	GLuint sv = makeSpriteVao(1,1);
	animAddVao(h, sv);
	setAnim(f, h);
	free(sheets);	


	Actor *cloud = makeActor(f);
	Action *ch = makeAction(&cloudHover, NULL);
	addAction(cloud, ch);
	addActor(cloud);
}

void cloudHover(Form *c, Action *a) {

}
