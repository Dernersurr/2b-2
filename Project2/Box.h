#ifndef BOX_H_
#define BOX_H_

//Game engine header files
#include "Vector.h"

//Misc required headers

	class Box {

	private:
		df::Vector corner;   //Top left corner of box
		int horizontal;    //Horizontal width
		int vertical;      //Vertical height

	public:

		Box();
		Box(df::Vector init_corner, int init_horizontal, int init_vertical);	//Create custom box
		df::Vector getCorner();						//Get top left corner of box
		void setCorner(df::Vector new_corner);		//Set top left corner of box
		int getHorizontal();						//Get horizontal size
		void setHorizontal(int new_horizontal);		//Set horizontal size
		int getVertical();							//Get vertical size
		void setVertical(int new_vertical);			//Set vertical size

	};

#endif 