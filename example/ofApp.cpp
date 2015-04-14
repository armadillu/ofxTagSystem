#include "ofApp.h"


void ofApp::setup(){

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
		tm->addTagsForObjectInCategory(objectID, color, COLORS);


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
		tm->addTagsForObjectInCategory(objectID, shape, SHAPES);

		ofLogNotice() << objectID << " is '" << color << "' and '" << shape << "'";
	}

	ofLogNotice() << "\n\n ## Red Objects ##";
	vector<string> redObjects = tm->getObjectsWithTag(Tag<TAG_CATEGORIES>("red", COLORS));
	for(int i = 0; i < redObjects.size(); i++){
		ofLogNotice() << "red: " << redObjects[i];
	}

	ofLogNotice() << "\n\n ## hexagon Objects ##";
	vector<string> hexagonObjects = tm->getObjectsWithTag(Tag<TAG_CATEGORIES>("hexagon", SHAPES));
	for(int i = 0; i < hexagonObjects.size(); i++){
		ofLogNotice() << "hexagon: " << hexagonObjects[i];
	}


	vector<string>orderedCategoryNames;
	orderedCategoryNames.push_back("COLORS");
	orderedCategoryNames.push_back("SHAPES");

	tm->printStats(orderedCategoryNames);


	tm->printObjectsForTagLists(orderedCategoryNames, true);


}
