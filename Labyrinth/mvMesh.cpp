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
	//clear color
	colors.clear();

	//set color as a single colored object
	colors.push_back(c);
}

void mvMesh::setColor(double r, double g, double b)
{
	//clear color
	colors.clear();

	//set color as a single colored object
	colors.push_back(vec3(r, g, b));
}

mvVertex* mvMesh::getGeometry()
{
	mvVertex *rtn = new mvVertex[faces.size()*3];

	//check if single color or not
	bool singleColor = colors.size()==vertices.size() ? false : true;

	//if no color add default color of black
	if( (singleColor && colors.size()==0) )
		colors.push_back(vec3(0.0,0.0,0.0));

	//loop through faces creating each face
	for(int i=0,size=faces.size();i<size;++i)
	{
		int j=0;

		//set first vertex in face
		rtn[i*3+j].position[0] = float(vertices[int(faces[i].x-1)].x);
		rtn[i*3+j].position[1] = float(vertices[int(faces[i].x-1)].y);
		rtn[i*3+j].position[2] = float(vertices[int(faces[i].x-1)].z);

		if(singleColor)
		{
			rtn[i*3+j].color[0] = float(colors[0].x);
			rtn[i*3+j].color[1] = float(colors[0].y);
			rtn[i*3+j].color[2] = float(colors[0].z);
		}
		else
		{
			rtn[i*3+j].color[0] = float(colors[int(faces[i].x-1)].x);
			rtn[i*3+j].color[1] = float(colors[int(faces[i].x-1)].y);
			rtn[i*3+j].color[2] = float(colors[int(faces[i].x-1)].z);
		}

		++j;
		
		//set second vertex in face
		rtn[i*3+j].position[0] = float(vertices[int(faces[i].y-1)].x);
		rtn[i*3+j].position[1] = float(vertices[int(faces[i].y-1)].y);
		rtn[i*3+j].position[2] = float(vertices[int(faces[i].y-1)].z);

		if(singleColor)
		{
			rtn[i*3+j].color[0] = float(colors[0].x);
			rtn[i*3+j].color[1] = float(colors[0].y);
			rtn[i*3+j].color[2] = float(colors[0].z);
		}
		else
		{
			rtn[i*3+j].color[0] = float(colors[int(faces[i].y-1)].x);
			rtn[i*3+j].color[1] = float(colors[int(faces[i].y-1)].y);
			rtn[i*3+j].color[2] = float(colors[int(faces[i].y-1)].z);
		}

		++j;
		
		//set third vertex in face
		rtn[i*3+j].position[0] = float(vertices[int(faces[i].z-1)].x);
		rtn[i*3+j].position[1] = float(vertices[int(faces[i].z-1)].y);
		rtn[i*3+j].position[2] = float(vertices[int(faces[i].z-1)].z);

		if(singleColor)
		{
			rtn[i*3+j].color[0] = float(colors[0].x);
			rtn[i*3+j].color[1] = float(colors[0].y);
			rtn[i*3+j].color[2] = float(colors[0].z);
		}
		else
		{
			rtn[i*3+j].color[0] = float(colors[int(faces[i].z-1)].x);
			rtn[i*3+j].color[1] = float(colors[int(faces[i].z-1)].y);
			rtn[i*3+j].color[2] = float(colors[int(faces[i].z-1)].z);
		}
	}

	return rtn;
}

int mvMesh::countVertices()
{
	//return vertex count
	return faces.size()*3;
}

void mvMesh::addMesh(mvMesh &mesh)
{
	int origSize = (int)vertices.size();
	
	//check if single color or not
	bool singleColor = colors.size()==vertices.size() ? false : true;
	
	//if no color add default color of black
	if( (singleColor && colors.size()==0) )
		colors.push_back(vec3(0.0,0.0,0.0));

	//if single color make multi color of same color
	if(singleColor)
	{
		vec3 tmpColor = colors[0];
		colors.clear();

		for(int i=0,size=vertices.size();i<size;++i)
			colors.push_back(tmpColor);
	}

	//check if single color or not of mesh being added
	singleColor = mesh.colors.size()==mesh.vertices.size() ? false : true;
	
	//if no color add default color of black
	if( (singleColor && mesh.colors.size()==0) )
		mesh.colors.push_back(vec3());

	//add color and vertices to current list of color and vertices
	for(int i=0,size=mesh.vertices.size();i<size;++i)
	{
		vertices.push_back(mesh.vertices[i]);

		if(singleColor)
			colors.push_back(mesh.colors[0]);
		else
			colors.push_back(mesh.colors[i]);
	}

	//add faces to current list of faces
	for(int i=0,size=mesh.faces.size();i<size;++i)
	{
		faces.push_back(mesh.faces[i].plus(origSize));
	}
}

void mvMesh::scale(double s)
{
	//scale mesh
	for(int i=0,size=vertices.size();i<size;++i)
		vertices[i] = vertices[i].mulScalar(s);
}

void mvMesh::scale(vec3 s)
{
	//scale mesh
	for(int i=0,size=vertices.size();i<size;++i)
		vertices[i] = vertices[i].mul(s);
}

void mvMesh::translate(vec3 v)
{
	//translate mesh
	for(int i=0,size=vertices.size();i<size;++i)
		vertices[i] = vertices[i].plus(v);
}

void mvMesh::clear()
{
	//clear mesh data
	vertices.clear();
	faces.clear();
	colors.clear();
}