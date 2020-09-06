#pragma once
#include "../Json/Json.hpp"
#include "../Main.h"

template<typename T>
class Singleton__
{
protected:
	Singleton__() {}
	~Singleton__() {}

	Singleton__(const Singleton__&) = delete;
	Singleton__& operator=(const Singleton__&) = delete;

	Singleton__(Singleton__&&) = delete;
	Singleton__& operator=(Singleton__&&) = delete;

public:
	static T& Get()
	{
		static T inst{};
		return inst;
	}

	static T& G()
	{
		static T inst{};
		return inst;
	}
};

class IConfig
{
protected:
	virtual void UpdateColors() = 0;
	virtual void Save(nlohmann::json &j) = 0;
	virtual void Load(nlohmann::json j) = 0;
};

#define RV(a,b) Config.RegVar(a, XorStr(b));

class CConfig : public IConfig
{
private:
	template<typename TV>
	struct InstVar
	{
		string Key = "";
		TV     &Var;
		InstVar(TV &_Var, const string _Key) : Var(_Var)
		{
			Key = _Key;
		}
	};

	vector<InstVar<bool>>	VecBool;
	vector<InstVar<int>>	VecInt;
	vector<InstVar<float>>	VecFloat;
	vector<InstVar<double>> VecDouble;
	vector<InstVar<string>> VecString;
	vector<InstVar<Color>>	VecColor;
	vector<InstVar<CBind>>	VecBind;

	string SectionName = "";
public:
	CConfig(const string Name)
	{
		SectionName = Name;
	}

	~CConfig()
	{
		VecBool.clear();
		VecInt.clear();
		VecFloat.clear();
		VecDouble.clear();
		VecString.clear();
		VecBind.clear();
		SectionName = "";
	}

	template<typename TVar>
	void RegVar(TVar &Var, const string Key) {}

	template<> void RegVar<bool>(bool &Var, const string Key) {
		VecBool.push_back(InstVar<bool>(Var, Key));
	}

	template<> void RegVar<int>(int &Var, const string Key) {
		VecInt.push_back(InstVar<int>(Var, Key));
	}

	template<> void RegVar<float>(float &Var, const string Key) {
		VecFloat.push_back(InstVar<float>(Var, Key));
	}

	template<> void RegVar<double>(double &Var, const string Key) {
		VecDouble.push_back(InstVar<double>(Var, Key));
	}

	template<> void RegVar<string>(string &Var, const string Key) {
		VecString.push_back(InstVar<string>(Var, Key));
	}

	template<> void RegVar<Color>(Color &Var, const string Key) {
		VecColor.push_back(InstVar<Color>(Var, Key));
	}

	template<> void RegVar<CBind>(CBind &Var, const string Key) {
		VecBind.push_back(InstVar<CBind>(Var, Key));
	}

	virtual void UpdateColors();
	virtual void Save(nlohmann::json &j);
	virtual void Load(nlohmann::json j);
};

class CGSettings : public Singleton__<CGSettings>
{
private:
	string config_name;

	struct CfgInfo_s
	{
		string name;
		string id;
		bool pc_cloud;
	};

	vector<CfgInfo_s> AllSettings;
public:
	void SetName(const string _name);
	void SaveEx(nlohmann::json &j);
	void LoadEx(nlohmann::json &j);
	bool Save(string name);
	bool Load();
	void UpdateColors();
	void Menu();
	void UpdateList();

	string readFile(const string& fileName);
	void CopyFile__(const std::string& filename_in, const std::string& filename_out)
	{
		string bf = readFile(filename_out);
		ofstream fl(filename_in);
		fl << bf;
		fl.close();
	}
};

class IMain
{
protected:
	virtual void SetMenuColors() = 0;
};

class CMain : IMain
{
public:
	CConfig Config = CConfig(XorStr("MainCheatConfig"));

	virtual void SetMenuColors();

	int MenuButton = VK_INSERT;
	string HintMsg = "";

	Color BackgroundColor = Color(18, 18, 22, 255);
	Color TitleColor = Color(112, 112, 116, 255);
	Color TextColor = Color(255, 255, 255, 255);
	Color FrameColor = Color(34, 35, 37, 255);
	Color ButtonColor = Color(128, 135, 140, 255);
	Color DisableButtonColor = Color(225, 20, 20, 255);
	Color LineColor = Color(120, 121, 123, 255);

	CMain()
	{
		RV(MenuButton, "MenuButton");
		RV(BackgroundColor, "BackgroundColor");
		RV(TitleColor, "TitleColor");
		RV(TextColor, "TextColor");
		RV(FrameColor, "FrameColor");
		RV(ButtonColor, "ButtonColor");
		RV(DisableButtonColor, "DisableButtonColor");
		RV(LineColor, "LineColor");
	}
};