#include "ofApp.h"


void ofApp::setup(){

	//lets make 100 objects, and assign some randomized tags for each of the categories.
	for(int i = 0; i < 100; i++){
		string objectID = "obj_" + ofToString(i);

		string color;
		switch((int)floor(ofRandom(0,7))){
			case 0: color = "red"; break;
			case 1: color = "green"; break;
			case 2: color = "blue"; break;
			case 3: color = "orange"; break;
			case 4: color = "white"; break;
			case 5: color = "yellow"; break;
			case 6: color = "purple"; break;
		}

		//add a new tag for our objectID, with a random color (tags are always <string>) for the
		//"COLORS" category
		tm->addTagForObjectInCategory(objectID, color, COLORS);

		string shape;
		switch((int)floor(ofRandom(0,7))){
			case 0: shape = "circle"; break;
			case 1: shape = "triangle"; break;
			case 2: shape = "rectangle"; break;
			case 3: shape = "square"; break;
			case 4: shape = "hexagon"; break;
			case 5: shape = "ellipse"; break;
			case 6: shape = "line"; break;
		}
		//add a new tag for our objectID, with a random shape (tags are always <string>) for the
		//"SHAPES" category
		tm->addTagForObjectInCategory(objectID, shape, SHAPES);

		ofLogNotice() << objectID << " is '" << color << "' and '" << shape << "'";
	}

	//List all objects that are tagged "red" in the "COLORS" category
	ofLogNotice() << "\n\n ## Red Objects ##";
	vector<string> redObjects = tm->getObjectsWithTag(Tag<TAG_CATEGORIES>("red", COLORS));
	for(int i = 0; i < redObjects.size(); i++){
		ofLogNotice() << "red: " << redObjects[i];
	}

	//List all objects that are tagged "hexagon" in the "SHAPES" category
	ofLogNotice() << "\n\n ## hexagon Objects ##";
	vector<string> hexagonObjects = tm->getObjectsWithTag(Tag<TAG_CATEGORIES>("hexagon", SHAPES));
	for(int i = 0; i < hexagonObjects.size(); i++){
		ofLogNotice() << "hexagon: " << hexagonObjects[i];
	}


	//make an ordered name list of our TAG_CATEGORIES enum, to prettify the stats print
	vector<string>orderedCategoryNames;
	orderedCategoryNames.push_back("COLORS");
	orderedCategoryNames.push_back("SHAPES");

	//print stats for all Tag Categories (supply their names, as enum type is not printable)
	tm->printStats(orderedCategoryNames);

	//print object list for all tags in eac Category (supply their names, as enum type is not printable)
	tm->printObjectsForTagLists(orderedCategoryNames, true);

	//print num objects per tag in all Tag Categories (supply their names, as enum type is not printable)
	tm->printObjectsForTagLists(orderedCategoryNames, false);

}
