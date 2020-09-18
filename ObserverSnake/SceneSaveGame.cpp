#include "SceneSaveGame.h"
#include <fstream>
#include <filesystem>
#include"SceneGame.h"

SceneSaveGame::SceneSaveGame(SceneStateMachine& sceneStateMachine)
	: Scene(), _sceneStateMachine(sceneStateMachine), _currentGameScene(0){}

void SceneSaveGame::SetSaveGameScene(std::shared_ptr<Scene>& prev)
{
	_currentGameScene = std::dynamic_pointer_cast<SceneGame>(prev);
}

void SceneSaveGame::SetSwitchToScene(std::unordered_map<std::string, std::shared_ptr<Scene>> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void SceneSaveGame::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void SceneSaveGame::OnCreate()
{}

// Source: https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
bool is_file_exist(const std::wstring fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void SceneSaveGame::OnActivate() 
{
	auto path = std::filesystem::current_path();
	auto savegamePath = path;
	savegamePath += "\\savegames";

	std::filesystem::create_directory(savegamePath);

	//gotoXY(0, 0);
	//TextColor(ColorCode_Cyan);
	//for (const auto& entry : std::filesystem::directory_iterator(savegamePath))
	//	std::cout << entry.path() << std::endl; 
	
	unsigned int n = 0;

	std::wstring fileName{ savegamePath.c_str() };
	fileName += L"\\savegame";

	while (is_file_exist(fileName + std::to_wstring(n) + L".txt")) {
		n++;
	}
	
	std::wstring output = fileName + std::to_wstring(n) + L".txt";
	std::ofstream writer(output, std::ios::out);

	writer << _currentGameScene->getMapPath() << std::endl;
	writer << _currentGameScene->getFruit()->getX() << " " << _currentGameScene->getFruit()->getY() << std::endl;

	for (auto i : _currentGameScene->getSnake()->segments)
	{
		writer << i->getX() << " " << i->getY() << std::endl;
	}
	writer.close();

	gotoXY(30,10);
	TextColor(ColorCode_Cyan);
	std::wcout << L"Successfully save game to " << output << std::endl;

	Sleep(3000);
	system("cls");

	SwitchTo("ContinueScene"); 
}

void SceneSaveGame::OnDestroy()
{}
