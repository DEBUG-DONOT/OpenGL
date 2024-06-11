#pragma once


class Application
{
public:
	Application() = default;
	virtual ~Application();
	void tick();//让整个程序跑起来
	bool AppInitialization();
private:
	void LogicTick();
	void RenderTick();

};