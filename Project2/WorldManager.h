# pragma 
#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"

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
	};

}
#endif