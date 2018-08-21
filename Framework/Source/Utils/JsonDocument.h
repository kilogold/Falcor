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
#pragma once
#include "Externals/RapidJson/include/rapidjson/document.h"

namespace Falcor
{
    class JsonDocument
    {
    public:
        using SharedPtr = std::shared_ptr<JsonDocument>;        
        using Value = rapidjson::Value;
        using MemberIterator = rapidjson::Document::ConstMemberIterator;

        /** Create an empty document
        */
        static SharedPtr create();

        /** Create a document from a file
        */
        static SharedPtr load(const std::string& filename, std::string& log = std::string());

        /** Save a document to a file
        */
        bool save(const std::string& filename);

        /** Get the first member iterator
        */
        MemberIterator memberBegin() const { return mJDoc.MemberBegin(); }

        /** Get the end of the member list
        */
        MemberIterator memberEnd() const { return mJDoc.MemberEnd(); }

        /** Find a member by name
        */
        MemberIterator findMember(const std::string& name) const { return mJDoc.FindMember(name.c_str()); }
    private:
        JsonDocument();
        rapidjson::Document mJDoc;
    };
}