#pragma once


class Application
{
public:
	Application() = default;
	virtual ~Application();
	void tick();//����������������
	bool AppInitialization();
private:
	void LogicTick();
	void RenderTick();

};