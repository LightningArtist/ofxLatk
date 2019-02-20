/*
based on ofxJSON
Created by Jeffrey Crouse on 12/17/10.
Copyright 2010 Eyebeam. All rights reserved.

Updates by Christopher Baker 2012 - 2014
http://christopherbaker.net

https://github.com/jeffcrouse/ofxJSON/blob/master/license.md
The code in this repository is available under the MIT License.
Copyright (c) [2015] [Roy J. Macdonald]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
