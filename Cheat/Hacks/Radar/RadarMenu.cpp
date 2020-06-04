#include "Radar.h"
#include"../../GUI/Gui.h"

void CRadar::Menu()
{

	VectorEx<const char*> RadTraceStyleItem = { lolc("Line"), lolc("FOV"),lolc("FOV + Line") };
	VectorEx<const char*> PointStyleItem = { lolc("Filled box"), lolc("Box"), lolc("Filled circle"), lolc("Circle"), lolc("None") };

	X1Gui().PushItemWidth(360);

	DCheckBox("InGame Radar", RadarInGame);
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	DCheckBox("Drawn radar", RadarActive);
	if (RadarActive)
	{
		X1Gui().SameLine();
		DCheckBox("With map", TexturedRadar);
	}
	X1Gui().Spacing();
	X1Gui().Separator();
	X1Gui().Spacing();
	if (RadarActive)
	{
		DCheckBox("Enemy", Enemy);

		X1Gui().SameLine();
		DCheckBox("Team", Team);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		DColorEdit("CT color", ColorCT);
		X1Gui().SameLine();
		DColorEdit("Visible CT color", ColorVisbleCT);


		DColorEdit("T color", ColorTT);
		X1Gui().SameLine();
		DColorEdit("Visible T color", ColorVisbleTT);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();
		SliderInts("Zoom", Range, 1, 4000);
		X1Gui().Spacing();

		SliderInts("Position X", RadarPosX, 1, CGlobal::iScreenWidth);
		SliderInts("Position Y", RadarPosY, 1, CGlobal::iScreenHeight);


		X1Gui().Spacing();

		SliderInts("Size X", RadarSizeX, 1, 900);
		SliderInts("Size Y", RadarSizeY, 1, 900);


		X1Gui().Spacing();

		SliderInts("Alpha", Alpha, 1, 255);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		DCheckBox("Fov", Fov);

		X1Gui().SameLine();
		DCheckBox("Line", Line);
		X1Gui().SameLine();
		DCheckBox("Outline", OutLine);
		X1Gui().SameLine();
		DCheckBox("Only in radar", OnlyInRadar);
		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		DColorEdit("Background color", ColorBackground);
		DColorEdit("Line color", ColorLine);

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		SliderInts("Size##point", PointSize, 2, 50);
		DComboBox("Style##point", PointStyle, PointStyleItem);

//		X1Gui().Spacing();
//		X1Gui().Separator();
//		X1Gui().Spacing();

/*		DCheckBox("Sound", Sound);
		if (Sound)
		{
			SliderInts("Size##soud", SoundPointSize, 2, 50);
			DComboBox("Style##soud", SoundPointStyle, PointStyleItem);
			DColorEdit("Color##soud", SoundColor);
		}
*/

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		DCheckBox("Trace", Trace);

		if (Trace)
		{
			SliderInts("Lenght##trace", TraceLenght, 2, 300);
			DComboBox("Style##trace", TraceStyle, RadTraceStyleItem);
		}

		X1Gui().Spacing();
		X1Gui().Separator();
		X1Gui().Spacing();

		DCheckBox("Name", Name);
		if (Name)
		{
			SliderInts("Text size##name", TextNameSize, 9, MAX_FONT_SIZE);

			DColorEdit("Color##name", NameColor);
		}

	}
}