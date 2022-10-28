#pragma once

enum DotaUnitOrder_t
{
	DOTA_UNIT_ORDER_NONE = 0,
	DOTA_UNIT_ORDER_MOVE_TO_POSITION = 1,
	DOTA_UNIT_ORDER_MOVE_TO_TARGET = 2,
	DOTA_UNIT_ORDER_ATTACK_MOVE = 3,
	DOTA_UNIT_ORDER_ATTACK_TARGET = 4,
	DOTA_UNIT_ORDER_CAST_POSITION = 5,
	DOTA_UNIT_ORDER_CAST_TARGET = 6,
	DOTA_UNIT_ORDER_CAST_TARGET_TREE = 7,
	DOTA_UNIT_ORDER_CAST_NO_TARGET = 8,
	DOTA_UNIT_ORDER_CAST_TOGGLE = 9,
	DOTA_UNIT_ORDER_HOLD_POSITION = 10,
	DOTA_UNIT_ORDER_TRAIN_ABILITY = 11,
	DOTA_UNIT_ORDER_DROP_ITEM = 12,
	DOTA_UNIT_ORDER_GIVE_ITEM = 13,
	DOTA_UNIT_ORDER_PICKUP_ITEM = 14,
	DOTA_UNIT_ORDER_PICKUP_RUNE = 15,
	DOTA_UNIT_ORDER_PURCHASE_ITEM = 16,
	DOTA_UNIT_ORDER_SELL_ITEM = 17,
	DOTA_UNIT_ORDER_DISASSEMBLE_ITEM = 18,
	DOTA_UNIT_ORDER_MOVE_ITEM = 19,
	DOTA_UNIT_ORDER_CAST_TOGGLE_AUTO = 20,
	DOTA_UNIT_ORDER_STOP = 21,
	DOTA_UNIT_ORDER_TAUNT = 22,
	DOTA_UNIT_ORDER_BUYBACK = 23,
	DOTA_UNIT_ORDER_GLYPH = 24,
	DOTA_UNIT_ORDER_EJECT_ITEM_FROM_STASH = 25,
	DOTA_UNIT_ORDER_CAST_RUNE = 26,
	DOTA_UNIT_ORDER_PING_ABILITY = 27,
	DOTA_UNIT_ORDER_MOVE_TO_DIRECTION = 28,
	DOTA_UNIT_ORDER_PATROL = 29,
	DOTA_UNIT_ORDER_VECTOR_TARGET_POSITION = 30,
	DOTA_UNIT_ORDER_RADAR = 31,
	DOTA_UNIT_ORDER_SET_ITEM_COMBINE_LOCK = 32,
	DOTA_UNIT_ORDER_CONTINUE = 33,
	DOTA_UNIT_ORDER_VECTOR_TARGET_CANCELED = 34,
	DOTA_UNIT_ORDER_CAST_RIVER_PAINT = 35,
	DOTA_UNIT_ORDER_PREGAME_ADJUST_ITEM_ASSIGNMENT = 36,
	DOTA_UNIT_ORDER_DROP_ITEM_AT_FOUNTAIN = 37,
	DOTA_UNIT_ORDER_TAKE_ITEM_FROM_NEUTRAL_ITEM_STASH = 38,
};

enum PlayerOrderIssuer_t
{
	DOTA_ORDER_ISSUER_SELECTED_UNITS = 0,
	DOTA_ORDER_ISSUER_CURRENT_UNIT_ONLY = 1,
	DOTA_ORDER_ISSUER_HERO_ONLY = 2,
	DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY = 3
};

enum OrderQueueBehavior_t
{
	DOTA_ORDER_QUEUE_DEFAULT = 0,
	DOTA_ORDER_QUEUE_NEVER = 1,
	DOTA_ORDER_QUEUE_ALWAYS = 2,
};

class C_DotaPlayer : public C_BaseEntity
{
public:
	inline C_DOTA_BaseNPC_Hero* GetAssignedHero()
	{
		return static_cast<C_DOTA_BaseNPC_Hero*>(I::EntitySystem->GetBaseEntityFromHandle(
			*reinterpret_cast<unsigned long*>(reinterpret_cast<uintptr_t>(this) + Schema::m_hAssignedHero)));
	}

	inline void PrepareUnitOrders(DotaUnitOrder_t OrderType, int TargetIndex, vec3 Position, int AbilityIndex, 
		PlayerOrderIssuer_t OrderIssuer = DOTA_ORDER_ISSUER_SELECTED_UNITS, C_DOTA_BaseNPC* Unit = nullptr, 
		OrderQueueBehavior_t QueueBehavior = DOTA_ORDER_QUEUE_DEFAULT, bool ShowEffects = true)
	{
		typedef void(__thiscall* Fn)(C_DotaPlayer*, DotaUnitOrder_t, int, vec3, int, PlayerOrderIssuer_t, C_DOTA_BaseNPC*, OrderQueueBehavior_t, bool);
		reinterpret_cast<Fn>(Signatures::C_DotaPlayer__PrepareUnitOrders)(this, OrderType, TargetIndex, Position, AbilityIndex, OrderIssuer, Unit, QueueBehavior, ShowEffects);
	}
};