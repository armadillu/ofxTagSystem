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
		ofLogNotice() << "++++ Stats for \"" << name << "\" Tags +++++++++++++++++++++++++++++++++++";
		ofLogNotice() << "+ num unique tags : " << getNumTags();
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
		ofLogNotice() << "+ tag least used is \"" << minTag.tag <<"\" (" << min << ")";
		ofLogNotice() << "+ tag most used is \"" << maxTag.tag <<"\" (" << max << ")";
		ofLogNotice() << "+ avg objects per tag is " << avg;
	}


	void printObjectsForTagList(string name, bool onlyStats = true){

		typename map<Tag<C>, vector<string> >::iterator it = objectsByTag.begin();
		if(onlyStats){
			ofLogNotice() << "== Object Counts for Tag \"" << name << "\" =================================";
		}else{
			ofLogNotice() << "== Objects for Tag List For \"" << name << "\" =================================";
		}
		while(it != objectsByTag.end()){
			string t = "== ";
			if (onlyStats){
				ofLogNotice() << it->first.tag << ": " << it->second.size();
			}else{
				for(int i = 0 ; i < it->second.size(); i++){
					t += it->second[i];
					if( i != it->second.size() -1) t += ", ";
				}
				ofLogNotice() << it->first.tag << ": (" << it->second.size() << ") " << t;
			}
			++it;
		}
		ofLogNotice() << "=================================================";
	}

	void removeObjects(const vector<string> & objectIdsToRemove){

		vector<string>::const_iterator it = objectIdsToRemove.begin();
		while( it != objectIdsToRemove.end()){

			const string & thisObjectID = *it;
			typename map<Tag<C>, vector<string> >::iterator it2 = objectsByTag.begin();

			vector<Tag<C>> tagsToDelete;

			while(it2 != objectsByTag.end()){

				vector<string> & objs = it2->second;
				const Tag<C> & thisTag = it2->first;

				for(int i = objs.size() - 1; i >= 0 ; i--){

					if (objs[i] == thisObjectID){
						objs.erase(objs.begin() + i); //remove object from tag obj list
						tags[thisTag]--;
						if(tags[thisTag] <= 0){
							tags.erase(thisTag);
						}
					}
				}
				if(objs.size() == 0){
					tagsToDelete.push_back(thisTag);
				}
				++it2;
			}
			for(int i = 0; i < tagsToDelete.size(); i++){
				objectsByTag.erase(tagsToDelete[i]);
			}
			++it;
		}
	}

private:

	//tags
	map<Tag<C>, int>				tags; //keep track of all tags that exist, and count its frequency
	map<Tag<C>, vector<string> >	objectsByTag; //give me a tag, I give you a list of objectsIDs with that tag

	vector<string>					emptyVector; //to return a const ref
};

#endif
