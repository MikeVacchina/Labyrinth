#include "mvCollision.h"


mvCollision::mvCollision()
{
}


mvCollision::~mvCollision()
{
}

void mvCollision::setMaze(mvMaze *m)
{
	maze = m;
	xWalls = maze->getXWalls();
	zWalls = maze->getZWalls();
	holes = maze->getHoles();
	goal = maze->getGoal();
}

void mvCollision::setBall(mvSphere *b)
{
	ball = b;
	radius = ball->getMeshRadius();
}

//TODO: currently function is ugly 
//needs to be broken down into parts
//collision detection with the multiple objects
//followed by collision response
void mvCollision::resolveCollisions()
{
	std::set<int> xWallsSet;
	std::set<int> zWallsSet;
	std::map<int,std::pair<int,int> > walls;
	std::set<int> intersections;

	//check for a collision

	//check if in goal
	if(sqrt((ball->pos.x - goal.x)*(ball->pos.x - goal.x) + (ball->pos.z - goal.y)*(ball->pos.z - goal.y)) < goal.z)
	{
		std::cout << "goal reached game over\n";
	}

	//check if on hole
	for(int i=0,size=holes.size();i<size;++i)
	{
		if(sqrt((ball->pos.x - holes[i].x)*(ball->pos.x - holes[i].x) + (ball->pos.z - holes[i].z)*(ball->pos.z - holes[i].z)) < holes[i].r)
		{
			//fell into hole
			std::cout << "fell into hole game over\n";
		}
	}

	//check collision with walls

	//search through x axis aligned walls
	for(int i=0,sizei=xWalls.size();i<sizei;++i)
	{
		if(ball->pos.x + radius > xWalls[i].start && ball->pos.x - radius < xWalls[i].end)
		{
			xWallsSet.insert(xWallsSet.end(),xWalls[i].id);
			walls[xWalls[i].id].first = i;
		}
		else if(ball->pos.x + radius < xWalls[i].start)
			break;
	}

	//search through z axis aligned walls
	for(int i=0,sizei=zWalls.size();i<sizei;++i)
	{
		if(ball->pos.z + radius > zWalls[i].start && ball->pos.z - radius < zWalls[i].end)
		{
			zWallsSet.insert(zWallsSet.end(),zWalls[i].id);
			walls[zWalls[i].id].second = i;
		}
		else if(ball->pos.z + radius < zWalls[i].start)
			break;
	}

	//get walls were there was an intersection in both x and z directions
	std::set_intersection(xWallsSet.begin(), xWallsSet.end(), zWallsSet.begin(), zWallsSet.end(), std::inserter(intersections, intersections.end()));
	
	//each intersection is a collision with a wall
	for(std::set<int>::iterator it=intersections.begin();it!=intersections.end();++it)//there has been a collision!
	{
		//resolve collision

		int index = (*it);


		//get segments of wall
		std::vector<std::pair<glm::vec2,glm::vec2> > wallPts;

		wallPts.push_back(std::pair<glm::vec2,glm::vec2>(glm::vec2( xWalls[walls[index].first].start, zWalls[walls[index].second].start),
														glm::vec2( xWalls[walls[index].first].start, zWalls[walls[index].second].end)));

		wallPts.push_back(std::pair<glm::vec2,glm::vec2>(glm::vec2( xWalls[walls[index].first].start, zWalls[walls[index].second].end),
														glm::vec2( xWalls[walls[index].first].end, zWalls[walls[index].second].end)));
			
		wallPts.push_back(std::pair<glm::vec2,glm::vec2>(glm::vec2( xWalls[walls[index].first].end, zWalls[walls[index].second].end),
														glm::vec2( xWalls[walls[index].first].end, zWalls[walls[index].second].start)));

		wallPts.push_back(std::pair<glm::vec2,glm::vec2>(glm::vec2( xWalls[walls[index].first].end, zWalls[walls[index].second].start),
														glm::vec2( xWalls[walls[index].first].start, zWalls[walls[index].second].start)));

		//set default norm
		glm::vec2 norm(0.0);
			
		//check if ball is in wall
		if(ball->pos.x > xWalls[walls[index].first].start && ball->pos.x < xWalls[walls[index].first].end && ball->pos.z > zWalls[walls[index].second].start && ball->pos.z < zWalls[walls[index].second].end)
		{
			//center is in wall

			//currently do not do anything
			//unless the computer sucks the ball should never move fast enough that in a time step it is suddenly in a wall
				
			//get line segment(s) it intersects with
				//using commented out section below
			//int segID = getIntersectingSegment(wallPts, glm::vec2(lP.x, lP.y),glm::vec2(P.x, P.y));

			//get normal to line segment(s)
			//bounce using normal

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
		}
		else
		{
			//radius of ball intersected a wall

			//get the closest wall segment with the ball
			double dist =  radius - distanceLineSegPt(wallPts[0].first,wallPts[0].second,glm::vec2(ball->pos.x, ball->pos.z));

			std::vector<int> intersectedSegments;
			intersectedSegments.push_back(0);

			for(int i=1;i<4;++i)
			{
				//get closest distance from center of sphere to each line segment 
				double d = radius - distanceLineSegPt(wallPts[i].first,wallPts[i].second,glm::vec2(ball->pos.x, ball->pos.z));
				
				//biggest d will be closest since we are doing radius - distance
				if(d > dist)
				{
					intersectedSegments.clear();
					intersectedSegments.push_back(i);
					dist = d;
				}
				else if(d == dist)
				{
					//ball can be hitting two segments at same time...
					intersectedSegments.push_back(i);
				}
			}

			if(dist < 0)
			{
				//didnt actually collide

				//this happens because the ball is a sphere and we are doing axis aligned search to find collisions
				//happens when ball is close to hitting a corner of a wall

				return;
			}

			//get normal to line segment(s)
			for(int i=0, size=intersectedSegments.size();i<size;++i)
			{
				glm::vec2 tmpNorm;
				tmpNorm.x = -1*(wallPts[intersectedSegments[i]].first.y - wallPts[intersectedSegments[i]].second.y);
				tmpNorm.y = -1*(wallPts[intersectedSegments[i]].first.x - wallPts[intersectedSegments[i]].second.x);

				tmpNorm = glm::normalize(tmpNorm);

				//determine the direction of the norm
				if(glm::dot(tmpNorm,wallPts[intersectedSegments[i]].first-glm::vec2(ball->pos.x,ball->pos.z)) > 0)
					tmpNorm *= -1;

				//add the normal as a normal force acting on the ball for the next physics update
				ball->normalForces.push_back(glm::vec3(tmpNorm.x, 0.0, tmpNorm.y));

				//sum up normals
				norm += tmpNorm;
			}

			//average normals
			norm /= (double)intersectedSegments.size();
			norm = glm::normalize(norm);

			//set offset to keep ball out of the walls
			glm::vec2 offset(norm.x*dist, norm.y*dist);

			//move ball out of wall
			ball->pos = glm::vec3(offset.x + ball->pos.x, 0.0, offset.y + ball->pos.z);
		}

		//bounce the ball off the wall using the norm to find correct direction

		double u = -2*glm::dot(ball->vel,glm::vec3(norm.x, 0.0, norm.y));

		glm::vec3 nV = glm::normalize( ball->vel + glm::vec3(norm.x*u, 0.0, norm.y*u) );
		
		nV = glm::normalize(nV);

		//scale back the velocity as momentom and energy is lost
		float scale = glm::length(ball->vel)*0.5f;
			
		nV.x = nV.x * scale;
		nV.y = nV.y * scale;
		nV.z = nV.z * scale;

		//set new velocity
		ball->vel = nV;
	}
}