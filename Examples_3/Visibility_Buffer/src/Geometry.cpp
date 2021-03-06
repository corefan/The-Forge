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

#include "Geometry.h"

#include "../../../Common_3/ThirdParty/OpenSource/TinySTL/unordered_set.h"

#include "../../../Common_3/ThirdParty/OpenSource/assimp/3.3.1/include/assimp/cimport.h"
#include "../../../Common_3/ThirdParty/OpenSource/assimp/3.3.1/include/assimp/scene.h"
#include "../../../Common_3/ThirdParty/OpenSource/assimp/3.3.1/include/assimp/postprocess.h"
#include "../../../Common_3/OS/Interfaces/IFileSystem.h"
#include "../../../Common_3/OS/Interfaces/ILogManager.h"
#include "../../../Common_3/OS/Interfaces/IMemoryManager.h"
#include "../../../Common_3/OS/Core/Compiler.h"

#if OLD_MODELS
static void SetAlphaTestMaterials(tinystl::unordered_set<String>& mats)
{
	// Sponza
	mats.insert("Material__57");
	mats.insert("leaf");
	mats.insert("chain");

	// San Miguel
	mats.insert("aglaonema_Leaf");
	mats.insert("brevipedunculata_Leaf1");
	mats.insert("Azalea_1_blattg1");
	mats.insert("Azalea_1_Blutenb");
	mats.insert("Azalea_1_leafcal");
	mats.insert("Azalea_2_blattg1");
	mats.insert("Azalea_2_Blutenb");
	mats.insert("Chusan_Palm_1_Leaf");
	mats.insert("Fern_1_Fan");
	mats.insert("Fern_3_Leaf");
	mats.insert("Ficus_1_Leaf1");
	mats.insert("Geranium_1_Leaf");
	mats.insert("Geranium_1_blbl1");
	mats.insert("Geranium_1_blbl2");
	mats.insert("Geranium_1_Kelchbl");
	mats.insert("Hoja_Seca_2A");
	mats.insert("Hoja_Seca_2B");
	mats.insert("Hoja_Seca_2C");
	mats.insert("Hoja_Verde_A");
	mats.insert("Hoja_Verde_B");
	mats.insert("Hojas_Rojas_top");
	mats.insert("hybrids_blossom");
	mats.insert("hybrids_Leaf");
	mats.insert("Ivy_1_Leaf");
	mats.insert("Leave_A_a");
	mats.insert("Leave_A_b");
	mats.insert("Leave_A_c");
	mats.insert("Mona_Lisa_1_Leaf1");
	mats.insert("Mona_Lisa_1_Leaf2");
	mats.insert("Mona_Lisa_2_Leaf1");
	mats.insert("Mona_Lisa_1_petal11");
	mats.insert("Mona_Lisa_1_petal12");
	mats.insert("paniceum_Leaf");
	mats.insert("Pansy_1_blblbac");
	mats.insert("Pansy_1_Leaf");
	mats.insert("Pansy_1_Leafcop");
	mats.insert("Pansy_1_Leafsma");
	mats.insert("Poinsettia_1_Leaf");
	mats.insert("Poinsettia_1_redleaf");
	mats.insert("Poinsettia_1_smallre");
	mats.insert("Rose_1_Blatt2");
	mats.insert("Rose_1_Blutenb");
	mats.insert("Rose_1_Blatt1_");
	mats.insert("Rose_1_Kelchbl");
	mats.insert("Rose_2__Blutenb");
	mats.insert("Rose_2__Kelchbl");
	mats.insert("Rose_2_Blatt1_");
	mats.insert("Rose_3_Blutenb");
	mats.insert("Rose_3_Blatt2");
	mats.insert("zebrina_Leaf");
}

static void SetTwoSidedMaterials(tinystl::unordered_set<String>& mats)
{
	// Sponza
	mats.insert("Material__57");
	mats.insert("leaf");
	mats.insert("chain");

	// San Miguel
	mats.insert("aglaonema_Leaf");
	mats.insert("brevipedunculata_Leaf1");
	mats.insert("Azalea_1_blattg1");
	mats.insert("Azalea_1_Blutenb");
	mats.insert("Azalea_1_leafcal");
	mats.insert("Azalea_2_blattg1");
	mats.insert("Azalea_2_Blutenb");
	mats.insert("Chusan_Palm_1_Leaf");
	mats.insert("Fern_1_Fan");
	mats.insert("Fern_3_Leaf");
	mats.insert("Ficus_1_Leaf1");
	mats.insert("Geranium_1_Leaf");
	mats.insert("Geranium_1_blbl1");
	mats.insert("Geranium_1_blbl2");
	mats.insert("Geranium_1_Kelchbl");
	mats.insert("Hoja_Seca_2A");
	mats.insert("Hoja_Seca_2B");
	mats.insert("Hoja_Seca_2C");
	mats.insert("Hoja_Verde_A");
	mats.insert("Hoja_Verde_B");
	mats.insert("Hojas_Rojas_top");
	mats.insert("hybrids_blossom");
	mats.insert("hybrids_Leaf");
	mats.insert("Ivy_1_Leaf");
	mats.insert("Leave_A_a");
	mats.insert("Leave_A_b");
	mats.insert("Leave_A_c");
	mats.insert("Mona_Lisa_1_Leaf1");
	mats.insert("Mona_Lisa_1_Leaf2");
	mats.insert("Mona_Lisa_2_Leaf1");
	mats.insert("Mona_Lisa_1_petal11");
	mats.insert("Mona_Lisa_1_petal12");
	mats.insert("paniceum_Leaf");
	mats.insert("Pansy_1_blblbac");
	mats.insert("Pansy_1_Leaf");
	mats.insert("Pansy_1_Leafcop");
	mats.insert("Pansy_1_Leafsma");
	mats.insert("Poinsettia_1_Leaf");
	mats.insert("Poinsettia_1_redleaf");
	mats.insert("Poinsettia_1_smallre");
	mats.insert("Rose_1_Blatt2");
	mats.insert("Rose_1_Blutenb");
	mats.insert("Rose_1_Blatt1_");
	mats.insert("Rose_1_Kelchbl");
	mats.insert("Rose_2__Blutenb");
	mats.insert("Rose_2__Kelchbl");
	mats.insert("Rose_2_Blatt1_");
	mats.insert("Rose_3_Blutenb");
	mats.insert("Rose_3_Blatt2");
	mats.insert("zebrina_Leaf");
	mats.insert("Tronco");
	mats.insert("Muros");
	mats.insert("techos");
	mats.insert("Azotea");
	mats.insert("Pared_SanMiguel_N");
	mats.insert("Pared_SanMiguel_H");
	mats.insert("Pared_SanMiguel_B");
	mats.insert("Pared_SanMiguel_G");
	mats.insert("Barandal_Detalle_Extremos");
	mats.insert("Madera_Silla");
	mats.insert("Forja_Macetas");
	mats.insert("Muro_Naranja_Escalera");
	mats.insert("Tela_Mesa_D_2");
	mats.insert("Tela_Mesa_D");
}
#endif

#if !defined(METAL)
static inline float2 abs(const float2& v)
{
	return float2(fabsf(v.getX()), fabsf(v.getY()));
}
static inline float2 subtract(const float2& v, const float2& w)
{
	return float2(v.getX() - w.getX(), v.getY() - w.getY());
}
static inline float2 step(const float2& y, const float2& x)
{
	return float2(x.getX() >= y.getX() ? 1.f : 0.f,
		x.getY() >= y.getY() ? 1.f : 0.f);
}
static inline float2 mulPerElem(const float2 &v, float f)
{
	return float2(v.getX()*f, v.getY()*f);
}
static inline float2 mulPerElem(const float2 &v, const float2& w)
{
	return float2(v.getX()*w.getX(), v.getY()*w.getY());
}
static inline float2 sumPerElem(const float2 &v, const float2& w)
{
	return float2(v.getX() + w.getX(), v.getY() + w.getY());
}
static inline float2 sign_not_zero(const float2& v)
{
	return subtract(mulPerElem(step(float2(0, 0), v), 2.0), float2(1, 1));
}
static inline uint packSnorm2x16(const float2& v)
{
	uint x = (uint)round(clamp(v.getX(), -1, 1) * 32767.0f);
	uint y = (uint)round(clamp(v.getY(), -1, 1) * 32767.0f);
	return ((uint)0x0000FFFF & x) | ((y << 16) & (uint)0xFFFF0000);
}
static inline uint packUnorm2x16(const float2& v)
{
	uint x = (uint)round(clamp(v.getX(), 0, 1) * 65535.0f);
	uint y = (uint)round(clamp(v.getY(), 0, 1) * 65535.0f);
	return ((uint)0x0000FFFF & x) | ((y << 16) & (uint)0xFFFF0000);
}

#define F16_EXPONENT_BITS 0x1F
#define F16_EXPONENT_SHIFT 10
#define F16_EXPONENT_BIAS 15
#define F16_MANTISSA_BITS 0x3ff
#define F16_MANTISSA_SHIFT (23 - F16_EXPONENT_SHIFT)
#define F16_MAX_EXPONENT (F16_EXPONENT_BITS << F16_EXPONENT_SHIFT)

static inline unsigned short F32toF16(float val)
{
	uint f32 = (*(uint *)&val);
	unsigned short f16 = 0;
	/* Decode IEEE 754 little-endian 32-bit floating-point value */
	int sign = (f32 >> 16) & 0x8000;
	/* Map exponent to the range [-127,128] */
	int exponent = ((f32 >> 23) & 0xff) - 127;
	int mantissa = f32 & 0x007fffff;
	if (exponent == 128)
	{ /* Infinity or NaN */
		f16 = (unsigned short)(sign | F16_MAX_EXPONENT);
		if (mantissa) f16 |= (mantissa & F16_MANTISSA_BITS);

	}
	else if (exponent > 15)
	{ /* Overflow - flush to Infinity */
		f16 = (unsigned short)(sign | F16_MAX_EXPONENT);
	}
	else if (exponent > -15)
	{ /* Representable value */
		exponent += F16_EXPONENT_BIAS;
		mantissa >>= F16_MANTISSA_SHIFT;
		f16 = (unsigned short)(sign | exponent << F16_EXPONENT_SHIFT | mantissa);
	}
	else
	{
		f16 = (unsigned short)sign;
	}
	return f16;
}
static inline uint pack2Floats(float2 f)
{
	return (F32toF16(f.getX()) & 0x0000FFFF) | ((F32toF16(f.getY()) << 16) & 0xFFFF0000);
}

static inline float2 normalize(const float2 & vec)
{
	float lenSqr = vec.getX()*vec.getX() + vec.getY()*vec.getY();
	float lenInv = (1.0f / sqrtf(lenSqr));
	return float2(vec.getX() * lenInv, vec.getY() * lenInv);
}

static inline float OctWrap(float v, float w)
{
	return (1.0f - abs(w)) * (v >= 0.0f ? 1.0f : -1.0f);
}

static inline uint encodeDir(const float3& n)
{
	float absLength = (abs(n.getX()) + abs(n.getY()) + abs(n.getZ()));
	float3 enc;
	enc.setX(n.getX() / absLength);
	enc.setY(n.getY() / absLength);
	enc.setZ(n.getZ() / absLength);

	if (enc.getZ() < 0)
	{
		float oldX = enc.getX();
		enc.setX(OctWrap(enc.getX(), enc.getY()));
		enc.setY(OctWrap(enc.getY(), oldX));
	}
	enc.setX(enc.getX() * 0.5f + 0.5f);
	enc.setY(enc.getY() * 0.5f + 0.5f);

	return packUnorm2x16(float2(enc.getX(), enc.getY()));
}
#endif

// Loads a scene using ASSIMP and returns a Scene object with scene information
Scene* loadScene(Renderer* pRenderer, const char* fileName)
{
#if TARGET_IOS
	NSString *fileUrl = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String : fileName] ofType : @""];
	fileName = [fileUrl fileSystemRepresentation];
#endif

#if OLD_MODELS
	Scene* scene = (Scene*)conf_calloc(1, sizeof(Scene));
	File assimpScene = {};
	assimpScene.Open(fileName, FileMode::FM_ReadBinary, FSRoot::FSR_Absolute);
	ASSERT(assimpScene.IsOpen());

	assimpScene.Read(&scene->numMeshes, sizeof(uint32_t));
	assimpScene.Read(&scene->totalVertices, sizeof(uint32_t));
	assimpScene.Read(&scene->totalTriangles, sizeof(uint32_t));

	scene->meshes = (Mesh*)conf_calloc(scene->numMeshes, sizeof(Mesh));
	scene->indices = tinystl::vector<uint32>(scene->totalTriangles, uint32_t(0));
	scene->positions = tinystl::vector<SceneVertexPos>(scene->totalVertices, SceneVertexPos{ 0 });
	scene->attributes = tinystl::vector<SceneVertexAttr>(scene->totalVertices, SceneVertexAttr{ 0 });

	tinystl::vector<float2> texcoords(scene->totalVertices);
	tinystl::vector<float3> normals(scene->totalVertices);
	tinystl::vector<float3> tangents(scene->totalVertices);

	assimpScene.Read(scene->indices.getArray(), sizeof(uint32_t) * scene->totalTriangles);
	assimpScene.Read(scene->positions.getArray(), sizeof(float3) * scene->totalVertices);
	assimpScene.Read(texcoords.getArray(), sizeof(float2) * scene->totalVertices);
	assimpScene.Read(normals.getArray(), sizeof(float3) * scene->totalVertices);
	assimpScene.Read(tangents.getArray(), sizeof(float3) * scene->totalVertices);

	for (uint32_t v = 0; v < scene->totalVertices; v++)
	{
		const float3& normal = normals[v];
		scene->attributes[v].normal = encodeDir(normal);

		const float3& tangent = tangents[v];
		scene->attributes[v].tangent = encodeDir(tangent);

		const float2& tc = texcoords[v];
		scene->attributes[v].texCoord = pack2Floats(float2(tc.x, 1.0f - tc.y));
	}

	for (uint32_t i = 0; i < scene->numMeshes; ++i)
	{
		Mesh& batch = scene->meshes[i];

		assimpScene.Read(&batch.materialId, sizeof(uint32_t));
		assimpScene.Read(&batch.vertexCount, sizeof(uint32_t));
		assimpScene.Read(&batch.startIndex, sizeof(uint32_t));
		assimpScene.Read(&batch.indexCount, sizeof(uint32_t));
	}

	tinystl::unordered_set<String> twoSidedMaterials;
	SetTwoSidedMaterials(twoSidedMaterials);

	tinystl::unordered_set<String> alphaTestMaterials;
	SetAlphaTestMaterials(alphaTestMaterials);

	assimpScene.Read(&scene->numMaterials, sizeof(uint32_t));
	scene->materials = (Material*)conf_calloc(scene->numMaterials, sizeof(Material));
	scene->textures = (char**)conf_calloc(scene->numMaterials, sizeof(char*));
	scene->normalMaps = (char**)conf_calloc(scene->numMaterials, sizeof(char*));
	scene->specularMaps = (char**)conf_calloc(scene->numMaterials, sizeof(char*));

#ifdef ORBIS
#define DEFAULT_ALBEDO "default.gnf"
#define DEFAULT_NORMAL "default_nrm.gnf"
#define DEFAULT_SPEC   "default_spec.gnf"
#else
#define DEFAULT_ALBEDO "default.dds"
#define DEFAULT_NORMAL "default_nrm.dds"
#define DEFAULT_SPEC "default.dds"
#endif

	for (uint32_t i = 0; i < scene->numMaterials; i++)
	{
		Material& m = scene->materials[i];
		m.twoSided = false;

		int texIndex = 0;

		uint32_t matNameLength = 0;
		assimpScene.Read(&matNameLength, sizeof(uint32_t));

		tinystl::vector<char> matName(matNameLength);
		assimpScene.Read(matName.getArray(), sizeof(char) * matNameLength);

		uint32_t albedoNameLength = 0;
		assimpScene.Read(&albedoNameLength, sizeof(uint32_t));

		tinystl::vector<char> albedoName(albedoNameLength);
		assimpScene.Read(albedoName.getArray(), sizeof(char)*albedoNameLength);

		if (albedoName[0] != '\0')
		{
			String path(albedoName.getArray());
			uint dotPos = 0;
#ifdef ORBIS
			// try to load the GNF version instead: change extension to GNF
			path.rfind('.', -1, &dotPos);
			path.resize(dotPos);
			path[dotPos] = '\0';
			path.append(".gnf", 4);
#endif
			String base_filename = FileSystem::GetFileNameAndExtension(path);
			scene->textures[i] = (char*)conf_calloc(base_filename.size() + 1, sizeof(char));
			strcpy(scene->textures[i], base_filename.c_str());

			// try load the associated normal map 
			String normalMap(base_filename);
			normalMap.rfind('.', -1, &dotPos);
			normalMap.insert(dotPos, "_NRM", 4);

			if (!FileSystem::FileExists(normalMap, FSR_Textures))
				normalMap = DEFAULT_NORMAL;

			scene->normalMaps[i] = (char*)conf_calloc(normalMap.size() + 1, sizeof(char));
			strcpy(scene->normalMaps[i], normalMap.c_str());

			// try load the associated spec map 
			String specMap(base_filename);
			dotPos = 0;
			specMap.rfind('.', -1, &dotPos);
			specMap.insert(dotPos, "_SPEC", 5);

			if (!FileSystem::FileExists(specMap, FSR_Textures))
				specMap = DEFAULT_SPEC;

			scene->specularMaps[i] = (char*)conf_calloc(specMap.size() + 1, sizeof(char));
			strcpy(scene->specularMaps[i], specMap.c_str());
		}
		else
		{
			// default textures
			scene->textures[i] = (char*)conf_calloc(strlen(DEFAULT_ALBEDO) + 1, sizeof(char));
			strcpy(scene->textures[i], DEFAULT_ALBEDO);

			scene->normalMaps[i] = (char*)conf_calloc(strlen(DEFAULT_NORMAL) + 1, sizeof(char));
			strcpy(scene->normalMaps[i], DEFAULT_NORMAL);

			scene->specularMaps[i] = (char*)conf_calloc(strlen(DEFAULT_SPEC) + 1, sizeof(char));
			strcpy(scene->specularMaps[i], DEFAULT_SPEC);
		}

		float ns = 0.0f;
		assimpScene.Read(&ns, sizeof(float));  // load shininess

		int twoSided = 0;
		assimpScene.Read(&twoSided, sizeof(float));  // load two sided
		m.twoSided = (twoSided != 0);

		String tinyMatName(matName.getArray());
		if (twoSidedMaterials.find(tinyMatName) != twoSidedMaterials.end())
			m.twoSided = true;

		m.alphaTested = (alphaTestMaterials.find(tinyMatName) != alphaTestMaterials.end());
	}

	assimpScene.Close();
#else
	const aiScene* assimpScene = aiImportFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_ImproveCacheLocality | aiProcess_PreTransformVertices | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!assimpScene)
		LOGERRORF(aiGetErrorString());
	ASSERT(assimpScene);

	Scene* scene = (Scene*)conf_malloc(sizeof(Scene));
	memset(scene, 0, sizeof(*scene));
	scene->numMeshes = assimpScene->mNumMeshes;
	scene->numMaterials = assimpScene->mNumMaterials;
	scene->meshes = (Mesh*)conf_malloc(scene->numMeshes * sizeof(Mesh));
	scene->materials = (Material*)conf_malloc(scene->numMaterials * sizeof(Material));
	scene->textures = (char**)conf_malloc(scene->numMaterials * sizeof(char*));
	scene->normalMaps = (char**)conf_malloc(scene->numMaterials * sizeof(char*));
	scene->specularMaps = (char**)conf_calloc(scene->numMaterials, sizeof(char*));

	memset(scene->meshes, 0, scene->numMeshes * sizeof(Mesh));
	memset(scene->materials, 0, scene->numMaterials * sizeof(Material));

	// Metal does not load indices
#if defined(METAL)
	// Build vertex buffer data
	for (uint32_t i = 0; i < assimpScene->mNumMeshes; i++)
	{
		const aiMesh* assimpMesh = assimpScene->mMeshes[i];

		scene->meshes[i].startVertex = (uint32_t)scene->positions.size();
		scene->meshes[i].minBBox = float3((float)INT_MAX, (float)INT_MAX, (float)INT_MAX);
		scene->meshes[i].maxBBox = float3((float)-INT_MAX, (float)-INT_MAX, (float)-INT_MAX);
		scene->meshes[i].materialId = assimpMesh->mMaterialIndex;

		for (uint32_t j = 0; j < assimpMesh->mNumFaces; j++)
		{
			assert(assimpMesh->mFaces[j].mNumIndices == 3);
			for (uint32_t k = 0; k < assimpMesh->mFaces[j].mNumIndices; k++)
			{
				uint32_t index = assimpMesh->mFaces[j].mIndices[k];
				const aiVector3D& pos = assimpMesh->mVertices[index];
				const aiVector3D& tex = (assimpMesh->HasTextureCoords(0) ? assimpMesh->mTextureCoords[0][index] : aiVector3D(0, 0, 0));
				const aiVector3D& nor = (assimpMesh->HasNormals() ? assimpMesh->mNormals[index] : aiVector3D(0, 0, 0));
				const aiVector3D& tan = (assimpMesh->HasTangentsAndBitangents() ? assimpMesh->mTangents[index] : aiVector3D(0, 0, 0));

				if (pos.x < scene->meshes[i].minBBox.getX()) scene->meshes[i].minBBox.setX(pos.x);
				if (pos.y < scene->meshes[i].minBBox.getY()) scene->meshes[i].minBBox.setY(pos.y);
				if (pos.z < scene->meshes[i].minBBox.getZ()) scene->meshes[i].minBBox.setZ(pos.z);
				if (pos.x > scene->meshes[i].maxBBox.getX()) scene->meshes[i].maxBBox.setX(pos.x);
				if (pos.y > scene->meshes[i].maxBBox.getY()) scene->meshes[i].maxBBox.setY(pos.y);
				if (pos.z > scene->meshes[i].maxBBox.getZ()) scene->meshes[i].maxBBox.setZ(pos.z);

				SceneVertexPos vertexPos;
				vertexPos.x = pos.x;
				vertexPos.y = pos.y;
				vertexPos.z = pos.z;
				scene->positions.push_back(vertexPos);

				SceneVertexAttr vertexAttr;
				vertexAttr.u = tex.x;
				vertexAttr.v = tex.y;
				vertexAttr.nx = nor.x;
				vertexAttr.ny = nor.y;
				vertexAttr.nz = nor.z;
				vertexAttr.tx = tan.x;
				vertexAttr.ty = tan.y;
				vertexAttr.tz = tan.z;
				scene->attributes.push_back(vertexAttr);
			}
		}
		scene->meshes[i].vertexCount = (uint32_t)scene->positions.size() - scene->meshes[i].startVertex;
		scene->meshes[i].triangleCount = scene->meshes[i].vertexCount / 3;
		scene->totalTriangles += scene->meshes[i].triangleCount;
		scene->totalVertices += scene->meshes[i].vertexCount;
	}
#else
	for (unsigned int i = 0; i < assimpScene->mNumMeshes; i++) {
		aiMesh *mesh = assimpScene->mMeshes[i];
		scene->totalVertices += assimpScene->mMeshes[i]->mNumVertices;
		for (unsigned int f = 0; f < mesh->mNumFaces; f++)
			scene->totalTriangles += mesh->mFaces[f].mNumIndices;
	}

	scene->indices = tinystl::vector<uint32>(scene->totalTriangles, uint32_t(0));
	scene->positions = tinystl::vector<SceneVertexPos>(scene->totalVertices, SceneVertexPos{ 0 });
	scene->attributes = tinystl::vector<SceneVertexAttr>(scene->totalVertices, SceneVertexAttr{ 0 });

	for (unsigned int i = 0, kv = 0, ki = 0; i < assimpScene->mNumMeshes; i++)
	{
		aiMesh* mesh = assimpScene->mMeshes[i];

		scene->meshes[i].materialId = mesh->mMaterialIndex;
		scene->meshes[i].startIndex = ki;
		scene->meshes[i].vertexCount = mesh->mNumVertices;

		for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
			aiFace *face = mesh->mFaces + f;
			for (unsigned int j = 0; j < face->mNumIndices; j++, ki++)
				scene->indices[ki] = face->mIndices[j] + kv;
		}

		for (unsigned int v = 0; v < mesh->mNumVertices; v++, kv++) {
			aiVector3D *position = mesh->mVertices + v;
			scene->positions[kv].x = position->x;
			scene->positions[kv].y = position->y;
			scene->positions[kv].z = position->z;

			if (mesh->HasNormals()) {
				aiVector3D *normal = mesh->mNormals + v;
				scene->attributes[kv].normal = encodeDir(float3(normal->x, normal->y, normal->z));
			}

			if (mesh->HasTangentsAndBitangents()) {
				aiVector3D *tangent = mesh->mTangents + v;
				scene->attributes[kv].tangent = encodeDir(float3(tangent->x, tangent->y, tangent->z));
			}

			if (mesh->HasTextureCoords(0)) {
				aiVector3D *tc = mesh->mTextureCoords[0] + v;
				scene->attributes[kv].texCoord = pack2Floats(float2(tc->x, tc->y));
			}
		}

		scene->meshes[i].indexCount = ki - scene->meshes[i].startIndex;
	}
#endif

	// Try to load .twosided file with information about two sided materials
	tinystl::vector<aiString> doubleSidedMaterials;
	String twoSidedFileName = String(fileName) + String(".twosided");
	File file = {}; file.Open(twoSidedFileName.c_str(), FM_ReadBinary, FSR_Absolute);
	if (file.IsOpen())
	{
		while (!file.IsEof())
		{
			String line = file.ReadLine();
			aiString matName(line.c_str());
			doubleSidedMaterials.push_back(matName);
		}
		file.Close();
	}

	// Build material info data
	for (uint32_t i = 0; i < assimpScene->mNumMaterials; ++i)
	{
		char textureFileName[MAX_PATH] = "white.png";  // Default diffuse map
		char normalMapFileName[MAX_PATH] = "flat.png"; // Default normal map
		char specularMapFileName[MAX_PATH] = "white.png";

		aiMaterial* assimpMaterial = assimpScene->mMaterials[i];

		aiString texturePath;
		aiReturn texFound = assimpMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

		if (texFound == aiReturn_SUCCESS)
		{
			// texture found: use it!
			strncpy(textureFileName, texturePath.C_Str(), sizeof(textureFileName));
		}

		// If a DDS file is present with the same name, prefer that one
		int dotIndex;
		for (dotIndex = MAX_PATH - 1; dotIndex >= 0; dotIndex--)
			if (textureFileName[dotIndex] == '.')
				break;

		String ddsFileName;
		ddsFileName.append(textureFileName, dotIndex);
		ddsFileName.append(".DDS", 4);

		// Check if the DDS file exists
		if (FileSystem::FileExists(ddsFileName, FSR_Textures))
		{
			// File exists: prefer the DDS file
			strncpy(textureFileName, ddsFileName.c_str(), sizeof(textureFileName));
		}

		// Look for a normal map: the same texture filename with suffix _norm
		String fileName = FileSystem::GetFileName(textureFileName);
		String extension = FileSystem::GetExtension(textureFileName);
		String normalMapFile = fileName + String("_norm") + extension;
		String specularMapFile = fileName + String("_spec") + extension;
		if (FileSystem::FileExists(normalMapFile, FSR_Textures))
		{
			// File exists
			strncpy(normalMapFileName, normalMapFile.c_str(), normalMapFile.size());
		}
		if (FileSystem::FileExists(specularMapFile, FSR_Textures))
		{
			// File exists
			strncpy(specularMapFileName, specularMapFile.c_str(), specularMapFile.size());
		}

		// Determine if the material is two-sided
		int twoSided = 0;
		aiReturn res = aiGetMaterialInteger(assimpMaterial, AI_MATKEY_TWOSIDED, &twoSided);
		if (res == aiReturn_SUCCESS)
		{
			printf("Two sided: %s", texturePath.C_Str());
		}

		aiString materialName;
		res = aiGetMaterialString(assimpMaterial, AI_MATKEY_NAME, &materialName);
		if (res == aiReturn_SUCCESS)
		{
			// Is this material in the two sided material list?
			for (uint32_t j = 0; j < doubleSidedMaterials.size(); j++)
			{
				const aiString& matName = doubleSidedMaterials[j];
				if (materialName == matName)
				{
					twoSided = 1;
					break;
				}
			}
		}

		scene->materials[i].twoSided = (twoSided == 1);

		scene->textures[i] = (char*)conf_calloc(strlen(textureFileName) + 1, sizeof(char));
		memcpy(scene->textures[i], textureFileName, strlen(textureFileName));

		scene->normalMaps[i] = (char*)conf_calloc(strlen(normalMapFileName) + 1, sizeof(char));
		memcpy(scene->normalMaps[i], normalMapFileName, strlen(normalMapFileName));

		scene->specularMaps[i] = (char*)conf_calloc(strlen(specularMapFileName) + 1, sizeof(char));
		memcpy(scene->specularMaps[i], specularMapFileName, strlen(specularMapFileName));
	}

	aiReleaseImport(assimpScene);
#endif
	return scene;
}

void removeScene(Scene* scene)
{
	for (uint32_t i = 0; i < scene->numMaterials; ++i)
	{
		conf_free(scene->textures[i]);
		conf_free(scene->normalMaps[i]);
		conf_free(scene->specularMaps[i]);
	}

	scene->positions.~vector();
	scene->attributes.~vector();
#ifndef METAL
	scene->indices.~vector();
#endif

	conf_free(scene->textures);
	conf_free(scene->normalMaps);
	conf_free(scene->specularMaps);
	conf_free(scene->meshes);
	conf_free(scene->materials);
	conf_free(scene);
}

vec3 makeVec3(const SceneVertexPos& v)
{
	return vec3(v.x, v.y, v.z);
}

// Compute an array of clusters from the mesh vertices. Clusters are sub batches of the original mesh limited in number
// for more efficient CPU / GPU culling. CPU culling operates per cluster, while GPU culling operates per triangle for
// all the clusters that passed the CPU test.
void CreateClusters(bool twoSided, const Scene* pScene, Mesh* mesh)
{
#if defined(METAL)
	struct Triangle
	{
		vec3 vtx[3];
	};

	Triangle triangleCache[CLUSTER_SIZE * 3];

	mesh->clusterCount = (mesh->triangleCount + CLUSTER_SIZE - 1) / CLUSTER_SIZE;
	mesh->clusters = (Cluster*)conf_malloc(mesh->clusterCount * sizeof(Cluster));
	memset(mesh->clusters, 0, mesh->clusterCount * sizeof(Cluster));

	const uint32_t triangleStart = mesh->startVertex / 3;  // Assumes that we have no indices and every 3 vertices are a triangle (due to Metal limitation).

	for (uint32_t i = 0; i < mesh->clusterCount; ++i)
	{
		const int clusterStart = i * CLUSTER_SIZE;
		const uint32_t clusterEnd = min<uint32_t>(clusterStart + CLUSTER_SIZE, mesh->triangleCount);

		const int clusterTriangleCount = clusterEnd - clusterStart;

		// Load all triangles into our local cache
		for (uint32_t triangleIndex = clusterStart; triangleIndex < clusterEnd; ++triangleIndex)
		{
			triangleCache[triangleIndex - clusterStart].vtx[0] = makeVec3(pScene->positions[triangleStart + triangleIndex * 3]);
			triangleCache[triangleIndex - clusterStart].vtx[1] = makeVec3(pScene->positions[triangleStart + triangleIndex * 3 + 1]);
			triangleCache[triangleIndex - clusterStart].vtx[2] = makeVec3(pScene->positions[triangleStart + triangleIndex * 3 + 2]);
		}

		vec3 aabbMin = vec3(INFINITY, INFINITY, INFINITY);
		vec3 aabbMax = -aabbMin;

		vec3 coneAxis = vec3(0, 0, 0);

		for (int triangleIndex = 0; triangleIndex < clusterTriangleCount; ++triangleIndex)
		{
			const Triangle& triangle = triangleCache[triangleIndex];
			for (int j = 0; j < 3; ++j)
			{
				aabbMin = minPerElem(aabbMin, triangle.vtx[j]);
				aabbMax = maxPerElem(aabbMax, triangle.vtx[j]);
			}

			vec3 triangleNormal = cross(triangle.vtx[1] - triangle.vtx[0],
				triangle.vtx[2] - triangle.vtx[0]);
			//if(!(triangleNormal == vec3(0,0,0)))
			if (lengthSqr(triangleNormal) > 0.01f)
				triangleNormal = normalize(triangleNormal);

			coneAxis = coneAxis - triangleNormal;
		}

		// This is the cosine of the cone opening angle - 1 means it's 0??,
		// we're minimizing this value (at 0, it would mean the cone is 90?? open)
		float coneOpening = 1;

		// dont cull two sided meshes
		bool validCluster = !twoSided;

		vec3 center = (aabbMin + aabbMax) / 2;
		// if the axis is 0 then we have a invalid cluster
		if (coneAxis == vec3(0, 0, 0))
			validCluster = false;

		coneAxis = normalize(coneAxis);

		float t = -INFINITY;

		// cant find a cluster for 2 sided objects
		if (validCluster)
		{
			// We nee a second pass to find the intersection of the line center + t * coneAxis with the plane defined by each triangle
			for (int triangleIndex = 0; triangleIndex < clusterTriangleCount; ++triangleIndex)
			{
				const Triangle& triangle = triangleCache[triangleIndex];
				// Compute the triangle plane from the three vertices

				const vec3 triangleNormal = normalize(cross(triangle.vtx[1] - triangle.vtx[0],
					triangle.vtx[2] - triangle.vtx[0]));
				const float directionalPart = dot(coneAxis, -triangleNormal);

				if (directionalPart <= 0.0f)   //AMD BUG?: changed to <= 0 because directionalPart is used to divide a quantity
				{
					// No solution for this cluster - at least two triangles are facing each other
					validCluster = false;
					break;
				}

				// We need to intersect the plane with our cone ray which is center + t * coneAxis, and find the max
				// t along the cone ray (which points into the empty space) See: https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
				const float td = dot(center - triangle.vtx[0], triangleNormal) / -directionalPart;

				t = max(t, td);

				coneOpening = min(coneOpening, directionalPart);
			}
		}

		mesh->clusters[i].aabbMax = v3ToF3(aabbMax);
		mesh->clusters[i].aabbMin = v3ToF3(aabbMin);

		mesh->clusters[i].coneAngleCosine = sqrtf(1 - coneOpening * coneOpening);
		mesh->clusters[i].coneCenter = v3ToF3(center + coneAxis*t);
		mesh->clusters[i].coneAxis = v3ToF3(coneAxis);

		mesh->clusters[i].triangleCount = clusterTriangleCount;
		mesh->clusters[i].clusterStart = clusterStart;

		//#if AMD_GEOMETRY_FX_ENABLE_CLUSTER_CENTER_SAFETY_CHECK
		// If distance of coneCenter to the bounding box center is more than 16x the bounding box extent, the cluster is also invalid
		// This is mostly a safety measure - if triangles are nearly parallel to coneAxis, t may become very large and unstable
		if (validCluster)
		{
			const float aabbSize = length(aabbMax - aabbMin);
			const float coneCenterToCenterDistance = length(f3Tov3(mesh->clusters[i].coneCenter - v3ToF3(center)));

			if (coneCenterToCenterDistance > (16 * aabbSize))
				validCluster = false;
		}
		//#endif

		mesh->clusters[i].valid = validCluster;
	}
#else
	// 12 KiB stack space
	struct Triangle
	{
		vec3 vtx[3];
	};

	Triangle triangleCache[CLUSTER_SIZE * 3];

	const int triangleCount = mesh->indexCount / 3;
	const int clusterCount = (triangleCount + CLUSTER_SIZE - 1) / CLUSTER_SIZE;

	mesh->clusterCount = clusterCount;
	mesh->clusters = (Cluster*)conf_calloc(mesh->clusterCount, sizeof(Cluster));

	for (int i = 0; i < clusterCount; ++i)
	{
		const int clusterStart = i * CLUSTER_SIZE;
		const int clusterEnd = min(clusterStart + CLUSTER_SIZE, triangleCount);

		const int clusterTriangleCount = clusterEnd - clusterStart;

		// Load all triangles into our local cache
		for (int triangleIndex = clusterStart; triangleIndex < clusterEnd; ++triangleIndex)
		{
			triangleCache[triangleIndex - clusterStart].vtx[0] = makeVec3(pScene->positions[pScene->indices[mesh->startIndex + triangleIndex * 3]]);
			triangleCache[triangleIndex - clusterStart].vtx[1] = makeVec3(pScene->positions[pScene->indices[mesh->startIndex + triangleIndex * 3 + 1]]);
			triangleCache[triangleIndex - clusterStart].vtx[2] = makeVec3(pScene->positions[pScene->indices[mesh->startIndex + triangleIndex * 3 + 2]]);
		}

		vec3 aabbMin = vec3(INFINITY, INFINITY, INFINITY);
		vec3 aabbMax = -aabbMin;

		vec3 coneAxis = vec3(0, 0, 0);

		for (int triangleIndex = 0; triangleIndex < clusterTriangleCount; ++triangleIndex)
		{
			const auto& triangle = triangleCache[triangleIndex];
			for (int j = 0; j < 3; ++j)
			{
				aabbMin = minPerElem(aabbMin, triangle.vtx[j]);
				aabbMax = maxPerElem(aabbMax, triangle.vtx[j]);
			}

			vec3 triangleNormal = cross(
				triangle.vtx[1] - triangle.vtx[0],
				triangle.vtx[2] - triangle.vtx[0]);

			if (!(triangleNormal == vec3(0, 0, 0)))
				triangleNormal = normalize(triangleNormal);

			//coneAxis = DirectX::XMVectorAdd(coneAxis, DirectX::XMVectorNegate(triangleNormal));
			coneAxis = coneAxis - triangleNormal;
		}

		// This is the cosine of the cone opening angle - 1 means it's 0?,
		// we're minimizing this value (at 0, it would mean the cone is 90?
		// open)
		float coneOpening = 1;
		// dont cull two sided meshes
		bool validCluster = !twoSided;

		const vec3 center = (aabbMin + aabbMax) / 2;
		// if the axis is 0 then we have a invalid cluster
		if (coneAxis == vec3(0, 0, 0))
			validCluster = false;

		coneAxis = normalize(coneAxis);

		float t = -INFINITY;

		// cant find a cluster for 2 sided objects
		if (validCluster)
		{
			// We nee a second pass to find the intersection of the line center + t * coneAxis with the plane defined by each triangle
			for (int triangleIndex = 0; triangleIndex < clusterTriangleCount; ++triangleIndex)
			{
				const Triangle& triangle = triangleCache[triangleIndex];
				// Compute the triangle plane from the three vertices

				const vec3 triangleNormal = normalize(
					cross(
						triangle.vtx[1] - triangle.vtx[0],
						triangle.vtx[2] - triangle.vtx[0]));

				const float directionalPart = dot(coneAxis, -triangleNormal);

				if (directionalPart <= 0)   //AMD BUG?: changed to <= 0 because directionalPart is used to divide a quantity
				{
					// No solution for this cluster - at least two triangles are facing each other
					validCluster = false;
					break;
				}

				// We need to intersect the plane with our cone ray which is center + t * coneAxis, and find the max
				// t along the cone ray (which points into the empty space) See: https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
				const float td = dot(center - triangle.vtx[0], triangleNormal) / -directionalPart;

				t = max(t, td);

				coneOpening = min(coneOpening, directionalPart);
			}
		}

		mesh->clusters[i].aabbMax = v3ToF3(aabbMax);
		mesh->clusters[i].aabbMin = v3ToF3(aabbMin);

		mesh->clusters[i].coneAngleCosine = sqrtf(1 - coneOpening * coneOpening);
		mesh->clusters[i].coneCenter = v3ToF3(center + coneAxis * t);
		mesh->clusters[i].coneAxis = v3ToF3(coneAxis);

		mesh->clusters[i].triangleCount = clusterTriangleCount;
		mesh->clusters[i].clusterStart = clusterStart;

		//#if AMD_GEOMETRY_FX_ENABLE_CLUSTER_CENTER_SAFETY_CHECK
		// If distance of coneCenter to the bounding box center is more than 16x the bounding box extent, the cluster is also invalid
		// This is mostly a safety measure - if triangles are nearly parallel to coneAxis, t may become very large and unstable
		const float aabbSize = length(aabbMax - aabbMin);
		const float coneCenterToCenterDistance = length(f3Tov3(mesh->clusters[i].coneCenter) - center);

		if (coneCenterToCenterDistance > (16 * aabbSize))
			validCluster = false;

		mesh->clusters[i].valid = validCluster;
	}
#endif
}

#if defined(METAL)
void addClusterToBatchChunk(const Cluster* cluster, const Mesh* mesh, FilterBatchChunk* batchChunk)
{
	FilterBatchData* batchData = &batchChunk->batches[batchChunk->currentBatchCount++];

	batchData->triangleCount = cluster->triangleCount;
	batchData->triangleOffset = cluster->clusterStart + mesh->startVertex / 3; // each 3 vertices form a triangle
}
#else
void addClusterToBatchChunk(const Cluster* cluster, uint batchStart, uint accumDrawCount, uint accumNumTriangles, int meshIndex, FilterBatchChunk* batchChunk)
{
	const int filteredIndexBufferStartOffset = accumNumTriangles * 3;

	FilterBatchData* smallBatchData = &batchChunk->batches[batchChunk->currentBatchCount++];

	smallBatchData->accumDrawIndex = accumDrawCount;
	smallBatchData->faceCount = cluster->triangleCount;
	smallBatchData->meshIndex = meshIndex;

	// Offset relative to the start of the mesh
	smallBatchData->indexOffset = cluster->clusterStart * 3;
	smallBatchData->outputIndexOffset = filteredIndexBufferStartOffset;
	smallBatchData->drawBatchStart = batchStart;
}
#endif

void createCubeBuffers(Renderer* pRenderer, CmdPool* cmdPool, Buffer** ppVertexBuffer, Buffer** ppIndexBuffer)
{
	UNREF_PARAM(pRenderer);
	UNREF_PARAM(cmdPool);
	// Create vertex buffer
	float vertexData[] = {
		-1, -1, -1, 1,
		1, -1, -1, 1,
		1, 1, -1, 1,
		-1, 1, -1, 1,
		-1, -1, 1, 1,
		1, -1, 1, 1,
		1, 1, 1, 1,
		-1, 1, 1, 1,
	};

	BufferLoadDesc vbDesc = {};
	vbDesc.mDesc.mUsage = BUFFER_USAGE_VERTEX;
	vbDesc.mDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	vbDesc.mDesc.mSize = sizeof(vertexData);
	vbDesc.mDesc.mVertexStride = sizeof(float) * 4;
	vbDesc.pData = vertexData;
	vbDesc.ppBuffer = ppVertexBuffer;
	addResource(&vbDesc);

	// Create index buffer
	uint16_t indices[6 * 6] =
	{
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};

	BufferLoadDesc ibDesc = {};
	ibDesc.mDesc.mUsage = BUFFER_USAGE_INDEX;
	ibDesc.mDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	ibDesc.mDesc.mSize = sizeof(indices);
	ibDesc.mDesc.mIndexType = INDEX_TYPE_UINT16;
	ibDesc.pData = indices;
	ibDesc.ppBuffer = ppIndexBuffer;
	addResource(&ibDesc);
}

void destroyBuffers(Renderer* pRenderer, Buffer* outVertexBuffer, Buffer* outIndexBuffer)
{
	UNREF_PARAM(pRenderer);
	removeResource(outVertexBuffer);
	removeResource(outIndexBuffer);
}

void createTessellatedQuadBuffers(Buffer** ppVertexBuffer, Buffer** ppIndexBuffer, unsigned tessellationX, unsigned tessellationY)
{
	assert(tessellationX >= 1);
	assert(tessellationY >= 1);

	// full screen quad coordinates [-1, -1] to [1, 1] -> width & height = 2
	const float width = 2.0f;
	const float height = 2.0f;
	const float dx = width / tessellationX;
	const float dy = height / tessellationY;

	const int numQuads = tessellationX * tessellationY;
	const int numVertices = (tessellationX + 1) * (tessellationY + 1);

	tinystl::vector<vec4> vertices(numVertices);
	const unsigned m = tessellationX + 1;
	const unsigned n = tessellationY + 1;
	for (unsigned i = 0; i < n; ++i)
	{
		const float y = i * dy - 1.0f;		// offset w/ -1.0f :  [0,2]->[-1,1]
		for (unsigned j = 0; j < m; ++j)
		{
			const float x = j * dx - 1.0f;	// offset w/ -1.0f :  [0,2]->[-1,1]
			vertices[i*m + j] = vec4(x, y, 0, 1);
		}
	}

	BufferLoadDesc vbDesc = {};
	vbDesc.mDesc.mUsage = BUFFER_USAGE_VERTEX;
	vbDesc.mDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	vbDesc.mDesc.mSize = vertices.size() * sizeof(vec4);
	vbDesc.mDesc.mVertexStride = sizeof(vec4);
	vbDesc.pData = vertices.data();
	vbDesc.ppBuffer = ppVertexBuffer;
	addResource(&vbDesc);


	tinystl::vector<uint16_t> indices(numQuads * 6);
	//	  A	+------+ B
	//		|	 / |
	//		|	/  |
	//		|  /   |
	//		| /	   |
	//		|/	   |
	//	  C	+------+ D
	//
	//	A	: V(i  , j  )
	//	B	: V(i  , j+1)
	//	C	: V(i+1, j  )
	//	D	: V(i+1, j+1)
	//
	//	ABC	: (i*n +j    , i*n + j+1, (i+1)*n + j  )
	//	CBD : ((i+1)*n +j, i*n + j+1, (i+1)*n + j+1)
	unsigned quad = 0;
	for (unsigned i = 0; i < tessellationY; ++i)
	{
		for (unsigned j = 0; j < tessellationX; ++j)
		{
			indices[quad * 6 + 0] = (uint16_t)(i*m + j);
			indices[quad * 6 + 1] = (uint16_t)(i*m + j + 1);
			indices[quad * 6 + 2] = (uint16_t)((i + 1)*m + j);
			indices[quad * 6 + 3] = (uint16_t)((i + 1)*m + j);
			indices[quad * 6 + 4] = (uint16_t)(i*m + j + 1);
			indices[quad * 6 + 5] = (uint16_t)((i + 1)*m + j + 1);
			quad++;
		}
	}

	BufferLoadDesc ibDesc = {};
	ibDesc.mDesc.mUsage = BUFFER_USAGE_INDEX;
	ibDesc.mDesc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_ONLY;
	ibDesc.mDesc.mSize = indices.size() * sizeof(uint16_t);
	ibDesc.mDesc.mIndexType = INDEX_TYPE_UINT16;
	ibDesc.pData = indices.data();
	ibDesc.ppBuffer = ppIndexBuffer;
	addResource(&ibDesc);
}
