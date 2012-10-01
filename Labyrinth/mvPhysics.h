#ifndef MVPHYSICS
#define MVPHYSICS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier

#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

#include "mvSimpleStructs.h"

class mvPhysics
{
public:
	mvPhysics()
	{
		lastDT = 0.0;
	}

	~mvPhysics()
	{
	}
	
	void setAccel(glm::vec3 a)
	{
		lA = A;
		A = a;
	}
	void setVel(glm::vec3 v)
	{
		lV = V;
		V = v;
	}
	void setPos(glm::vec3 p)
	{
		lP = P;
		P = p;
	}
	glm::vec3 getPos()
	{
		return P;
	}

	void update(double deltaTime)
	{
		lV = V;
		lP = P;

		glm::vec3 T(deltaTime);
		lastDT = deltaTime;

		V += T * A;
		P += T * V;
	}

	void checkCollision(std::vector<mvWall> xWalls, std::vector<mvWall> zWalls, double radius)
	{
		std::set<int> xWallsSet;
		std::set<int> zWallsSet;
		std::map<int,std::pair<int,int> > walls;
		std::set<int> intersections;
		for(int i=0,sizei=xWalls.size();i<sizei;++i)
		{
			if(P.x + radius > xWalls[i].start && P.x - radius < xWalls[i].end)
			{
				xWallsSet.insert(xWallsSet.end(),xWalls[i].id);
				walls[xWalls[i].id].first = i;
			}
			else if(P.x + radius < xWalls[i].start)
				break;
		}
		for(int i=0,sizei=zWalls.size();i<sizei;++i)
		{
			if(P.z + radius > zWalls[i].start && P.z - radius < zWalls[i].end)
			{
				zWallsSet.insert(zWallsSet.end(),zWalls[i].id);
				walls[zWalls[i].id].second = i;
			}
			else if(P.z + radius < zWalls[i].start)
				break;
		}

		std::set_intersection(xWallsSet.begin(), xWallsSet.end(), zWallsSet.begin(), zWallsSet.end(), std::inserter(intersections, intersections.end()));
	
		if(intersections.size()>0)//there has been a collision!
		{
			//resolve collision
			
			std::set<int>::iterator it = intersections.begin();
			if(P.x > xWalls[*it].start && P.x < xWalls[*it].end && P.z > zWalls[*it].start && P.z < zWalls[*it].end)
			{
				//center is in wall
				
				//get line segment(s) it intersects with
					//using commented out section below
				//get normal to line segment(s)
				//bounce using normal
			}
			else
			{
				//radius intersected a wall

				//get closest distance from center of sphere to each line segment (assumed as lines)
				//the smallest distance(s) show which segment(s) sphere hit
				//get normal to line segment(s)
				//bounce using normal
			}

			//glm::vec2 motionFirst(lP.x, lP.z);
			//glm::vec2 motionSecond(P.x-lP.x, P.z-lP.z);

			//std::vector<glm::vec2> wallPts;

			//std::set<int>::iterator it = intersections.begin();
			//
			//wallPts.push_back(glm::vec2( xWalls[walls[*it].first].start, zWalls[walls[*it].second].start));
			//wallPts.push_back(glm::vec2( xWalls[walls[*it].first].start, zWalls[walls[*it].second].end));
			//wallPts.push_back(glm::vec2( xWalls[walls[*it].first].end, zWalls[walls[*it].second].end));
			//wallPts.push_back(glm::vec2( xWalls[walls[*it].first].end, zWalls[walls[*it].second].start));

			//for(int i=0,size=wallPts.size();i<size;++i)
			//{
			//	int next = i+1==size?0:i+i;
			//	double top = glm::dot((motionFirst - wallPts[i]),wallPts[next]);
			//	double btm = glm::dot(motionSecond, wallPts[next]);
			//	double val;

			//	if(btm == 0)
			//	{
			//		//parallel :(
			//		if(top==0)
			//		{
			//			//colinear :|
			//		}
			//	}
			//	else
			//	{
			//		val = top/btm;
			//		if(val <= 1 && val >= 0)
			//		{
			//			//found segment of collision
			//			glm::vec2 ptCollision = motionFirst + motionSecond*glm::vec2(val);
			//		}
			//	}
			//}

			int a = 5;
		}
	}

private:
	glm::vec3 A;
	glm::vec3 V;
	glm::vec3 P;

	glm::vec3 lA;
	glm::vec3 lV;
	glm::vec3 lP;

	double lastDT;
};

#endif //MVPHYSICS