# pragma 
#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"
#include "Box.h"

namespace df {

	const int MAX_ALTITUDE = 5;

	class WorldManager :public Manager {
#define WM df :: WorldManager :: getInstance ()
	private:
		WorldManager();
		WorldManager(WorldManager const&);
		void operator=(WorldManager const&);
		ObjectList updates;
		ObjectList deletions;
		Box boundary;				//World boundary
		Box view;					//Player view of game world
		Object* p_view_following;
	public:
		static WorldManager& getInstance();
		int startUp();

		void shutDown();

		int insertObject(Object* p_o);
	
		int removeObject(Object* p_o);

		ObjectList getAllObjects() const;

		ObjectList objectsOfType(std::string type) const;

		void update();

		ObjectList isCollision(Object* p_o, Vector where);

		int moveObject(Object* p_o, Vector where);

		int markForDelete(Object* p_o);

		void draw();

		Box getBoundary();					//Get game world boundary
		void setBoundary(Box new_boundary);	//Set game world boundary

		Box getView();

		ObjectList getCollisions(const Object* p_o, Vector where);
	};

}
#endif