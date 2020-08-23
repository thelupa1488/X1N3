#pragma once

#include "Definitions.hpp"

#include "Vector.hpp"
#include "VMatrix.hpp"

namespace SDK
{
	class CUtlBuffer;
	struct virtualmodel_t;
	typedef unsigned short MDLHandle_t;
	typedef float Quaternion[4];
	typedef float RadianEuler[3];

	class CPhysCollide;
	class IClientRenderable;
	struct virtualmodel_t;
	struct model_t;

	enum Hitboxes
	{
		HITBOX_HEAD,
		HITBOX_NECK,
		HITBOX_PELVIS,
		HITBOX_BELLY,
		HITBOX_THORAX,
		HITBOX_LOWER_CHEST,
		HITBOX_UPPER_CHEST,
		HITBOX_RIGHT_THIGH,
		HITBOX_LEFT_THIGH,
		HITBOX_RIGHT_CALF,
		HITBOX_LEFT_CALF,
		HITBOX_RIGHT_FOOT,
		HITBOX_LEFT_FOOT,
		HITBOX_RIGHT_HAND,
		HITBOX_LEFT_HAND,
		HITBOX_RIGHT_UPPER_ARM,
		HITBOX_RIGHT_FOREARM,
		HITBOX_LEFT_UPPER_ARM,
		HITBOX_LEFT_FOREARM,
		HITBOX_MAX
	};

	struct mstudiobone_t
	{
		int                    sznameindex;
		inline char* const     pszName(void) const { return ((char*)this) + sznameindex; }
		int                    parent;
		int                    bonecontroller[6];    // bone controller index, -1 == none
		Vector                 pos;
		Quaternion             quat;
		RadianEuler            rot;
		// compression scale
		Vector                 posscale;
		Vector                 rotscale;

		matrix3x4_t            poseToBone;
		Quaternion             qAlignment;
		int                    flags;
		int                    proctype;
		int                    procindex;
		mutable int            physicsbone;
		inline void*           pProcedure() const 
		{ 
			if (procindex == 0) 
				return NULL; 
			else
				return (void*)(((BYTE*)this) + procindex); 
		};
		int                    surfacepropidx;
		inline char* const     pszSurfaceProp(void) const 
		{ 
			return ((char*)this) + surfacepropidx; 
		}
		inline int             GetSurfaceProp(void) const 
		{ 
			return surfacepropLookup; 
		}

		int                    contents;
		int                    surfacepropLookup;
		int                    m_iPad01[7];

		mstudiobone_t() {}
	private:
		// No copy constructors allowed
		mstudiobone_t(const mstudiobone_t& vOther);
	};

	struct mstudiobbox_t
	{
		int         bone;
		int         group;
		Vector      bbmin;
		Vector      bbmax;
		int         szhitboxnameindex;
		int32_t     m_iPad01[3];
		float       m_flRadius;
		int32_t     m_iPad02[4];

		const char* GetName()
		{
			if (!szhitboxnameindex) return nullptr;
			return (const char*)((uint8_t*)this + szhitboxnameindex);
		}
	};

	struct mstudiohitboxset_t
	{
		int    sznameindex;
		int    numhitboxes;
		int    hitboxindex;

		const char* GetName()
		{
			if (!sznameindex) return nullptr;
			return (const char*)((uint8_t*)this + sznameindex);
		}

		mstudiobbox_t* GetHitbox(int i)
		{
			if (i > numhitboxes) return nullptr;
			return (mstudiobbox_t*)((uint8_t*)this + hitboxindex) + i;
		}
	};

	struct model_t
	{
		void* fnHandle;               //0x0000 
		char    szName[260];            //0x0004 
		__int32 nLoadFlags;             //0x0108 
		__int32 nServerCount;           //0x010C 
		__int32 type;                   //0x0110 
		__int32 flags;                  //0x0114 
		Vector  vecMins;                //0x0118 
		Vector  vecMaxs;                //0x0124 
		float   radius;                 //0x0130 
		char    pad[0x1C];              //0x0134
	};//Size=0x0150

	struct studiohdr_t
	{
		__int32 id;                     //0x0000 
		__int32 version;                //0x0004 
		long    checksum;               //0x0008 
		char    szName[64];             //0x000C 
		__int32 length;                 //0x004C 
		Vector  vecEyePos;              //0x0050 
		Vector  vecIllumPos;            //0x005C 
		Vector  vecHullMin;             //0x0068 
		Vector  vecHullMax;             //0x0074 
		Vector  vecBBMin;               //0x0080 
		Vector  vecBBMax;               //0x008C 
		__int32 flags;                  //0x0098 
		__int32 numbones;               //0x009C 
		__int32 boneindex;              //0x00A0 
		__int32 numbonecontrollers;     //0x00A4 
		__int32 bonecontrollerindex;    //0x00A8 
		__int32 numhitboxsets;          //0x00AC 
		__int32 hitboxsetindex;         //0x00B0 
		__int32 numlocalanim;           //0x00B4 
		__int32 localanimindex;         //0x00B8 
		__int32 numlocalseq;            //0x00BC 
		__int32 localseqindex;          //0x00C0 
		__int32 activitylistversion;    //0x00C4 
		__int32 eventsindexed;          //0x00C8 
		__int32 numtextures;            //0x00CC 
		__int32 textureindex;           //0x00D0

		mstudiohitboxset_t* GetHitboxSet(int i)
		{
			if (i > numhitboxsets) return nullptr;
			return (mstudiohitboxset_t*)((uint8_t*)this + hitboxsetindex) + i;
		}
		mstudiobone_t* GetBone(int i)
		{
			if (i > numbones) return nullptr;
			return (mstudiobone_t*)((uint8_t*)this + boneindex) + i;
		}
	};

	enum RenderableTranslucencyType_t
	{
		RENDERABLE_IS_OPAQUE = 0 ,
		RENDERABLE_IS_TRANSLUCENT ,
		RENDERABLE_IS_TWO_PASS ,	// has both translucent and opaque sub-partsa
	};

	class IVModelInfo
	{
	public:
		virtual                                 ~IVModelInfo(void) {}
		virtual const model_t*                  GetModel(int modelindex) const = 0;
		virtual int                             GetModelIndex(const char* name) const = 0;
		virtual const char*                     GetModelName(const model_t* model) const = 0;
		virtual vcollide_t*                     GetVCollide(const model_t* model) const = 0;
		virtual vcollide_t*                     GetVCollide(int modelindex) const = 0;
		virtual void                            GetModelBounds(const model_t* model, Vector& mins, Vector& maxs) const = 0;
		virtual void                            GetModelRenderBounds(const model_t* model, Vector& mins, Vector& maxs) const = 0;
		virtual int                             GetModelFrameCount(const model_t* model) const = 0;
		virtual int                             GetModelType(const model_t* model) const = 0;
		virtual void*                           GetModelExtraData(const model_t* model) = 0;
		virtual bool                            ModelHasMaterialProxy(const model_t* model) const = 0;
		virtual bool                            IsTranslucent(model_t const* model) const = 0;
		virtual bool                            IsTranslucentTwoPass(const model_t* model) const = 0;
		virtual void                            Unused0() {};
		virtual void                            UNUSED() = 0;
		virtual void                            UNUSE11D() = 0;
		virtual RenderableTranslucencyType_t    ComputeTranslucencyType(const model_t* model, int nSkin, int nBody) = 0;
		virtual int                             GetModelMaterialCount(const model_t* model) const = 0;
		virtual void                            GetModelMaterials(const model_t* model, int count, IMaterial** ppMaterial) = 0;
		virtual bool                            IsModelVertexLit(const model_t* model) const = 0;
		virtual const char*                     GetModelKeyValueText(const model_t* model) = 0;
		virtual bool                            GetModelKeyValue(const model_t* model, CUtlBuffer& buf) = 0;
		virtual float                           GetModelRadius(const model_t* model) = 0;
		virtual studiohdr_t*                     GetStudioHdr(MDLHandle_t handle) = 0;
		virtual const studiohdr_t*              FindModel(const studiohdr_t* pStudioHdr, void** cache, const char* modelname) const = 0;
		virtual const studiohdr_t*              FindModel(void* cache) const = 0;
		virtual virtualmodel_t*                 GetVirtualModel(const studiohdr_t* pStudioHdr) const = 0;
		virtual uint8_t*                        GetAnimBlock(const studiohdr_t* pStudioHdr, int iBlock) const = 0;
		virtual void                            GetModelMaterialColorAndLighting(const model_t* model, Vector const& origin, QAngle const& angles, trace_t* pTrace, Vector& lighting, Vector& matColor) = 0;
		virtual void                            GetIlluminationPoint(const model_t* model, IClientRenderable* pRenderable, Vector const& origin, QAngle const& angles, Vector* pLightingCenter) = 0;
		virtual int                             GetModelContents(int modelIndex) const = 0;
		virtual studiohdr_t*                    GetStudioModel(const model_t* mod) = 0;
		virtual int                             GetModelSpriteWidth(const model_t* model) const = 0;
		virtual int                             GetModelSpriteHeight(const model_t* model) const = 0;
		virtual void                            SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
		virtual void                            GetLevelScreenFadeRange(float* pMinArea, float* pMaxArea) const = 0;
		virtual void                            SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;
		virtual unsigned char                   ComputeLevelScreenFade(const Vector& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
		virtual unsigned char                   ComputeViewScreenFade(const Vector& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
		virtual int                             GetAutoplayList(const studiohdr_t* pStudioHdr, unsigned short** pAutoplayList) const = 0;
		virtual CPhysCollide*                   GetCollideForVirtualTerrain(int index) = 0;
		virtual bool                            IsUsingFBTexture(const model_t* model, int nSkin, int nBody, IClientRenderable** pClientRenderable) const = 0;
		virtual const model_t*                  FindOrLoadModel(const char* name) const = 0;
		virtual MDLHandle_t                     GetCacheHandle(const model_t* model) const = 0;
		virtual int                             GetBrushModelPlaneCount(const model_t* model) const = 0;
		virtual void                            GetBrushModelPlane(const model_t* model, int nIndex, cplane_t& plane, Vector* pOrigin) const = 0;
		virtual int                             GetSurfacepropsForVirtualTerrain(int index) = 0;
		virtual bool                            UsesEnvCubemap(const model_t* model) const = 0;
		virtual bool                            UsesStaticLighting(const model_t* model) const = 0;
	};
}