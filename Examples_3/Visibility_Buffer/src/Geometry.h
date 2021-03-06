/*
 * Copyright (c) 2018 Confetti Interactive Inc.
 * 
 * This file is part of The-Forge
 * (see https://github.com/ConfettiFX/The-Forge).
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*/

#ifndef Geometry_h
#define Geometry_h

#ifdef METAL
// NOTE: Metal version cannot work with old models since it needs the duplicate vertices
// as it has no index buffer
#define OLD_MODELS 0
#else
// TODO: Remove this switch after the new models are optimized
#define OLD_MODELS 1
#endif

#include "../../../Common_3/Renderer/IRenderer.h"
#include "../../../Common_3/Renderer/ResourceLoader.h"

#if defined(METAL)
#include "OSXMetal/shader_defs.h"
#elif defined(DIRECT3D12) || defined(_DURANGO)
#define NO_HLSL_DEFINITIONS
#include "PCDX12/shader_defs.h"
#elif defined(VULKAN)
#define NO_GLSL_DEFINITIONS
#include "PCVulkan/shader_defs.h"
#endif

#define MAX_PATH 260

// Type definitions

typedef struct SceneVertexPos
{
    float x,y,z;
} SceneVertexPos;

typedef struct SceneVertexAttr
{
#if defined(METAL)
    float u,v;      // texture coords
    float nx,ny,nz; // normals
    float tx,ty,tz; // tangents
#else
	uint32_t texCoord;
	uint32_t normal;
	uint32_t tangent;
#endif
} SceneVertexAttr;

typedef struct Cluster
{
    float3 aabbMin, aabbMax;
    float3 coneCenter, coneAxis;
    uint32_t triangleCount;
    uint32_t clusterStart;
    float coneAngleCosine;
    bool valid;
    uint32_t meshIndex;
} Cluster;

typedef struct Mesh
{
#if defined(METAL)
    uint32_t startVertex;
    uint32_t triangleCount;
#else
	uint32_t startIndex;
	uint32_t indexCount;
#endif
    uint32_t vertexCount;
    float3 minBBox, maxBBox;
    Cluster* clusters;
    uint32_t clusterCount;
    uint32_t materialId;
} Mesh;

typedef struct Material
{
    bool twoSided;
    bool alphaTested;
} Material;

typedef struct Scene
{
    uint32_t numMeshes;
    uint32_t numMaterials;
    uint32_t totalTriangles;
    uint32_t totalVertices;
    Mesh* meshes;
    Material* materials;
    tinystl::vector<SceneVertexPos> positions;
    tinystl::vector<SceneVertexAttr> attributes;
    char** textures;
    char** normalMaps;
    char** specularMaps;
    
#if !defined(METAL)
	tinystl::vector<uint32_t>			indices;
#endif
} Scene;

typedef struct FilterBatchData
{
#if defined(METAL)
    uint32_t triangleCount;
    uint32_t triangleOffset;
#else
	uint meshIndex;         // Index into meshConstants
	uint indexOffset;       // Index relative to the meshConstants[meshIndex].indexOffset
	uint faceCount;         // Number of faces in this small batch
	uint outputIndexOffset; // Offset into the output index buffer
	uint drawBatchStart;    // First slot for the current draw call
	uint accumDrawIndex;
	uint _pad0;
	uint _pad1;
#endif
} FilterBatchData;

typedef struct FilterBatchChunk
{
    FilterBatchData* batches;
    uint32_t currentBatchCount;
    uint32_t currentDrawCallCount;
#if defined(METAL)
    Buffer*** batchDataBuffer;         // an array of Buffer*: one per clusters/BATCH_COUNT per mesh (clusters are filtered in batches of size BATCH_COUNT)
#else
	struct UniformRingBuffer* pRingBuffer;
#endif
} FilterBatchChunk;

// Exposed functions

Scene* loadScene(Renderer* pRenderer, const char* fileName);
void removeScene(Scene* scene);
void CreateClusters(bool twoSided, const Scene* pScene, Mesh* mesh);
#if defined(METAL)
void addClusterToBatchChunk(const Cluster* cluster, const Mesh* mesh, FilterBatchChunk* batchChunk);
#else
void addClusterToBatchChunk(const Cluster* cluster, uint batchStart, uint accumDrawCount, uint accumNumTriangles, int meshIndex, FilterBatchChunk* batchChunk);
#endif
void createCubeBuffers(Renderer* pRenderer, CmdPool* cmdPool, Buffer **outVertexBuffer, Buffer **outIndexBuffer);
void createTessellatedQuadBuffers(Buffer** ppVertexBuffer, Buffer** ppIndexBuffer, unsigned tessellationX, unsigned tessellationY);
void destroyBuffers(Renderer* pRenderer, Buffer* outVertexBuffer, Buffer* outIndexBuffer);

#endif
