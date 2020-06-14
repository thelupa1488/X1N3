#include "Engine.h"
#include "Materials.h"

IMaterial* Materials::material_flat;
IMaterial* Materials::material_flat_ignorez;

IMaterial* Materials::material_texture;
IMaterial* Materials::material_texture_ignorez;

IMaterial* Materials::material_wireframe;
IMaterial* Materials::material_wireframe_ignorez;

IMaterial* Materials::material_metallic_plus;
IMaterial* Materials::material_metallic_plus_ignorez;

IMaterial* Materials::material_metallic;
IMaterial* Materials::material_metallic_ignorez;

IMaterial* Materials::material_animated;
IMaterial* Materials::material_glowoverlay;

IMaterial* Materials::material_bubble;
IMaterial* Materials::material_dogtag;

void Materials::InitializationMaterials()
{
	std::ofstream(XorStr("csgo/materials/glowOverlay.vmt")) << (R"#("VertexLitGeneric" {
    	"$additive" "1"
    	"$envmap" "models/effects/cube_white"
		"$model"        "1"
    	"$envmaptint" "[1 1 1]"
    	"$envmapfresnel" "1"
    	"$envmapfresnelminmaxexp" "[0 1 2]"
    	"$alpha" "0.8"
    })#");
	std::ofstream(XorStr("csgo\\materials\\textured.vmt")) << (R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#");
	std::ofstream(XorStr("csgo\\materials\\textured_ignorez.vmt")) << (R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#");
	std::ofstream(XorStr("csgo\\materials\\flat.vmt")) << (R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#");
	std::ofstream(XorStr("csgo\\materials\\flat_ignorez.vmt")) << (R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#");
	std::ofstream{ XorStr("csgo\\materials\\chamsAnimated.vmt") } <<
		"VertexLitGeneric { $envmap editor/cube_vertigo $envmapcontrast 1 $envmaptint \"[.7 .7 .7]\" $basetexture dev/zone_warning proxies { texturescroll { texturescrollvar $basetexturetransform texturescrollrate 0.6 texturescrollangle 90 } } }";

	std::ofstream(XorStr("csgo\\materials\\metallic_plus.vmt")) << (R"#("VertexLitGeneric" 
{
		"$basetexture" "vgui/white"
		"$bumpmap" "de_nuke/hr_nuke/pool_water_normals_002"
		"$bumptransform" "center 0.5 0.5 scale 0.25 0.25 rotate 0.0 translate 0.0 0.0"
		"$ignorez" "0"
		"$nofog" "1"
		"$model" "1"
		"$color2" "[1.0, 1.0, 1.0]"
		"$halflambert" "1"
		"$envmap" "env_cubemap"
		"$envmaptint" "[0.1 0.1 0.1]"
		"$envmapfresnel" "1.0"
		"$envmapfresnelminmaxexp" "[1.0, 1.0, 1.0]"
		"$phong" "1"
		"$phongexponent" "1024"
		"$phongboost" "4.0"
		"$phongfresnelranges" "[1.0, 1.0, 1.0]"
		"$rimlight" "1"
		"$rimlightexponent" "4.0"
		"$rimlightboost" "2.0"
        "$pearlescent" "4"
    
		"Proxies"
		{
			"TextureScroll"
			{
				"textureScrollVar" "$bumptransform"
				"textureScrollRate" "0.25"
				"textureScrollAngle" "0.0"
			}
		}
	}
)#");

	std::ofstream(XorStr("csgo\\materials\\metallic_plus_ignorez.vmt")) << (R"#("VertexLitGeneric" 
{
		"$basetexture" "vgui/white"
		"$bumpmap" "de_nuke/hr_nuke/pool_water_normals_002"
		"$bumptransform" "center 0.5 0.5 scale 0.25 0.25 rotate 0.0 translate 0.0 0.0"
		"$ignorez" "1"
		"$nofog" "1"
		"$model" "1"
		"$color2" "[1.0, 1.0, 1.0]"
		"$halflambert" "1"
		"$envmap" "env_cubemap"
		"$envmaptint" "[0.1 0.1 0.1]"
		"$envmapfresnel" "1.0"
		"$envmapfresnelminmaxexp" "[1.0, 1.0, 1.0]"
		"$phong" "1"
		"$phongexponent" "1024"
		"$phongboost" "4.0"
		"$phongfresnelranges" "[1.0, 1.0, 1.0]"
		"$rimlight" "1"
		"$rimlightexponent" "4.0"
		"$rimlightboost" "2.0"
        "$pearlescent" "1"
    
		"Proxies"
		{
			"TextureScroll"
			{
				"textureScrollVar" "$bumptransform"
				"textureScrollRate" "0.25"
				"textureScrollAngle" "0.0"
			}
		}
	}
)#");

	std::ofstream(XorStr("csgo\\materials\\wireframe.vmt")) << R"#("VertexLitGeneric" 
{ 
"$basetexture" "vgui/white" 
"$ignorez" "0" 
"$envmap" "" 
"$nofog" "1" 
"$model" "1" 
"$nocull" "0" 
"$selfillum" "1" 
"$halflambert" "1" 
"$znearer" "0" 
"$wireframe" "1" 
"$flat" "0" 
} 
)#";

	std::ofstream(XorStr("csgo\\materials\\wireframe_ignorez.vmt")) << R"#("VertexLitGeneric" 
{ 
"$basetexture" "vgui/white" 
"$ignorez" "1" 
"$envmap" "" 
"$nofog" "1" 
"$model" "1" 
"$nocull" "0" 
"$selfillum" "1" 
"$halflambert" "1" 
"$znearer" "0" 
"$wireframe" "1" 
"$flat" "0" 
} 
)#";

	std::ofstream(XorStr("csgo\\materials\\metallic.vmt")) << R"#("VertexLitGeneric"
{ 
"$basetexture" "vgui/white_additive"
"$ignorez"      "0"
"$envmap"       "env_cubemap"
"$normalmapalphaenvmapmask"  "1"
"$envmapcontrast"             "1"
"$nofog"        "1"
"$model"        "1"
"$nocull"       "0"
"$selfillum"    "1"
"$halflambert"  "1"
"$znearer"      "0"
"$flat"         "1"
} 
)#";
	std::ofstream(XorStr("csgo\\materials\\metallic_ignorez.vmt")) << R"#("VertexLitGeneric"
{ 
"$basetexture" "vgui/white_additive"
"$ignorez"      "1"
"$envmap"       "env_cubemap"
"$normalmapalphaenvmapmask"  "1"
"$envmapcontrast"             "1"
"$nofog"        "1"
"$model"        "1"
"$nocull"       "0"
"$selfillum"    "1"
"$halflambert"  "1"
"$znearer"      "0"
"$flat"         "1"
} 
)#";

	Materials::material_flat = I::MaterialSystem()->FindMaterial("flat", TEXTURE_GROUP_MODEL);
	Materials::material_flat_ignorez = I::MaterialSystem()->FindMaterial("flat_ignorez", TEXTURE_GROUP_MODEL);

	Materials::material_texture = I::MaterialSystem()->FindMaterial("textured", TEXTURE_GROUP_MODEL);
	Materials::material_texture_ignorez = I::MaterialSystem()->FindMaterial("textured_ignorez", TEXTURE_GROUP_MODEL);

	Materials::material_wireframe = I::MaterialSystem()->FindMaterial("wireframe", TEXTURE_GROUP_MODEL);
	Materials::material_wireframe_ignorez = I::MaterialSystem()->FindMaterial("wireframe_ignorez", TEXTURE_GROUP_MODEL);

	Materials::material_metallic_plus = I::MaterialSystem()->FindMaterial("metallic_plus", TEXTURE_GROUP_MODEL);
	Materials::material_metallic_plus_ignorez = I::MaterialSystem()->FindMaterial("metallic_plus_ignorez", TEXTURE_GROUP_MODEL);

	Materials::material_metallic = I::MaterialSystem()->FindMaterial("metallic", TEXTURE_GROUP_MODEL);
	Materials::material_metallic_ignorez = I::MaterialSystem()->FindMaterial("metallic_ignorez", TEXTURE_GROUP_MODEL);

	Materials::material_animated = I::MaterialSystem()->FindMaterial("chamsAnimated", TEXTURE_GROUP_MODEL);
	Materials::material_glowoverlay = I::MaterialSystem()->FindMaterial("glowOverlay", TEXTURE_GROUP_MODEL);

	Materials::material_bubble = I::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_MODEL);
	Materials::material_dogtag = I::MaterialSystem()->FindMaterial("models\\inventory_items\\dogtags\\dogtags_outline", TEXTURE_GROUP_OTHER);
}

void Materials::DeleteMaterials()
{
	std::remove(XorStr("csgo\\materials\\textured.vmt"));
	std::remove(XorStr("csgo\\materials\\textured_ignorez.vmt"));
	std::remove(XorStr("csgo\\materials\\flat.vmt"));
	std::remove(XorStr("csgo\\materials\\flat_ignorez.vmt"));
	std::remove(XorStr("csgo\\materials\\wireframe.vmt"));
	std::remove(XorStr("csgo\\materials\\wireframe_ignorez.vmt"));
	std::remove(XorStr("csgo\\materials\\metallic_plus.vmt"));
	std::remove(XorStr("csgo\\materials\\metallic_plus_ignorez.vmt"));
	std::remove(XorStr("csgo\\materials\\metallic.vmt"));
	std::remove(XorStr("csgo\\materials\\metallic_ignorez.vmt"));
	std::remove(XorStr("csgo\\materials\\chamsAnimated.vmt"));
	std::remove(XorStr("csgo\\materials\\glowOverlay.vmt"));
}