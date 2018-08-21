/***************************************************************************
# Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
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
#include <string>
#include "Graphics/Material/Material.h"
#include "Scene.h"
#include "Utils/JsonDocument.h"

namespace Falcor
{
    class SceneImporter
    {
    public:
        static bool loadScene(Scene& scene, const std::string& filename, Model::LoadFlags modelLoadFlags, Scene::LoadFlags sceneLoadFlags);

    private:
        using JsonVal = JsonDocument::Value;
        SceneImporter(Scene& scene) : mScene(scene) {}
        bool load(const std::string& filename, Model::LoadFlags modelLoadFlags, Scene::LoadFlags sceneLoadFlags);

        bool parseVersion(const JsonVal& jsonVal);
        bool parseModels(const JsonVal& jsonVal);
        bool parseLights(const JsonVal& jsonVal);
        bool parseLightProbes(const JsonVal& jsonVal);
        bool parseCameras(const JsonVal& jsonVal);
        bool parseAmbientIntensity(const JsonVal& jsonVal);
        bool parseActiveCamera(const JsonVal& jsonVal);
        bool parseCameraSpeed(const JsonVal& jsonVal);
        bool parseLightingScale(const JsonVal& jsonVal);
        bool parsePaths(const JsonVal& jsonVal);
        bool parseUserDefinedSection(const JsonVal& jsonVal);
        bool parseActivePath(const JsonVal& jsonVal);
        bool parseIncludes(const JsonVal& jsonVal);

        bool topLevelLoop();

        bool loadIncludeFile(const std::string& Include);

        bool createModel(const JsonVal& jsonModel);
        bool createModelInstances(const JsonVal& jsonVal, const Model::SharedPtr& pModel);
        bool createPointLight(const JsonVal& jsonLight);
        bool createDirLight(const JsonVal& jsonLight);
        ObjectPath::SharedPtr createPath(const JsonVal& jsonPath);
        bool createPathFrames(ObjectPath* pPath, const JsonVal& jsonFramesArray);
        bool createCamera(const JsonVal& jsonCamera);

        bool error(const std::string& msg);

        template<uint32_t VecSize>
        bool getFloatVec(const JsonVal& jsonVal, const std::string& desc, float vec[VecSize]);
        bool getFloatVecAnySize(const JsonVal& jsonVal, const std::string& desc, std::vector<float>& vec);
        JsonDocument::SharedPtr mpJDoc;
        Scene& mScene;
        std::string mFilename;
        std::string mDirectory;
        Model::LoadFlags mModelLoadFlags;
        Scene::LoadFlags mSceneLoadFlags;

        using ObjectMap = std::map<std::string, IMovableObject::SharedPtr>;
        bool isNameDuplicate(const std::string& name, const ObjectMap& objectMap, const std::string& objectType) const;
        IMovableObject::SharedPtr getMovableObject(const std::string& type, const std::string& name) const;

        ObjectMap mInstanceMap;
        ObjectMap mCameraMap;
        ObjectMap mLightMap;

        struct FuncValue
        {
            const std::string token;
            decltype(&SceneImporter::parseModels) func;
        };

        static const FuncValue kFunctionTable[];
        bool validateSceneFile();
    };
}