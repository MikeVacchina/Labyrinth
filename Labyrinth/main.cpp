#include <cstdlib>
#include <cstdio>

#include "framework_labyrinth.h"

int main(int argc, char **argv)
{
	int windowWidth = 640;
	int windowHeight = 480;
	initalizeGlut(argc,argv);

	framework_labyrinth::instance()->initialize("Labyrinth Game", windowWidth, windowHeight);

	startGlut();
	return 1;
}