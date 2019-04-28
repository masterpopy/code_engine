#include "defines.h"


const struct b_background_info battle_bgs[] =
#if EM_VERSION == EM
{
    {&bg_grass_tileset, &bg_grass_tilemap, &entry_bg_grass_tileset, &entry_bg_grass_tilemap, &bg_grass_pal}, //0 grass
    {&bg_longgrass_tileset, &bg_longgrass_tilemap, &entry_bg_longgrass_tileset, &entry_bg_longgrass_tilemap, &bg_longgrass_pal}, //1 long grass
    {&bg_sand_tileset, &bg_sand_tilemap, &entry_bg_sand_tileset, &entry_bg_sand_tilemap, &bg_sand_pal}, //2 sand
    {&bg_underwater_tileset, &bg_underwater_tilemap, &entry_bg_underwater_tileset, &entry_bg_underwater_tilemap, &bg_underwater_pal}, //3 underwater
    {&bg_water_tileset, &bg_water_tilemap, &entry_bg_water_tileset, &entry_bg_water_tilemap, &bg_water_pal}, //4 water
    {&bg_pond_tileset, &bg_pond_tilemap, &entry_bg_pond_tileset, &entry_bg_pond_tilemap, &bg_pond_pal}, //5 pond
    {&bg_rock_tileset, &bg_rock_tilemap, &entry_bg_rock_tileset, &entry_bg_rock_tilemap, &bg_rock_pal}, //6 rock
    {&bg_cave_tileset, &bg_cave_tilemap, &entry_bg_cave_tileset, &entry_bg_cave_tilemap, &bg_cave_pal}, //7 cave
    {&bg_indoors_tileset, &bg_indoors_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_indoors1_pal}, //8 indoors1
    {&bg_indoors_tileset, &bg_indoors_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_indoors2_pal}, //9 indoors2
    {&bg_indoors_tileset, &bg_indoors_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_frontier_pal}, //10 frontier
    {&bg_cave_tileset, &bg_cave_tilemap, &entry_bg_cave_tileset, &entry_bg_cave_tilemap, &bg_groudon_pal}, //11 groudon
    {&bg_water_tileset, &bg_water_tilemap, &entry_bg_underwater_tileset, &entry_bg_underwater_tilemap, &bg_kyorge_pal}, //12 kyorge
    {&bg_rayquaza_tileset, &bg_rayquaza_tilemap, &entry_bg_ray_tileset, &entry_bg_ray_tilemap, &bg_rayquaza_pal}, //13 rayquaza
    {&bg_indoors_tileset, &bg_indoors_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_leader_pal}, //14 leader
    {&bg_indoors_tileset, &bg_indoors_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_champion_pal}, //15 champion
    {&bg_indoors_tileset, &bg_indoors_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_gym_pal}, //16 gym
    {&bg_boss_tileset, &bg_boss_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_teammagma_pal}, //17 team magma
    {&bg_boss_tileset, &bg_boss_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_teamaqua_pal}, //18 team aqua
    {&bg_boss_tileset, &bg_boss_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_elitefour1_pal}, //19 elitefour1
    {&bg_boss_tileset, &bg_boss_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_elitefour2_pal}, //20 elitefour2
    {&bg_boss_tileset, &bg_boss_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_elitefour3_pal}, //21 elitefour3
    {&bg_boss_tileset, &bg_boss_tilemap, &entry_bg_indoors_tileset, &entry_bg_indoors_tilemap, &bg_elitefour4_pal}, //22 elitefour4
};

// const struct b_background_info battle_bgs[] = {
// {(void*)0x8f708d0,(void*)0x8f70350,(void*)0x8d7e280,(void*)0x8f79f60,(void*)0x8d78318},//grass
// {(void*)0x8f71ef0,(void*)0x8f70350,(void*)0x8d7e9c4,(void*)0x8f7a130,(void*)0x8d78c78},//long grass
// {(void*)0x8f73130,(void*)0x8f70350,(void*)0x8d7f30c,(void*)0x8d7f850,(void*)0x8d79560},//sand
// {(void*)0x8f73fc0,(void*)0x8f70350,(void*)0x8d7f9f8,(void*)0x8f7a370,(void*)0x8d79e10},//underwater
// {(void*)0x8f75170,(void*)0x8f70350,(void*)0x8d80054,(void*)0x8f7a500,(void*)0x8d7a6dc},//water
// {(void*)0x8f76230,(void*)0x8f70350,(void*)0x8d80804,(void*)0x8f7a6b0,(void*)0x8d7af78},//pond
// {(void*)0x8f76f60,(void*)0x8f70350,(void*)0x8d80e9c,(void*)0x8d8147c,(void*)0x8d7b828},//rock
// {(void*)0x8f78c30,(void*)0x8f70350,(void*)0x8d81610,(void*)0x8d81e2c,(void*)0x8d7c10c},//cave
// {(void*)0x8f7a800,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7deb4},//indoors1
// {(void*)0x8f7cbe0,(void*)0x949c6c0,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7c404},//indoors2
// {(void*)0x8f7a800,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7c9ec},//frontier
// {(void*)0x8f78c30,(void*)0x8f70350,(void*)0x8d81610,(void*)0x8d81e2c,(void*)0x8d7df30},//groudon
// {(void*)0x8f75170,(void*)0x8f70350,(void*)0x8d7f9f8,(void*)0x8f7a370,(void*)0x8d7def4},//kyogre
// {(void*)0x8d7d590,(void*)0x8d7dc04,(void*)0x8d82608,(void*)0x8d82c70,(void*)0x8d7e234},//rayquaza
// {(void*)0x8f7a800,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7dfc4},//leader
// {(void*)0x8f7c230,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7e1f8},//champion
// {(void*)0x8f7a800,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7df88},//gym
// {(void*)0x8f7b950,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7e060},//team magma
// {(void*)0x8f7b950,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7e000},//team aqua
// {(void*)0x8f7b950,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7e0cc},//elitefour1
// {(void*)0x8f7b950,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7e11c},//elitefour2
// {(void*)0x8f7b950,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7e164},//elitefour3
// {(void*)0x8f7b950,(void*)0x8f70350,(void*)0x8d820d4,(void*)0x8d824e4,(void*)0x8d7e1a8}//elitefour4
// };


//only for II
#elif EM_VERSION == UTRAL
{
    {(void*) 0x8f708d0, (void*) 0x8a6a3d0, (void*) 0x8d7e280, (void*) 0x8f79f60, (void*) 0x8d78318},//grass
    {(void*) 0x8f71ef0, (void*) 0x8a6a3d0, (void*) 0x8d7e9c4, (void*) 0x8f7a130, (void*) 0x8d78c78},//long grass
    {(void*) 0x8f73130, (void*) 0x8a6a3d0, (void*) 0x8d7f30c, (void*) 0x8d7f850, (void*) 0x8d79560},//sand
    {(void*) 0x8f73fc0, (void*) 0x8a6a950, (void*) 0x8d7f9f8, (void*) 0x8f7a370, (void*) 0x8d79e10},//underwater
    {(void*) 0x8f75170, (void*) 0x8a6aef0, (void*) 0x8d80054, (void*) 0x8f7a500, (void*) 0x8d7a6dc},//water
    {(void*) 0x8f76230, (void*) 0x8a6b490, (void*) 0x8d80804, (void*) 0x8f7a6b0, (void*) 0x8d7af78},//pond
    {(void*) 0x8f76f60, (void*) 0x8a6b490, (void*) 0x8d80e9c, (void*) 0x8d8147c, (void*) 0x8d7b828},//rock
    {(void*) 0x8f78c30, (void*) 0x8a6bfb0, (void*) 0x8d81610, (void*) 0x8d81e2c, (void*) 0x8d7c10c},//cave
    {(void*) 0x8f7a800, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7deb4},//indoors1
    {(void*) 0x8f7cbe0, (void*) 0x8a700c0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7c404},//indoors2
    {(void*) 0x8f7a800, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7c9ec},//frontier
    {(void*) 0x8f78c30, (void*) 0x8a6bfb0, (void*) 0x8d81610, (void*) 0x8d81e2c, (void*) 0x8d7df30},//groudon
    {(void*) 0x8f75170, (void*) 0x8a6aef0, (void*) 0x8d7f9f8, (void*) 0x8f7a370, (void*) 0x8d7def4},//kyogre
    {(void*) 0x8d7d590, (void*) 0x8d7dc04, (void*) 0x8d82608, (void*) 0x8d82c70, (void*) 0x8d7e234},//rayquaza
    {(void*) 0x8f7a800, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7dfc4},//leader
    {(void*) 0x8f7c230, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7e1f8},//champion
    {(void*) 0x8f7a800, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7df88},//gym
    {(void*) 0x8f7a800, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7e060},//team magma
    {(void*) 0x8f7b950, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7e000},//team aqua
    {(void*) 0x8f7b950, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7e0cc},//elitefour1
    {(void*) 0x8f7b950, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7e11c},//elitefour2
    {(void*) 0x8f7b950, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7e164},//elitefour3
    {(void*) 0x8f7b950, (void*) 0x8a6a3d0, (void*) 0x8d820d4, (void*) 0x8d824e4, (void*) 0x8d7e1a8}//elitefour4
};

#endif
const struct img_size trainerthrow_imgs[] = {
        {(void*) 0x8D66480, 0x2000}, // 0 brendan
        {(void*) 0x8D68480, 0x12000}, // 1 may
        {(void*) 0x8D6A480, 0x22800}, // 2 FR male protag
        {(void*) 0x8D6CC80, 0x32800}, // 3 FR female protag
        {(void*) 0x8D6F480, 0x42000}, // 4 RS brendan
        {(void*) 0x8D71480, 0x52000}, // 5 RS may
        {(void*) 0x8D73480, 0x62000}, // 6 wally
        {(void*) 0x8D75480, 0x72000}, // 7 steven
};

u8 wally_pallete[] __attribute__((aligned(2))) = {
        0x10, 0x20, 0x0, 0x0, 0x0, 0xe, 0x53, 0xbf, 0x6b, 0xdb, 0x52, 0x57, 0x3a, 0x0, 0x6f, 0x29, 0x53, 0x56, 0xae,
        0x41, 0x37, 0x33, 0x0, 0xb2, 0x26, 0x7b, 0x73, 0x4c, 0x1a, 0xa8, 0xd, 0x0, 0x6c, 0x6e, 0xd6, 0x66, 0xff, 0x7f,
        0x0, 0x0};

u8 steven_pallete[] __attribute__((aligned(2))) = {
        0x10, 0x20, 0x0, 0x0, 0x0, 0xe, 0x53, 0x7f, 0x67, 0xdb, 0x4a, 0x57, 0x3a, 0x0, 0x6f, 0x29, 0xd7, 0x65, 0x54,
        0x55, 0x4a, 0x2d, 0x0, 0xc6, 0x1c, 0x7a, 0x77, 0xf5, 0x6a, 0x4f, 0x52, 0x0, 0x9f, 0x2d, 0x18, 0x21, 0xff, 0x7f,
        0x0, 0x0};

const struct img_size trainerthrow_pals[] = {
        {(void*) 0x83021E0, 0}, // 0 brendan
        {(void*) 0x83021E0, 1}, // 1 may
        {(void*) 0x8D77480, 2}, // 2 FR male protag
        {(void*) 0x8D774A8, 3}, // 3 FR female protag
        {(void*) 0x8D66130, 4}, // 4 RS brendan
        {(void*) 0x8D66458, 5}, // 5 RS may
        {wally_pallete, 6}, // 6 wally
        {steven_pallete, 7}, // 7 steven
};

const struct trainerhrow_position trainerhrow_positions[] = {
        {8, 4, 0}, // 0 brendan
        {8, 4, 0}, // 1 may
        {8, 5, 0}, // 2 FR male protag
        {8, 5, 0}, // 3 FR female protag
        {8, 4, 0}, // 4 RS brendan
        {8, 4, 0}, // 5 RS may
        {8, 4, 0}, // 6 wally
        {8, 4, 0}, // 7 steven
};

bool does_partner_animate(void)
{
    return (partner_trainer == TRAINER_STEVEN || (partner_trainer & PARTNER_ANIMATES));
}

u8 get_fitting_BG_ID(void)
{
    if (BATTLE_FRONTIER_BATTLE || battle_flags.link)
        return BACKGROUND_FRONTIER;
    else if (battle_flags.groudon)
        return BACKGROUND_GROUDON;
    else if (battle_flags.kyorge)
        return BACKGROUND_KYORGE;
    else if (battle_flags.rayquaza)
        return BACKGROUND_RAYQUAZA;
    else if (battle_flags.trainer)
    {
        u8 class = (*trainer_table)[var_8015_trainer_opponent_A].class;
        if (class == CLASS_LEADER)
            return BACKGROUND_LEADER;
        if (class == CLASS_CHAMPION)
            return BACKGROUND_CHAMPION;
    }
    switch (sav1_get_map_battleground())
    {
        case 0:
            if (battle_chosen_bg)
                return battle_chosen_bg - 1;
            else
                return battle_env_bg;
        case 1:
            return BACKGROUND_GYM;
        case 2:
            return BACKGROUND_TEAM_MAGMA;
        case 3:
            return BACKGROUND_TEAM_AQUA;
        case 4:
            return BACKGROUND_ELITEFOUR1;
        case 5:
            return BACKGROUND_ELITEFOUR2;
        case 6:
            return BACKGROUND_ELITEFOUR3;
        case 7:
            return BACKGROUND_ELITEFOUR4;
        case 8:
        default:
            return BACKGROUND_FRONTIER;
    }
}

const struct b_background_info* get_BG_struct(void)
{
    return &battle_bgs[get_fitting_BG_ID()];
}

void b_load_fitting_bg(void)
{
    const struct b_background_info* BG_info = get_BG_struct();
    LZ77UnCompVram(BG_info->tileset, (void*) (0x06008000));
    LZ77UnCompVram(BG_info->tilemap, (void*) (0x0600D000));
    gpu_pal_decompress_apply(BG_info->pal, 0x20, 0x60);
}

void b_load_fitting_entry_bg(void)
{
    if (battle_flags.link)
    {
        LZ77UnCompVram((void*) (0x8D778F0), (void*) (0x06004000));
        LZ77UnCompVram((void*) (0x8D77B0C), (void*) (0x06010000));
        gpu_pal_decompress_apply((void*) (0x8D77AE4), 0x60, 0x20);
        gpu_bg_config_set_field(1, 3, 1);

        lcd_io_set(0xA, 0x5C04);
        tilemap_decompress_wram_BGconfig(1, (void*) (0x8D779D8), 0, 0);
        tilemap_decompress_wram_BGconfig(2, (void*) (0x8D779D8), 0, 0);
        bgid_send_tilemap(1);
        bgid_send_tilemap(2);

        lcd_io_set(0x48, 0x36);
        lcd_io_set(0x4A, 0x36);
        BG1Y_battle = 0xFF5C;
        bg2Y_battle = 0xFF5C;
        gpu_decompress_tile_obj_alloc_tag_and_upload((void*) (0x831AA00));
    }
    else if (battle_flags.player_ingame_partner && !does_partner_animate())
    {
        gpu_bg_config_set_field(1, 1, 2);
        gpu_bg_config_set_field(2, 1, 2);

        tilemap_decompress_wram_BGconfig(1, (void*) (0x8D857A8), 0, 0);
        tilemap_decompress_wram_BGconfig(2, (void*) (0x8D85A1C), 0, 0);

        bgid_send_tilemap(1);
        bgid_send_tilemap(2);
    }
    else
    {
        const struct b_background_info* BG_info = get_BG_struct();
        LZ77UnCompVram(BG_info->entry_tileset, (void*) (0x06004000));
        LZ77UnCompVram(BG_info->entry_tilemap, (void*) (0x0600E000));
    }
}

bool b_load_chosen_bg_element(u8 caseID)
{
    bool to_ret = 0;
    const struct b_background_info* BG_info = get_BG_struct();
    switch (caseID)
    {
        case 0: //tileset battle text box
            LZ77UnCompWram(battletextbox_tileset, (void*) (0x6000000));
            break;
        case 1: //tilemap battle text box
            tilemap_decompress_wram_BGconfig(0, battletextbox_tilemap, 0, 0);
            bgid_send_tilemap(0);
            break;
        case 2: //pal battle text box
            gpu_pal_decompress_apply(battletextbox_pal, 0, 0x40);
            break;
        case 3: //bg tileset
            LZ77UnCompVram(BG_info->tileset, (void*) (0x06008000));
            break;
        case 4: //bg tilemap
            LZ77UnCompVram(BG_info->tilemap, (void*) (0x0600D000));
            break;
        case 5: //bg pal
            gpu_pal_decompress_apply(BG_info->pal, 0x20, 0x60);
            break;
        case 6: //frame battle text box
            frame_battletextbox();
            break;
        default:
            to_ret = 1;
            break;
    }
    return to_ret;
}
