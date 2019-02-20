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
#include "LatkJson.h"

LatkJson::LatkJson() { }

LatkJson::LatkJson(const Json::Value& v): Json::Value(v) { }

LatkJson::LatkJson(const std::string& jsonString) {
    parse(jsonString);
}

LatkJson::~LatkJson() { }

bool LatkJson::parse(const std::string& jsonString) {
    Json::Reader reader;

    if (!reader.parse( jsonString, *this )) {
        ofLogError("LatkJson::parse") << "Unable to parse string: " << reader.getFormattedErrorMessages();
        return false;
    }

    return true;
}

bool LatkJson::open(const std::string& filename) {
    if (filename.find("http://") == 0 || filename.find("https://") == 0) {
        return openRemote(filename);
    } else {
        return openLocal(filename);
    }
}


bool LatkJson::openLocal(const std::string& filename) {
    ofBuffer buffer = ofBufferFromFile(filename);

    Json::Reader reader;

    if (!reader.parse(buffer.getText(), *this)) {
        ofLogError("LatkJson::openLocal") << "Unable to parse " << filename << ": " << reader.getFormattedErrorMessages();
        return false;
    } else {
        return true;
    }
}


bool LatkJson::openRemote(const std::string& filename) {
    std::string result = ofLoadURL(filename).data.getText();

    Json::Reader reader;

    if (!reader.parse(result, *this)) {
        ofLogError("LatkJson::openRemote") << "Unable to parse " << filename << ": " << reader.getFormattedErrorMessages();
        return false;
    }

    return true;
}


bool LatkJson::save(const std::string& filename, bool pretty) const {
    ofFile file;

    if (!file.open(filename, ofFile::WriteOnly)) {
        ofLogError("LatkJson::save") << "Unable to open " << file.getAbsolutePath() << ".";
        return false;
    }

    if (pretty) {
        Json::StyledWriter writer;
        file << writer.write( *this ) << std::endl;
    } else {
        Json::FastWriter writer;
        file << writer.write( *this ) << std::endl;
    }

    ofLogVerbose("LatkJson::save") << "JSON saved to " << file.getAbsolutePath() << ".";

    file.close();

    return true;
}


std::string LatkJson::getRawString(bool pretty) const {
    std::string raw;

    if (pretty) {
        Json::StyledWriter writer;
        raw = writer.write(*this);
    } else {
        Json::FastWriter writer;
        raw = writer.write(*this);
    }

    return raw;
}

std::string LatkJson::toString(Json::ValueType type) {
    switch (type) {
        case Json::nullValue:
            return "null";
        case Json::intValue:
            return "integer";
        case Json::uintValue:
            return "unsigned integer";
        case Json::realValue:
            return "double";
        case Json::stringValue:
            return "string";
        case Json::booleanValue:
            return "boolean";
        case Json::arrayValue:
            return "array";
        case Json::objectValue:
            return "object";
        default:
            ofLogError("LatkJson::toString") << "Unknown Json::ValueType.";
            return "unknown";
    }
}
