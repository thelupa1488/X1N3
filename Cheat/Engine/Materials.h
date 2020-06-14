#pragma once

namespace Materials
{
	extern IMaterial* material_flat;
	extern IMaterial* material_flat_ignorez;

	extern IMaterial* material_texture;
	extern IMaterial* material_texture_ignorez;

	extern IMaterial* material_wireframe;
	extern IMaterial* material_wireframe_ignorez;

	extern IMaterial* material_metallic_plus;
	extern IMaterial* material_metallic_plus_ignorez;

	extern IMaterial* material_metallic;
	extern IMaterial* material_metallic_ignorez;

	extern IMaterial* material_animated;
	extern IMaterial* material_glowoverlay;

	extern IMaterial* material_bubble;
	extern IMaterial* material_dogtag;

	extern void InitializationMaterials();
	extern void DeleteMaterials();
}