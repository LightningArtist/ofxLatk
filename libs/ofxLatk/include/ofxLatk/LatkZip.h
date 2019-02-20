/*
based on ofxZipArchive
Created by Jeffrey Crouse on 3/19/15.
Copyright (c) 2015 __MyCompanyName__. All rights reserved.

https://github.com/jeffcrouse/ofxZipArchive/blob/master/LICENSE
The MIT License (MIT)

Copyright (c) 2015 Jeff Crouse

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

#include "ofMain.h"
#include "ofxXmlPoco.h"

#include <Poco/Zip/ZipArchive.h>
#include <Poco/Zip/Compress.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Zip/ZipStream.h>
#include <Poco/Path.h>
#include <Poco/Delegate.h>
#include <Poco/File.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>

// ----------------------------------------------------------
class LatkZip {

    public:
        LatkZip():bOpened(false) { }
        
        bool open(string zipPath);
        vector<string> list();
        ofBuffer getFile(string fileName);
        bool unzipTo(string destination);
        
        static bool compress(string folderPath, string zipPath, bool recursive=true, bool excludeRoot=true, Poco::Zip::ZipCommon::CompressionLevel cl=Poco::Zip::ZipCommon::CL_NORMAL);

    protected:
        ifstream infile;
        bool bOpened;

};

// ----------------------------------------------------------
typedef std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> ZipErrorInfo;
typedef std::pair<const Poco::Zip::ZipLocalFileHeader, const Poco::Path> ZipOkInfo;
typedef const Poco::Zip::ZipLocalFileHeader ZipDoneInfo;

// ----------------------------------------------------------
class LatkZipArchiveHandler {

    public:
        LatkZipArchiveHandler() {
            isSuccessful = false;
        }

        ~LatkZipArchiveHandler() { }
        
        void onError(const void*, ZipErrorInfo& info) {
            ofLogError("LatkZip") << "Failed to Unzip: " + info.second;
            isSuccessful = false;
        }
        
        void onOk(const void*, ZipOkInfo& info) {
            ofLogNotice("LatkZip") << "Unzipped: " << info.second.toString();
            isSuccessful = true;
        }
        
        void onDone(const void*, ZipDoneInfo& header) {
            ofLogNotice("LatkZip") << "Zipped " << header.getFileName() << " was " << header.getUncompressedSize() << " now " << header.getCompressedSize();
            isSuccessful = true;
        }
        
        bool isSuccessful;

};

