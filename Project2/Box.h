#ifndef __BOX_H__
#define __BOX_H__

#include "Vector.h"
#include <string>
namespace df {

	class Box {

	private:
		Vector m_corner;         
		float m_horizontal;	   
		float m_vertical;	  
	public:
		
		Box(Vector init_corner, float init_horizontal, float init_vertical);

	
		Box();
	
		void setCorner(Vector new_corner);


		Vector getCorner() const;

		
		void setHorizontal(float new_horizontal);

		/// Get horizontal size of box.
		float getHorizontal() const;

		/// Set vertical size of box.
		void setVertical(float new_vertical);

		/// Get vertical size of box.
		float getVertical() const;

		/// Return attributes as string.
		std::string toString() const;

		bool operator==(const Box& other) const; ///< Compare boxes.
		bool operator!=(const Box& other) const; ///< Compare boxes.

		/// Draw box outline in pixels.
		void draw();
	};


} 
#endif //__BOX_H__
