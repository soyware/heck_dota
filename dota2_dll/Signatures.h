#pragma once

inline uintptr_t RelativeToDirect(const uintptr_t address, const uint8_t nextInstOfs = 4)
{
	return address + *reinterpret_cast<int32_t*>(address) + nextInstOfs;
}

namespace Signatures
{
	// Credits: Forza
	void FindLongestSegment(const char* Mask, size_t Out[2])
	{
		size_t start = 0,
			len = 0,
			maskLen = strlen(Mask);

		for (size_t i = len; i < maskLen; ++i)
		{
			if (Mask[i] != 'x')
				continue;

			size_t count = 0;
			for (size_t j = i; j < maskLen && Mask[j] == 'x'; ++j)
				++count;

			if (count > len)
			{
				start = i;
				len = count;
			}

			i += (count - 1);
		}

		Out[0] = start;
		Out[1] = len;
	}

	uintptr_t Find(const char* Module, const char* Signature, const char* Mask, const ptrdiff_t Offset = 0)
	{
		MODULEINFO modInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(Module), &modInfo, sizeof(MODULEINFO));

		size_t longest[2];
		FindLongestSegment(Mask, longest);

		const uint8_t* data = static_cast<uint8_t*>(modInfo.lpBaseOfDll);

		const uint8_t maskLen = static_cast<uint8_t>(strlen(Mask)),
			segStart = static_cast<uint8_t>(longest[0]),
			segLen = static_cast<uint8_t>(longest[1]),
			firstChar = static_cast<uint8_t>(Signature[segStart]);

		bool inPattern[UCHAR_MAX + 1] = { false };

		for (uint8_t i = segStart; i < (segStart + segLen); ++i)
			inPattern[(uint8_t)Signature[i]] = true;

		for (size_t i = modInfo.SizeOfImage - maskLen; i > 0; --i)
		{
			bool in = inPattern[data[i]];
			while (!in && i > segLen)
			{
				i -= segLen;
				in = inPattern[data[i]];
			}

			if (data[i] != firstChar)
				continue;

			if ((segStart > i) || (i - segStart + maskLen > modInfo.SizeOfImage))
				break;

			for (uint8_t j = 0; j < maskLen; ++j)
			{
				if (j == segStart || Mask[j] != 'x')
					continue;

				if (data[i - segStart + j] != (uint8_t)Signature[j])
					break;

				if (j + 1 == maskLen)
					return Offset ? *(uintptr_t*)(data + i - segStart + Offset) : (uintptr_t)(data + i - segStart);
			}
		}

		FatalError("Signature not found");
		return 0;
	}

	uintptr_t //Input,
		//bOverlayOpen,
		//g_pDOTAChat,
		//MessageMode,
		GetVectorInScreenSpace,
		C_DotaPlayer__PrepareUnitOrders,
		CDOTA_ModifierManager__AddNewModifier,
		pParticleManager,
		CDOTA_Buff__AddParticle,
		C_DOTA_BaseNPC__UpdateSelectionRing__sv_cheats_ReturnAddress,
		CDOTA_UI_Popup_Constructor,
		CUI_PopupManager__ShowPopup,
		GetTopmostPopupManager,
		/*CUIEvent0VT,
		RegisterUIEvent,*/
		CDOTARichPresence__SetRPStatus,
		s_RichPresence,
		CDOTA_DB_PopupSettings__CheckChildrenForSettingsConVars,
		CDOTA_MinimapObjectManager__AddNewObject,
		g_HudIcons,
		CTextEntry__SetText;

	void Init()
	{
		// "input_forceuser"
		//Input = RIPtoDirect(Find("client.dll", "\x48\x83\xEC\x60\x48\x83\x3D\x00\x00\x00\x00\x00\x48\x8D\x1D", "xxxxxxx????xxxx"), 15);
		// "Detected hot-key via dinput7 (buffered)" , outdated signature
		//bOverlayOpen = RelativeToDirect(Find("gameoverlayrenderer64.dll", "\x84\xC0\x74\x67\x80\x3D\x00\x00\x00\x00\x00\x48\x8D\x05", "xxxxxx????xxxx") + 6, 5);
		//g_pDOTAChat = RIPtoDirect(Find("client.dll", "\x48\x83\xEC\x28\x48\x8B\x05\x00\x00\x00\x00\x48\x85\xC0\x75\x3C", "xxxxxxx????xxxxx"), 7);
		//MessageMode = (uint32_t)Find("client.dll", "\x48\x89\x74\x24\x30\x48\x8D\x0D\x00\x00\x00\x00\x89\xBB", "xxxxxxxx????xx", 14);
		// "Total Dmg: %.2f", second call in xref'd function, above "test    al, al"
		GetVectorInScreenSpace = Find("client.dll", "\x40\x56\x41\x56\x48\x83\xEC\x68\x48\x89\x9C\x24\x80\x00\x00\x00\x49\x8B\xF0", "xxxxxxxxxxxxxxxxxxx");
		// "particles/ui_mouseactions/waypoint_flag.vpcf", biggest offset, or "courier_go_to_secretshop", biggest offset, last call
		C_DotaPlayer__PrepareUnitOrders = Find("client.dll", "\x4C\x89\x4C\x24\x20\x44\x89\x44\x24\x18\x89\x54\x24\x10\x48\x89\x4C\x24\x08", "xxxxxxxxxxxxxxxxxxx");
		// "isProvidedByAura", smallest offset
		CDOTA_ModifierManager__AddNewModifier = Find("client.dll", "\x4C\x89\x44\x24\x18\x48\x89\x54\x24\x10\x53\x55\x56\x41\x54\x41\x55", "xxxxxxxxxxxxxxxxx");
		// "UTIL_ReadEncryptedKVFile(%s)" , replaced by import
		//LoadFromBuffer = Find("client.dll", "\x48\x89\x6C\x24\x18\x56\x41\x56\x41\x57\x48\x81\xEC\x80\x00\x00\x00\x49", "xxxxxxxxxxxxxxxxxx");
		// "BroadcasterFacts" , replaced by import
		//KeyValues_Constructor = Find("client.dll", "\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x20\x57\x48\x83\xEC\x30\x8B\x41\x08", "xxxxxxxxxxxxxxxxxx");
		// "particles/units/heroes/hero_jakiro/jakiro_icepath_debuff.vpcf", above
		pParticleManager = RelativeToDirect(Find("client.dll", "\x74\x0B\x44\x39\x48\x10\x75\x05\x48\x8B\x10\xEB\x02\x33\xD2\x48\x8B\x0D", "xxxxxxxxxxxxxxxxxx") + 18);
		// "particles/units/heroes/hero_jakiro/jakiro_icepath_debuff.vpcf", call at the end
		CDOTA_Buff__AddParticle = Find("client.dll", "\x40\x57\x48\x83\xEC\x30\x48\x63\x81\x98\x00\x00\x00\x48\x8B\xF9\x85\xC0", "xxxxxxxxxxxxxxxxxx");
		// "particles/ui_mouseactions/hero_highlighter.vpcf", under ConVarRef::ConVarRef("sv_cheats") call
		C_DOTA_BaseNPC__UpdateSelectionRing__sv_cheats_ReturnAddress = Find("client.dll", "\x4C\x8B\x0D\x00\x00\x00\x00\x8B\xCB\x45\x85\xC9\x7E\x63\x4C\x8B\x1D", "xxx????xxxxxxxxxx");
		// "PickerButtonOK", first call
		CDOTA_UI_Popup_Constructor = Find("client.dll", "\x48\x89\x5C\x24\x10\x57\x48\x83\xEC\x40\x49\x8B\xF9\x48\x8B\xD9\xE8", "xxxxxxxxxxxxxxxxx");
		// "onpopupdisplayed", "HaveActivePopups"
		CUI_PopupManager__ShowPopup = Find("client.dll", "\x48\x89\x5C\x24\x18\x48\x89\x6C\x24\x20\x56\x57\x41\x54\x41\x56\x41\x57\x48\x83\xEC\x20\x65", "xxxxxxxxxxxxxxxxxxxxxxx");
		// "RootHidden", smallest offset
		GetTopmostPopupManager = Find("client.dll", "\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x20\x8B\x05\x00\x00\x00\x00\x8D\x68\xFF", "xxxxxxxxxxxx????xxx") - 10;
		//CUIEvent0VT = RIPtoDirect(Find("client.dll", "\x01\x49\x89\x06\x49\x8B\xC6\x48\x83\xC4\x20\x41\x5E\x5E\x5B", "xxxxxxxxxxxxxxx") - 3);
		//RegisterUIEvent = Find("client.dll", "\x48\x83\xEC\x68\x48\x8B\x84\x24\xA8\x00\x00\x00\x44\x89", "xxxxxxxxxxxxxx");
		// "Setting %s's status to %s.\n"
		CDOTARichPresence__SetRPStatus = Find("client.dll", "\x48\x89\x5C\x24\x18\x48\x89\x6C\x24\x20\x56\x41\x54\x41\x57\x48\x81\xEC", "xxxxxxxxxxxxxxxxxx");
		// "friend_picker_%d", near "mov     r9d, 4" and "mov     dword ptr [rsp+1A8h+arg_0], 0FFFFFFFFh"
		s_RichPresence = RelativeToDirect(Find("client.dll", "\x41\xB9\x04\x00\x00\x00\x45\x8B\xC7\x48\x8B\x01\xFF\x50\x20\x48\x8D\x0D", "xxxxxxxxxxxxxxxxxx") + 18);
		// "input_button_code_is_scan_code", biggest offset, jump near the end ("cmp     edx, 5")
		CDOTA_DB_PopupSettings__CheckChildrenForSettingsConVars = Find("client.dll", "\x40\x55\x56\x41\x56\x48\x83\xEC\x40\x4C\x8B\xF1\x48\x8B\xEA\x48\x8B\x4A\x08", "xxxxxxxxxxxxxxxxxxx");
		// "General.Write", biggest offset, second to last call, below "mov     r9b, 1"
		CDOTA_MinimapObjectManager__AddNewObject = Find("client.dll", "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x41\x8B\xF8\x8B\xDA\x81\xFA", "xxxxxxxxxxxxxxxxx");
		// "CHud::HudIcons(Init)", under
		g_HudIcons = RelativeToDirect(Find("client.dll", "\x48\x83\xC7\x20\x3B\xD8\x7C\xA6\x48\x8D\x0D\x00\x00\x00\x00\xFF\x15\x00\x00\x00\x00\x48\x8D\x0D", "xxxxxxxxxxx????xx????xxx") + 24);
		// "oninputsubmit", smellest offset, above
		CTextEntry__SetText = Find("client.dll", "\x48\x89\x7C\x24\x20\x41\x56\x48\x83\xEC\x40\x48\x8B\xE9\x48\x8B\xDA", "xxxxxxxxxxxxxxxxx");
	}
}