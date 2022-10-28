#pragma once

namespace Hooks
{
	extern CVTH hkMinigame;

	DestructorFn oMinigameDestructor;

	void MinigameDestructor(CPanel2D* _this, bool del)
	{
		hkMinigame.Unhook();

		oMinigameDestructor(_this, del);
	}

	typedef void(__thiscall* MinigameFn)(CPanel2D*, void*);
	MinigameFn oMinigame;

	CUtlDelegate<bool(int, CPanel2D*)> MinigameChooseFunc;

	void Minigame(CPanel2D* _this, void* msg)
	{
		oMinigame(_this, msg);

		void* unk1 = *(void**)((char*)msg + 40);

		void* iter = unk1 ? (char*)unk1 + 8 : nullptr;
		void* unk2 = iter;

		int heroIDs[3] = { 0 };
		int heroIDcount = 0;

		for (void* end = (char*)unk2 + (*(int*)((char*)msg + 32) * 8);
			iter != end; 
			iter = (char*)iter + 8)
		{
			void* unk3 = *(void**)iter;

			int msgID = *(int*)((char*)unk3 + 24);
			if (msgID == 0x192) // meepo
			{
				int meepoNum = *(int*)((char*)unk3 + 28) + 1;
				MinigameChooseFunc(meepoNum, _this);
			}
			else if (msgID == 0x1F5) // find
			{
				assert(heroIDcount < 3);
				int heroID = *(int*)((char*)unk3 + 28);
				heroIDs[heroIDcount] = heroID;
				++heroIDcount;
			}
			else if (msgID == 0x1F6)
			{
				int heroID = *(int*)((char*)unk3 + 28);
				int chooseNum = *(int*)((char*)unk3 + 32) + 1;

				for (int i = 0; i < heroIDcount; ++i)
				{
					if (heroIDs[i] == heroID)
					{
						MinigameChooseFunc(chooseNum, _this);
						break;
					}
				}
			}
			else if (msgID == 0xC9) // chairs
				MinigameChooseFunc(1, _this);
		}
	}
}