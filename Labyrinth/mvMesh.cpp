#include "mvMesh.h"


mvMesh::mvMesh()
{
}


mvMesh::~mvMesh()
{
}

void mvMesh::addVertex(vec3 v)
{
	vertices.push_back(v);
}

void mvMesh::addFace(vec3 f)
{
	faces.push_back(f);
}

void mvMesh::setColor(vec3 c)
{
	colors.clear();
	colors.push_back(c);
}

void mvMesh::setColor(double r, double g, double b)
{
	colors.clear();
	colors.push_back(vec3(r, g, b));
}

mvVertex* mvMesh::getGeometry()
{
	mvVertex *rtn = new mvVertex[faces.size()*3];

	bool singleColor = colors.size()==vertices.size() ? false : true;

	if( (singleColor && colors.size()==0) )
		colors.push_back(vec3());

	for(int i=0,size=faces.size();i<size;++i)
	{
		int j=0;

		rtn[i*3+j].position[0] = vertices[faces[i].x-1].x;
		rtn[i*3+j].position[1] = vertices[faces[i].x-1].y;
		rtn[i*3+j].position[2] = vertices[faces[i].x-1].z;

		if(singleColor)
		{
			rtn[i*3+j].color[0] = colors[0].x;
			rtn[i*3+j].color[1] = colors[0].y;
			rtn[i*3+j].color[2] = colors[0].z;
		}
		else
		{
			rtn[i*3+j].color[0] = colors[faces[i].x-1].x;
			rtn[i*3+j].color[1] = colors[faces[i].x-1].y;
			rtn[i*3+j].color[2] = colors[faces[i].x-1].z;
		}

		++j;

		rtn[i*3+j].position[0] = vertices[faces[i].y-1].x;
		rtn[i*3+j].position[1] = vertices[faces[i].y-1].y;
		rtn[i*3+j].position[2] = vertices[faces[i].y-1].z;

		if(singleColor)
		{
			rtn[i*3+j].color[0] = colors[0].x;
			rtn[i*3+j].color[1] = colors[0].y;
			rtn[i*3+j].color[2] = colors[0].z;
		}
		else
		{
			rtn[i*3+j].color[0] = colors[faces[i].y-1].x;
			rtn[i*3+j].color[1] = colors[faces[i].y-1].y;
			rtn[i*3+j].color[2] = colors[faces[i].y-1].z;
		}

		++j;

		rtn[i*3+j].position[0] = vertices[faces[i].z-1].x;
		rtn[i*3+j].position[1] = vertices[faces[i].z-1].y;
		rtn[i*3+j].position[2] = vertices[faces[i].z-1].z;

		if(singleColor)
		{
			rtn[i*3+j].color[0] = colors[0].x;
			rtn[i*3+j].color[1] = colors[0].y;
			rtn[i*3+j].color[2] = colors[0].z;
		}
		else
		{
			rtn[i*3+j].color[0] = colors[faces[i].z-1].x;
			rtn[i*3+j].color[1] = colors[faces[i].z-1].y;
			rtn[i*3+j].color[2] = colors[faces[i].z-1].z;
		}
	}

	return rtn;
}

int mvMesh::countVertices()
{
	return faces.size()*3;
}

void mvMesh::addMesh(mvMesh &mesh)
{
	int origSize = (int)vertices.size();

	bool singleColor = colors.size()==vertices.size() ? false : true;

	if( (singleColor && colors.size()==0) )
		colors.push_back(vec3());

	if(singleColor)
	{
		vec3 tmpColor = colors[0];
		colors.clear();

		for(int i=0,size=vertices.size();i<size;++i)
			colors.push_back(tmpColor);
	}

	singleColor = mesh.colors.size()==mesh.vertices.size() ? false : true;

	if( (singleColor && mesh.colors.size()==0) )
		mesh.colors.push_back(vec3());

	for(int i=0,size=mesh.vertices.size();i<size;++i)
	{
		vertices.push_back(mesh.vertices[i]);

		if(singleColor)
			colors.push_back(mesh.colors[0]);
		else
			colors.push_back(mesh.colors[i]);
	}

	for(int i=0,size=mesh.faces.size();i<size;++i)
	{
		faces.push_back(mesh.faces[i].plus(origSize));
	}
}

void mvMesh::clear()
{
	vertices.clear();
	faces.clear();
	colors.clear();
}