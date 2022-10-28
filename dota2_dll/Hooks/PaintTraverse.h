#pragma once

namespace Hooks
{
	typedef void(__thiscall* PaintTraverseFn) (VPanelWrapper*, CVGuiPaintSurfaceMainThread*, ULONGLONG, bool, bool);
	PaintTraverseFn oPaintTraverse;

	void PaintTraverse(VPanelWrapper* _this, CVGuiPaintSurfaceMainThread* paintSurface, ULONGLONG panel, bool forceRepaint, bool allowForce)
	{
		oPaintTraverse(_this, paintSurface, panel, forceRepaint, allowForce);

		static ULONGLONG topPanel = 0;

		if (!topPanel)
		{
			if (!strcmp(_this->GetName(panel), "RenderSystemTopPanel"))
				topPanel = panel;
		}
		else if (topPanel == panel)
		{
			Features::CourierPrediction::Predict();
			Features::ParticleMaphack::Draw();

			paintSurface->PushMakeCurrent(panel, false);
			Features::Visuals::Paint(paintSurface);
			paintSurface->PopMakeCurrent(panel);

			static bool menuPressed = false;
			if (I::InputSystem->IsButtonDown(KEY_INSERT))
			{
				if (!menuPressed)
				{
					menuPressed = true;
					if (!Menu::IsValid())
						Menu::Show();
					else
						Menu::Close();
				}
			}
			else if (menuPressed)
				menuPressed = false;
		}
	}
}