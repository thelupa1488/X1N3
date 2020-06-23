#pragma once

#include "SDK.h"

namespace Engine
{
    class CBaseEntity;
    class CBaseViewModel;
}
using namespace Engine;

namespace SDK
{
	struct colorVec
	{
		unsigned r, g, b, a;
	};

	class IRefCounted
	{
	public:
		virtual int AddRef() = 0;
		virtual int Release() = 0;
	};

	class IWorldRenderList : public IRefCounted
	{};

	struct VisibleFogVolumeInfo_t
	{
		int m_nVisibleFogVolume;
		int m_nVisibleFogVolumeLeaf;
		bool m_bEyeInFogVolume;
		float m_flDistanceToWater;
		float m_flWaterHeight;
		IMaterial* m_pFogVolumeMaterial;
	};

	typedef unsigned short LeafIndex_t;

	enum
	{
		INVALID_LEAF_INDEX = (LeafIndex_t)~0
	};

	struct WorldListLeafData_t
	{
		LeafIndex_t leafIndex; // 16 bits
		int16 waterData;
		uint16 firstTranslucentSurface; // engine-internal list index
		uint16 translucentSurfaceCount; // count of translucent surfaces+disps
	};

	struct WorldListInfo_t
	{
		int m_ViewFogVolume;
		int m_LeafCount;
		bool m_bHasWater;
		WorldListLeafData_t* m_pLeafDataList;
	};

	struct VisOverrideData_t
	{
		Vector m_vecVisOrigin; // The point to to use as the viewpoint for area portal backface cull checks.
		float m_fDistToAreaPortalTolerance; // The distance from an area portal before using the full screen as the viewable portion.
	};

	struct BrushVertex_t
	{
		Vector m_Pos;
		Vector m_Normal;
		Vector m_TangentS;
		Vector m_TangentT;
		Vector2D m_TexCoord;
		Vector2D m_LightmapCoord;

	private:
		BrushVertex_t(const BrushVertex_t& src);
	};

	class IBrushSurface
	{
	public:
		// Computes texture coordinates + lightmap coordinates given a world position
		virtual void ComputeTextureCoordinate(Vector const& worldPos, Vector2D& texCoord) = 0;
		virtual void ComputeLightmapCoordinate(Vector const& worldPos, Vector2D& lightmapCoord) = 0;

		// Gets the vertex data for this surface
		virtual int GetVertexCount() const = 0;
		virtual void GetVertexData(BrushVertex_t* pVerts) = 0;

		// Gets at the material properties for this surface
		virtual IMaterial* GetMaterial() = 0;
	};

	class IBrushRenderer
	{
	public:
		// Draws the surface; returns true if decals should be rendered on this surface
		virtual bool RenderBrushModelSurface(CBaseEntity* pBaseEntity, IBrushSurface* pBrushSurface) = 0;
	};

    //-----------------------------------------------------------------------------
    // Purpose: View setup and rendering
    //-----------------------------------------------------------------------------
	class IViewRender
	{
	public:
		virtual void                Init(void) = 0;
		virtual void                LevelInit(void) = 0;
		virtual void                LevelShutdown(void) = 0;
		virtual void                Shutdown(void) = 0;
		virtual void                OnRenderStart() = 0;
		virtual	void                Render(vrect_t* rect) = 0;
		virtual void                RenderView(const CViewSetup& view, int nClearFlags, int whatToDraw) = 0;
		virtual int                 GetDrawFlags() = 0;
		virtual void                StartPitchDrift(void) = 0;
		virtual void                StopPitchDrift(void) = 0;
		virtual void*               GetFrustum() = 0;
		virtual bool                ShouldDrawBrushModels(void) = 0;
		virtual const CViewSetup*   GetPlayerViewSetup(void) const = 0;
		virtual const CViewSetup*   GetViewSetup(void) const = 0;
		virtual void                DisableVis(void) = 0;
		virtual int                 BuildWorldListsNumber() const = 0;
		virtual void                SetCheapWaterStartDistance(float flCheapWaterStartDistance) = 0;
		virtual void                SetCheapWaterEndDistance(float flCheapWaterEndDistance) = 0;
		virtual void                GetWaterLODParams(float& flCheapWaterStartDistance, float& flCheapWaterEndDistance) = 0;
		virtual void                DriftPitch(void) = 0;
		virtual void                SetScreenOverlayMaterial(IMaterial* pMaterial) = 0;
		virtual IMaterial*          GetScreenOverlayMaterial() = 0;
		virtual void                WriteSaveGameScreenshot(const char* pFilename) = 0;
		virtual void                WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height) = 0;
		virtual void                QueueOverlayRenderView(const CViewSetup& view, int nClearFlags, int whatToDraw) = 0;
		virtual float               GetZNear() = 0;
		virtual float               GetZFar() = 0;
		virtual void                GetScreenFadeDistances(float* min, float* max) = 0;
		virtual CBaseEntity*        GetCurrentlyDrawingEntity() = 0;
		virtual void                SetCurrentlyDrawingEntity(CBaseEntity* pEnt) = 0;
	};
}                                                                                                                                                                                                                                                           