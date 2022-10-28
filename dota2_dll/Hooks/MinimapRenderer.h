#pragma once

namespace Hooks
{
	extern CVTH* hkMinimapRenderer;

	typedef void(__thiscall* MinimapRendrererDestructorFn)(void*, bool);
	MinimapRendrererDestructorFn oMinimapRendererDestructor;

	void MinimapRendererDestructor(void* _this, bool a2)
	{
		delete hkMinimapRenderer;
		hkMinimapRenderer = nullptr;
		oMinimapRendererDestructor(_this, a2);
	}

	typedef void(__thiscall* MinimapRendererPaintFn)(void*, void*, void*, void*, float, float, float, float);
	MinimapRendererPaintFn oMinimapRendererPaint;

	void MinimapRendererPaint(void* _this, void* sceneView, void* renderHelper, void* sceneLayer, float a5, float a6, float a7, float a8)
	{
		//Features::CourierPrediction::Predict();
		oMinimapRendererPaint(_this, sceneView, renderHelper, sceneLayer, a5, a6, a7, a8);
	}
}