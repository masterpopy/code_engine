#include "defines.h"
#include "static_references.h"

u8 get_bank_identity(u8 bank);

extern const struct img_size trainerthrow_pals[];

bool is_in_tag_battle(void)
{
    if (!not_in_battle() && battle_flags.double_battle)
    {
        if (battle_flags.trainer && battle_flags.player_partner)
            return 1;
        if (battle_flags.player_ingame_partner && (partner_trainer & PARTNER_CUSTOM))
            return 1;
    }
    return 0;
}

enum BANK_IDENTITY{
    AWAYS_PLAYER, AI, PARTNER, AI_PARTNER
};

bool is_controlled_by_trainer_in_multi(u8 bank)
{
    if (battle_flags.player_partner || battle_flags.multibattle)
    {
        switch (get_bank_identity(bank))
        {
        case AWAYS_PLAYER: //always player
            return 1;
        case AI: //ai
            if (battle_flags.trainer)
                return 1;
            return 0;
        case PARTNER: //partner
            if (battle_flags.double_battle && (battle_flags.player_ingame_partner || battle_flags.player_partner))
                return 1;
            return 0;
        case AI_PARTNER: //ai partner
            if (battle_flags.double_battle && battle_flags.multibattle)
                return 1;
        }
    }
    return 0;
}

void handle_outcome_trainerbattle(void)
{
    bool loss = battle_outcome == OUTCOME_DRAW || battle_outcome == OUTCOME_LOSS;
    bool pyramid = is_in_battle_pyramid();
    bool frontier = frontier_sth();

    //lost in the battle frontier
    if (var_8015_trainer_opponent_A == 0x400 || (loss && (pyramid || frontier)))
        set_callback2(c2_exit_to_overworld_1_continue_scripts_restart_music);
    //lost normal battle
    else if (loss && !GET_CUSTOMFLAG(ALLOW_LOSE_FLAG))
        set_callback2(c2_whiteout);
    else //battle won or lost but the allow lose flag is set
    {
        set_callback2(c2_exit_to_overworld_1_continue_scripts_restart_music);
        if (!pyramid && !frontier)
        {
            rematch_trainer_flag_set();
            set_battled_trainers_flags();
        }
    }
}

void handle_outcome_rematchbattle(void)
{
    bool loss = battle_outcome == OUTCOME_DRAW || battle_outcome == OUTCOME_LOSS;

    if (var_8015_trainer_opponent_A == 0x400)
        set_callback2(c2_exit_to_overworld_1_continue_scripts_restart_music);
    //won or lost but the custom flag is set
    else if (!loss || GET_CUSTOMFLAG(ALLOW_LOSE_FLAG))
    {
        set_callback2(c2_exit_to_overworld_1_continue_scripts_restart_music);
        rematch_trainer_flag_set();
        set_rematched_trainer_as_defeated();
    }
    //lost
    else
    {
        set_callback2(c2_whiteout);
    }
}

void battle_lost_set_script(void)
{
    battle_state_mode = 0;
    bool outcome_sth = battle_outcome & 0x80;
    battle_outcome &= 0x7F;
    if (!(battle_flags.link || battle_flags.flag_x2000000))
    {
        if (battle_flags.trainer && GET_CUSTOMFLAG(ALLOW_LOSE_FLAG))
            battlescripts_curr_instruction = &BS_CUSTOM_LOSS;
        else
            battlescripts_curr_instruction = (void*)(0x82DA96D);
    }
    else if (!(BATTLE_FRONTIER_BATTLE))
    {
        battle_text_buff1[0] = battle_outcome;
        bank_attacker = get_bank_by_player_ai(0);
        battlescripts_curr_instruction = (void*)(0x82DAA35);
    }
    else if (!outcome_sth)
    {
        battlescripts_curr_instruction = (void*)(0x82DAA0B);
    }
    else
    {
        battlescripts_curr_instruction = (void*)(0x82DB9C8);
        u8* byte = (u8*)(&(*sav2)) + 0xCA9;
        *byte |= 8;
    }
    battle_executed_routine = end_battle;
}

void handle_outcome_partnerbattle(void)
{
    //save current poke data
    struct pokemon* poke = malloc(sizeof(struct pokemon) * 3);
    memcpy(poke, party_player, sizeof(struct pokemon) * 3);

    //restore saved party
    sp29_party_from_save();

    //set current poke data
    memcpy(party_player, poke, sizeof(struct pokemon) * 3);
    free(poke);

    handle_outcome_trainerbattle();
}

void custom_battle_prepare_after_transition(u8 taskID)
{
    if (is_ov_to_battle_transition_done())
    {
        super.callback_backup = handle_outcome_partnerbattle;
        super.callback2 = battlestructs_setup;
        task_delete(taskID);
    }
}

void custom_stevenliketag_battle(void) //var 8005 = opponentB ID, var 8006 partner ID, var 8007: 0x1 - animate backsprite, 0x2 - trainer battle
{
    //save player party
    sp28_party_to_save();

    //set general battle flags
    battle_flags.trainer = 1;
    battle_flags.double_battle = 1;
    battle_flags.player_ingame_partner = 1;
    battle_flags.player_partner = 1;

    //create partner pokes
    partner_trainer = var_8006;
    memset(&party_player[3], 0, sizeof(struct pokemon) * 3);
    create_trainer_pokemon(&party_player[3], partner_trainer, 0);

    //set battle flags for either wild tag or trainer tag
    if (var_8007 & 2)
    {
        battle_flags.multibattle = 1;

        //set trainer B ID
        trainer_opponent_B = var_8005;
    }
    else
    {
        battle_flags.trainer = 0;
    }

    //or partner by 0x4000 to make sure it's a custom partner
    partner_trainer |= PARTNER_CUSTOM;

    //or partner by 0x8000 if it uses actual animations
    if (var_8007 & 1)
        partner_trainer |= PARTNER_ANIMATES;

    //prepare battle start stuff
    task_add(custom_battle_prepare_after_transition, 1);
    set_music_for_battle(0);
    prepare_ov_to_battle_transition(2);
}

u8 get_partner_spriteID(u16 trainerID)
{
    return (*trainer_table)[BIC(trainerID, PARTNER_ANIMATES | PARTNER_CUSTOM)].sprite;
}

u8 get_player_backspriteID(void)
{
    if (player_backsprite)
        return player_backsprite - 1;
    return sav2->gender;
}

const void* get_player_backsprite_pal(void)
{
    return trainerthrow_pals[get_player_backspriteID()].img;
}
