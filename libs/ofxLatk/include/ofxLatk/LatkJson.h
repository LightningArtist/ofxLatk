/*
 *  based on ofxJSON
 *
 *  Created by Jeffrey Crouse on 12/17/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 *  Updates by Christopher Baker 2012 - 2014
 *  http://christopherbaker.net
 *
 */


#pragma once

#include <string>
#include "json/json.h"
#include "ofLog.h"
#include "ofURLFileLoader.h"

class LatkJson: public Json::Value {

    public:
        LatkJson();
        LatkJson(const std::string& jsonString);
        LatkJson(const Json::Value& v);

        virtual ~LatkJson();

        bool parse(const std::string& jsonString);
        bool open(const std::string& filename);
        bool openLocal(const std::string& filename);
        bool openRemote(const std::string& filename);
        bool save(const std::string& filename, bool pretty = false) const;
        std::string getRawString(bool pretty = true) const;

        static std::string toString(Json::ValueType type);

};
