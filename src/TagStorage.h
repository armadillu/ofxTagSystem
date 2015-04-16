//
//  TagStorage.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 02/07/14.
//
//

#ifndef __BaseApp__TagStorage__
#define __BaseApp__TagStorage__

#include "ofMain.h"
#include "Tag.h"

template <class C>
class TagStorage{

public:

	TagStorage(){};

	void addTagsForObject( string objectID, const vector< Tag<C> > & tagsList){

		for(int i = 0 ; i < tagsList.size(); i++){

			Tag<C> tag = tagsList[i];

			//add all tags to our tagDB
			if (tags.find(tag) != tags.end()){
				tags[tag]++ ;
			}else{
				tags[tag] = 1;
			}

			//assign objects to this tag
			if (find(objectsByTag[tag].begin(), objectsByTag[tag].end(), objectID) == objectsByTag[tag].end()){
				objectsByTag[tag].push_back(objectID); //only add object to that tag if not existing
			}
		}
	}

	//read back
	const vector<string>& getObjectIDsTaggedWith(Tag<C> tag){

		typename map<Tag<C>, vector<string> >::iterator it = objectsByTag.find(tag);
		if( it != objectsByTag.end()){
			return it->second;
		}else{
			return emptyVector;
		}
	}

	bool tagExists(Tag<C> tag){
		return (tags.find(tag) != tags.end());
	}

	int getNumTagAppereances(Tag<C> tag){
		if (tags.find(tag) != tags.end()){
			return tags[tag];
		}else{
			return 0;
		}
	}

	int getNumTags(){
		return tags.size();
	}

	int getNumObjects(){
		return objectsByTag.size();
	}

	void printStats(string name){
		ofLogNotice() << "🍊🍊🍊🍊 Stats for \"" << name << "\" Tags 🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊🍊";
		ofLogNotice() << "🍊 num unique tags : " << getNumTags();
		typename map<Tag<C>, int >::iterator it = tags.begin();

		int min = INT_MAX;
		int max = INT_MIN;
		Tag<C> minTag;
		Tag<C> maxTag;
		double avg = 0.0f;

		while(it != tags.end()){
			if(it->second < min ){
				min = it->second;
				minTag = it->first;
			}
			if(it->second > max){
				max = it->second;
				maxTag = it->first;
			}
			avg += it->second / (double)tags.size();
			++it;
		}
		ofLogNotice() << "🍊 tag least used is \"" << minTag.tag <<"\" (" << min << ")";
		ofLogNotice() << "🍊 tag most used is \"" << maxTag.tag <<"\" (" << max << ")";
		ofLogNotice() << "🍊 avg objects per tag is " << avg;
	}


	void printObjectsForTagList(string name, bool onlyStats = true){

		typename map<Tag<C>, vector<string> >::iterator it = objectsByTag.begin();
		ofLogNotice() << "⭐️⭐️ Objects for Tag List For \"" << name << "\" ⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️";
		while(it != objectsByTag.end()){
			string t = "⭐️⭐️ ";
			if (onlyStats){
				ofLogNotice() << it->first.tag << ": " << it->second.size();
			}else{
				for(int i = 0 ; i < it->second.size(); i++){
					t += it->second[i];
					if( i != it->second.size() -1) t += ", ";
				}
				ofLogNotice() << it->first.tag << ": " << t;
			}
			++it;
		}
		ofLogNotice() << "⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️⭐️";
	}

private:

	//tags
	map<Tag<C>, int>				tags; //keep track of all tags that exist, and count its frequency
	map<Tag<C>, vector<string> >	objectsByTag; //give me a tag, I give you a list of objectsIDs with that tag

	vector<string>					emptyVector; //to return a const ref
};

#endif
