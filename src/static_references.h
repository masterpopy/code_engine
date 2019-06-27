#ifndef static_references
#define static_references

//locations in other C files
extern const struct move_info move_table[1024];

//move tables
extern const u16 sound_moves[];
extern const u16 powder_moves[];
extern const u16 ball_bomb_moves[];
extern const u16 reckless_moves_table[];
extern const u16 ironfist_moves_table[];
extern const u16 sheerforce_moves_table[];
extern const u16 biting_moves_table[];
extern const u16 megalauncher_moves_table[];
extern const u16 moveshitting_onair[];
extern const u16 moveshitting_underground[];
extern const u16 moveshitting_underwater[];
extern const u16 dual_type_moves[];
extern const u16 user_thawing_moves[];
extern const u16 ignore_targetstats_moves[];
extern const u16 always_crit_hits[];
extern const u16 dancing_moves[];
extern const u16 instruct_banlist[];
extern const u16 moves_with_charging_turn[];
extern const u16 moves_calling_another_move[];
extern const u16 pressing_moves_table[];

extern const u8 type_effectiveness_table[TYPE_FAIRY-0x4][TYPE_FAIRY-0x4];

extern void* fogcontinues_bs;
extern void* fogends_bs;
extern void* fog_animation;
extern void* stickybarbswap;
extern void* frisk_bs();
extern void* bad_dreams_bs();
extern void* CANCELER_FAIL();
extern void* defogblows_bs;

extern void* aegislash_change_bs;
extern void* zen_change_bs;
extern void* combined_move_bs;
extern void* fire_sea_bs;
extern void* swamp_bs;
extern void* rainbow_bs;
extern void* end_pledge_effect_bs;
extern void* sea_of_fire_hurt_bs;

extern void* aircurcontinues_bs;
extern void* aircurends_bs;

extern void* capture_exp_bs;

//extern scripts from battlescripts.s file
extern u8 BS_TELEKINESIS_ENDS_RET[];
extern u8 BS_TELEKINESIS_ENDS_2[];
extern u8 BS_BALL_BLOCK[];
extern u8 BS_CUSTOM_LOSS[];
extern u8 BS_TRAINER_SLIDE_MSG_RETURN[];
extern u8 BS_TRAINER_SLIDE_MSG_END2[];
extern u8 BS_PRINT_SPORT_FADED[];
extern u8 FRISK_BS[];
extern u8 BAD_DREAMS_BS[];
extern u8 BS_INTIMIDATE[];
extern u8 BS_MEGA_EVO[];
extern u8 BS_LIGHT_UP[];
extern u8 BS_FERVENT_EVO[];
extern u8 BS_ALPHA_PRIMAL[];
extern u8 BS_OMEGA_PRIMAL[];

extern u8 BS_DEF_ABILITY_STATUS[];
extern u8 BS_ATK_ABILITY_STATUS[];

extern u8 BS_DEF_ABILITY_CHANGES_ATK_STAT[];
extern u8 BS_DEF_ABILITY_CHANGES_DEF_STAT[];
extern u8 BS_ATK_ABILITY_CHANGES_ATK_STAT[];
extern u8 BS_ATK_ABILITY_CHANGES_ATK_STAT_END3[];

extern u8 BS_CHANGE_ATK_STAT[];
extern u8 BS_CHANGE_ATK_STAT_SELFINFLICTED[];
extern u8 BS_CHANGE_DEF_STAT_SELFINFLICTED[];
extern u8 BS_CHANGE_DEF_STAT[];
extern u8 ONE_STAT_TARGET_STATANIM[];
extern u8 ONE_STAT_USER_STATANIM[];
extern u8 ONE_STAT_PRINT[];
extern u8 BS_WEAK_ARMOR[];
extern u8 BS_MULTIPLESTATCHANCE_ATK_CERTAIN[];
extern u8 BS_MULTIPLESTATCHANCE_ATK[];

extern u8 BS_ELECTRIC_SURGE[];
extern u8 BS_MISTY_SURGE[];
extern u8 BS_GRASSY_SURGE[];
extern u8 BS_PSYCHIC_SURGE[];

extern u8 BS_CANTUSE_PRIORITY[];
extern u8 BS_CANTUSE_PRIORITY_TERRAIN[];
extern u8 BS_GOT_STATUS[];
extern u8 CANT_CONFUSE_DUETOABILITY_PRINT[];
extern u8 CANT_CONFUSE_DUETOABILITY_PRINT_END2[];

extern u8 BS_MOODY[];
extern u8 BS_CURSEDBODY[];
extern u8 BS_MUMMY[];
extern u8 BS_ROUGHSKIN[];
extern u8 BS_ANGERPOINT[];
extern u8 BS_AFTERMATH[];
extern u8 BS_CUTECHARM[];
extern u8 BS_DOWNLOAD[];
extern u8 BS_FOREWARN[];
extern u8 BS_ANTICIPATION[];
extern u8 BS_PROTEAN[];
extern u8 BS_ABILITYHPCHANGE_END2[];
extern u8 BS_ABILITYHPCHANGE_END3[];
extern u8 BS_HARVEST[];
extern u8 BS_DEFIANT[];
extern u8 BS_COMPETITIVE[];
extern u8 BS_RECEIVER[];
extern u8 BS_SNOWWARNING[];
extern u8 BS_DESOLATELAND[];
extern u8 BS_PRIMORDIALSEA[];
extern u8 BS_DELTASTREAM[];
extern u8 BS_PICKUP[];
extern u8 BS_PRESSURE[];
extern u8 BS_CHEEKPOUCH[];
extern u8 BS_PICKPOCKET[];
extern u8 BS_DARKAURA[];
extern u8 BS_FAIRYAURA[];
extern u8 BS_AURABREAK[];
extern u8 BS_MOLDBREAKER[];
extern u8 BS_UNNERVE[];
extern u8 BS_TELEPATHY[];
extern u8 BS_SYMBIOSIS[];
extern u8 BS_TRACE[];
extern u8 BS_IMPOSTER[];
extern u8 BS_ILLUSION_OFF[];
extern u8 BS_ILLUSION_OFF2[];
extern u8 BS_SLOWSTART_MSG1[];
extern u8 BS_IMMUNESTATRAISE_ABILITY[];
extern u8 BS_IMMUNE_ABILITY[];
extern u8 BS_HEALER[];

extern u8 BS_HEALBLOCK_PREVENTS[];
extern u8 BS_GRAVITY_PREVENTS[];
extern u8 BS_EMBARGO_PREVENTS[];
extern u8 BS_HEAVYRAIN_PREVENTS[];
extern u8 BS_HARSHSUN_PREVENTS[];
extern u8 BS_AROMAVEIL_PREVENTS[];

extern u8 BS_STURDYENDURES[];
extern u8 BS_ITEMSTATRAISE[];
extern u8 BS_ITEMSTATRAISE_END2[];
extern u8 BS_WEAKNESSPOLICY[];
extern u8 BS_BURNUP[];
extern u8 BS_RAPIDSPIN_SPINS[];
extern u8 BS_LEECHSEED[];

extern u8 BS_BUGBITE_STATRAISE[];
extern u8 BS_BUGBITE[];
extern u8 BS_BUGBITE_HEALCONDITION[];
extern u8 BS_BUGBITE_PERSIMBERRY[];

extern u8 BS_TOXICORB[];
extern u8 BS_FLAMEORB[];
extern u8 BS_LIFEORB[];
extern u8 BS_ROCKYHELMET[];
extern u8 BS_STICKYBARB[];
extern u8 BS_AIRBALLOON_POPS[];
extern u8 BS_AIRBALLOON_SWITCHIN[];
extern u8 BS_POWERHERB[];
extern u8 BS_DESTINYKNOT[];
extern u8 BS_MENTALHERB[];
extern u8 BS_MENTALHERB_END2[];
extern u8 BS_BERRYHPHEAL[];
extern u8 BS_BERRYHPHEAL_REMOVEITEM[];
extern u8 BS_LANSATBERRY[];
extern u8 BS_LANSATBERRY_REMOVEITEM[];
extern u8 BS_LEPPABERRY[];
extern u8 BS_LEPPABERRY_REMOVEITEM[];
extern u8 BS_LEPPABERRY_REMOVEITEM_END2[];
extern u8 BS_HEALCONFUSE_BERRY[];
extern u8 BS_HEALCONFUSE_BERRY_REMOVEITEM[];
extern u8 BS_HEALCONFUSE_BERRY_REMOVEITEM_END2[];
extern u8 BS_GEM_MSG[];
extern u8 BS_BERRY_DMG_REDUCE[];
extern u8 BS_REDCARD_SWITCH[];
extern u8 BS_EJECTBUTTON_SWITCH[];

extern u8 BS_POWDER[];

extern u8 BS_SPIKES[];
extern u8 BS_STEALTHROCK[];
extern u8 BS_STICKYWEB[];
extern u8 BS_TOXICSPIKES[];
extern u8 BS_TOXICSPIKESABSORBED[];
extern u8 BS_LUNARDANCE[];

extern u8 BS_QUICKCLAW[];
extern u8 BS_CUSTAPBERRY[];

extern u8 BS_HEALBLOCKEND[];
extern u8 BS_HEALBLOCKEND_END2[];
extern u8 BS_ROOMEND[];
extern u8 BS_MAGNETRISEEND[];
extern u8 BS_MAGNETRISEEND_END2[];
extern u8 BS_GRAVITYEND[];
extern u8 BS_GRAVITYBRINGSDOWN[];
extern u8 BS_EMBARGOEND[];
extern u8 BS_TAUNTEND[];
extern u8 BS_TAUNTEND_END2[];
extern u8 BS_TORMENTEND[];
extern u8 BS_DISABLEEND[];
extern u8 BS_ENCOREEND[];
extern u8 BS_TERRAINEND[];
extern u8 BS_THROATCHOPEND[];
extern u8 BS_THROATCHOPEND_END2[];

extern u8 BS_AQUARING[];
extern u8 BS_BINDEFFECT[];
extern u8 BS_SMACKDOWN[];
extern u8 BS_FLAMEBURST[];
extern u8 BS_DAMAGETRAP[];
extern u8 BS_SPIKYSHIELD[];
extern u8 BS_CLEARSMOG[];
extern u8 BS_INCINERATEBERRY[];
extern u8 BS_MAGICIAN[];
extern u8 BS_MAGICBOUNCE[];
extern u8 BS_SYNCHRONIZE[];
extern u8 BS_BEAKBLAST[];

extern u8 BS_CANTSELECT_GRAVITY[];
extern u8 BS_CANTSELECT_HEALBLOCK[];
extern u8 BS_CANTSELECT_ASSAULTVEST[];

extern u8 BS_GRASSYTERRAIN_HEAL[];

extern u8 BS_CASTFORMSWITCH_END3[];
extern u8 BS_CHERRIMSWITCH_END3[];
extern u8 BS_CHERRIMSWITCH[];
extern u8 BS_CASTFORMSWITCH[];
extern u8 BS_DROUGHT[];
extern u8 BS_DRIZZLE[];
extern u8 BS_SANDSTREAM[];
extern u8 BS_AIRLOCK[];
extern u8 BS_WIMPOUT[];

extern u8 BS_FORMCHANGE_WITH_TYPE_CHANGE[];
extern u8 BS_STAT_ONLY_FORMCHANGE_END2[];
extern u8 BS_STAT_ONLY_FORMCHANGE_END3[];
extern u8 BS_ZYGARDE_FORM_CHANGE[];
extern u8 BS_BATTLE_BOND[];
extern u8 BS_MIMIKYU_BUST[];
extern u8 BS_START_Z[];
extern u8 BS_Z_KOMMO_O[];

//locations in asm files
extern const u8 ability_names_table[250][13];
extern const u8 move_names_table[1025][13];
extern const u8 z_move_names_table[47][15];
extern const u8 type_names[TYPE_FAIRY][7];
extern u8* battlescripts_table[183];

#endif /* static_references */
