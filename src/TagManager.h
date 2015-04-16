//
//  TagManager.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 01/07/14.
//
//

#ifndef __BaseApp__CMSTagManager__
#define __BaseApp__CMSTagManager__

#include "ofMain.h"
#include "TagStorage.h"


template <class C> //C : TagCategory
class TagManager{

public:

	TagManager(int numCategories){
		for( C i = (C)0; i < numCategories; i = (C)(i+1) ){
			tagSystems[i] = new TagStorage<C>();
		}
	}


	vector<string> getObjectsWithTagInTagCategory(const string & tag,
												  C category,
												  int limitTo = 0){
		if (limitTo == 0) return tagSystems[category]->getObjectIDsTaggedWith(Tag<C>(tag, category));
		else{
			const vector<string> & v = tagSystems[category]->getObjectIDsTaggedWith(Tag<C>(tag, category));
			vector<string>::const_iterator first = v.begin();
			vector<string>::const_iterator last = v.begin() + MIN(limitTo, v.size());
			vector<string> newVec(first, last);
			return newVec;
		}

	}


	vector<string> getObjectsWithTag(const Tag<C> & tag,
									 int limitTo = 0,
									 bool shuffled = false){

		vector<string> res;
		if (limitTo == 0){
			res =  tagSystems[tag.category]->getObjectIDsTaggedWith(tag);
			if(shuffled){
				std::random_shuffle(res.begin(), res.end());
			}
			return res;
		}else{
			res = tagSystems[tag.category]->getObjectIDsTaggedWith(tag);
			if(shuffled){
				std::random_shuffle(res.begin(), res.end());
			}
			vector<string>::const_iterator first = res.begin();
			vector<string>::const_iterator last = res.begin() + MIN(limitTo, res.size());
			vector<string> newVec(first, last);
			return newVec;
		}
	}


	void addTagForObjectInCategory(const string & objectID, const string & tag, C category){
		if(tag.size()){
			vector<Tag<C>> v;
			v.push_back(Tag<C>(tag, category));
			tagSystems[category]->addTagsForObject(objectID, v);
		}
	}

	void addTagsForObject(const string & objectID,const vector<Tag<C>> & tags){
		if(tags.size()){
			tagSystems[tags[0].category]->addTagsForObject(objectID, tags);
		}
	}

	void addTagForObject(const string & objectID, const Tag<C> & tag){
		if(tag.tag.size()){
			vector<Tag<C>> v;
			v.push_back(tag);
			tagSystems[tag.category]->addTagsForObject(objectID, v);
		}
	}

	void printStats(vector<string> orderedCategoryNames){
		typename map <C, TagStorage<C>* >::iterator it = tagSystems.begin();
		int c = 0;
		while( it != tagSystems.end() ){
			string catName;
			if(c < orderedCategoryNames.size()) catName = orderedCategoryNames[c];
			it->second->printStats(catName);
			++it;
			c++;
		}
	}

	void printObjectsForTagLists(vector<string> orderedCategoryNames, bool fullObjectList = false){
		typename map <C, TagStorage<C>* >::iterator it = tagSystems.begin();
		int c = 0;
		while( it != tagSystems.end() ){
			string catName;
			if(c < orderedCategoryNames.size()) catName = orderedCategoryNames[c];
			it->second->printObjectsForTagList(catName, !fullObjectList);
			++it;
			c++;
		}
	}

private:

	//tags
	map<C, TagStorage<C>* > tagSystems;

	vector<string> emptyVector;	//to return an empty vector reference when needed
};

#endif /* defined(__BaseApp__CMSTagManager__) */