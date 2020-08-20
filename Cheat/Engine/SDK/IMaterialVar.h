#pragma once
#include "VMatrix.hpp"
#include "Vector4D.hpp"

namespace SDK
{
	class IMaterial;
	class VMatrix;
	class ITexture;

	//-----------------------------------------------------------------------------
	// Various material var types
	//-----------------------------------------------------------------------------
	enum MaterialVarType_t
	{
		MATERIAL_VAR_TYPE_FLOAT = 0,
		MATERIAL_VAR_TYPE_STRING,
		MATERIAL_VAR_TYPE_VECTOR,
		MATERIAL_VAR_TYPE_TEXTURE,
		MATERIAL_VAR_TYPE_INT,
		MATERIAL_VAR_TYPE_FOURCC,
		MATERIAL_VAR_TYPE_UNDEFINED,
		MATERIAL_VAR_TYPE_MATRIX,
		MATERIAL_VAR_TYPE_MATERIAL,
	};

	typedef unsigned short MaterialVarSym_t;

	class IMaterialVar
	{
	public:
		typedef unsigned long FourCC;

	protected:
		// base data and accessors
		char* m_pStringVal;
		int m_intVal;
		Vector4D m_VecVal;

		// member data. total = 4 bytes
		unsigned char m_Type : 4;
		unsigned char m_nNumVectorComps : 3;
		unsigned char m_bFakeMaterialVar : 1;
		unsigned char m_nTempIndex;
		void* m_Name;

	public:
		// class factory methods
		static IMaterialVar*    Create(IMaterial* pMaterial, char const* pKey, VMatrix const& matrix);
		static IMaterialVar*    Create(IMaterial* pMaterial, char const* pKey, char const* pVal);
		static IMaterialVar*    Create(IMaterial* pMaterial, char const* pKey, float* pVal, int numcomps);
		static IMaterialVar*    Create(IMaterial* pMaterial, char const* pKey, float val);
		static IMaterialVar*    Create(IMaterial* pMaterial, char const* pKey, int val);
		static IMaterialVar*    Create(IMaterial* pMaterial, char const* pKey);
		static void             Destroy(IMaterialVar* pVar);
		static MaterialVarSym_t	GetSymbol(char const* pName);
		static MaterialVarSym_t	FindSymbol(char const* pName);
		static bool             SymbolMatches(char const* pName, MaterialVarSym_t symbol);
		static void             DeleteUnreferencedTextures(bool enable);

		virtual ITexture*       GetTextureValue(void) = 0;

		virtual char const*     GetName(void) const = 0;
		virtual MaterialVarSym_t GetNameAsSymbol() const = 0;

		virtual void			SetFloatValue(float val) = 0;

		virtual void			SetIntValue(int val) = 0;

		virtual void			SetStringValue(char const* val) = 0;
		virtual char const*     GetStringValue(void) const = 0;

		// Use FourCC values to pass app-defined data structures between
		// the proxy and the shader. The shader should ignore the data if
		// its FourCC type not correct.	
		virtual void			SetFourCCValue(FourCC type, void* pData) = 0;
		virtual void			GetFourCCValue(FourCC* type, void** ppData) = 0;

		// Vec (dim 2-4)
		virtual void            unk() = 0;
		virtual void			SetVecValue(float const* val, int numcomps) = 0;
		virtual void			SetVecValue(float x, float y) = 0;
		virtual void			SetVecValue(float x, float y, float z) = 0;
		virtual void			SetVecValue(float x, float y, float z, float w) = 0;
		virtual void			GetLinearVecValue(float* val, int numcomps) const = 0;

		// revisit: is this a good interface for textures?
		virtual void			SetTextureValue(ITexture*) = 0;

		virtual IMaterial*      GetMaterialValue(void) = 0;
		virtual void			SetMaterialValue(IMaterial*) = 0;

		virtual bool			IsDefined() const = 0;
		virtual void			SetUndefined() = 0;

		// Matrix
		virtual void			SetMatrixValue(VMatrix const& matrix) = 0;
		virtual const VMatrix&  GetMatrixValue() = 0;
		virtual bool			MatrixIsIdentity() const = 0;

		// Copy....
		virtual void			CopyFrom(IMaterialVar* pMaterialVar) = 0;

		virtual void			SetValueAutodetectType(char const* val) = 0;

		virtual IMaterial*      GetOwningMaterial() = 0;

		//set just 1 component
		virtual void			SetVecComponentValue(float fVal, int nComponent) = 0;

	protected:
		virtual int				GetIntValueInternal(void) const = 0;
		virtual float			GetFloatValueInternal(void) const = 0;
		virtual float const*    GetVecValueInternal() const = 0;
		virtual void			GetVecValueInternal(float* val, int numcomps) const = 0;
		virtual int				VectorSizeInternal() const = 0;

	public:
		__forceinline MaterialVarType_t GetType(void) const
		{
			return (MaterialVarType_t)m_Type;
		}

		__forceinline bool IsTexture() const
		{
			return m_Type == MATERIAL_VAR_TYPE_TEXTURE;
		}

		__forceinline operator ITexture* ()
		{
			return GetTextureValue();
		}

		// NOTE: Fast methods should only be called in thread-safe situations
		__forceinline int GetIntValueFast(void) const
		{
			// Set methods for float and vector update this
			return m_intVal;
		}

		__forceinline float GetFloatValueFast(void) const
		{
			return m_VecVal[0];
		}

		__forceinline float const* GetVecValueFast() const
		{
			return m_VecVal.Base();
		}

		__forceinline void GetVecValueFast(float* val, int numcomps) const
		{
			//assert((numcomps > 0) && (numcomps <= 4));
			for (int i = 0; i < numcomps; i++)
			{
				val[i] = m_VecVal[i];
			}
		}

		__forceinline int VectorSizeFast() const
		{
			return m_nNumVectorComps;
		}

#ifdef FAST_MATERIALVAR_ACCESS
		__forceinline int GetIntValue(void) const
		{
			return GetIntValueFast();
		}

		__forceinline float GetFloatValue(void) const
		{
			return GetFloatValueFast();
		}

		__forceinline float const* GetVecValue() const
		{
			return GetVecValueFast();
		}

		__forceinline void GetVecValue(float* val, int numcomps) const
		{
			GetVecValueFast(val, numcomps);
		}

		__forceinline int VectorSize() const
		{
			return VectorSizeFast();
		}
#else // !FAST_MATERIALVAR_ACCESS
		__forceinline int GetIntValue(void) const
		{
			return GetIntValueInternal();
		}

		__forceinline float GetFloatValue(void) const
		{
			return GetFloatValueInternal();
		}

		__forceinline float const* GetVecValue() const
		{
			return GetVecValueInternal();
		}

		__forceinline void GetVecValue(float* val, int numcomps) const
		{
			return GetVecValueInternal(val, numcomps);
		}

		__forceinline int VectorSize() const
		{
			return VectorSizeInternal();
		}
#endif

	private:
		__forceinline void SetTempIndex(int nIndex)
		{
			m_nTempIndex = nIndex;
		}

		friend void EnableThreadedMaterialVarAccess(bool bEnable, IMaterialVar** ppParams, int nVarCount);
	};
}