/***************************************************************************
# Copyright (c) 2018, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/
#include "Framework.h"
#include "JsonDocument.h"
#include <fstream>
#include <sstream>
#include "Externals/RapidJson/include/rapidjson/error/en.h"

namespace Falcor
{
    JsonDocument::JsonDocument()
    {

    }

    JsonDocument::SharedPtr JsonDocument::load(const std::string& filename, std::string& log)
    {
        SharedPtr pDoc = create();

        // Load the file
        std::ifstream fileStream(filename);
        std::stringstream strStream;
        strStream << fileStream.rdbuf();
        std::string jsonData = strStream.str();
        rapidjson::StringStream JStream(jsonData.c_str());

        // create the DOM
        pDoc->mJDoc.ParseStream(JStream);

        if (pDoc->mJDoc.HasParseError())
        {
            size_t line;
            line = std::count(jsonData.begin(), jsonData.begin() + pDoc->mJDoc.GetErrorOffset(), '\n');
            log = (std::string("JSON Parse error in line ") + std::to_string(line) + ". " + rapidjson::GetParseError_En(pDoc->mJDoc.GetParseError()));
            return nullptr;
        }

        return pDoc;
    }
}