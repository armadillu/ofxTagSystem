//
//  Tag.h
//  PG_WALL
//
//  Created by Oriol Ferrer Mesià on 14/04/15.
//
//

#ifndef __PG_WALL__Tag__
#define __PG_WALL__Tag__

#include "ofMain.h"

template <class C> //TagCategory user defined
class Tag{

public:
	
	Tag(){
		category = (C)-1;
	}

	Tag(string t, C cat){
		tag = t;
		category = cat;
	}

	bool operator< (const Tag& o ) const {
		return tag < o.tag;
	}

	inline bool operator == (const Tag& o) const{
		return tag == o.tag && category == o.category ;
	}

	inline bool operator != (const Tag& o) const{
		return (tag != o.tag || category != o.category);
	}

public:

	string 	tag;
	C 		category;

};

#endif /* defined(__PG_WALL__Tag__) */
