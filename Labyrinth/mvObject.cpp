#include "mvObject.h"


mvObject::mvObject()
{
	geometry = NULL;
	vertexCount = 0;
}

mvObject::~mvObject()
{
	//if(geometry && vertexCount > 1)
	//	delete [] geometry;
	//else if(geometry && vertexCount > 0)
	//	delete geometry;
}

int mvObject::sizeofgeometry()
{
	return vertexCount*sizeof(mvVertex);
}