#include "defines.h"
#include "static_references.h"

u8 get_item_effect(u8 bank, u8 check_negating_effects);
bool has_ability_effect(u8 bank, u8 mold_breaker);
bool check_ability(u8 bank, u8 ability);
bool find_move_in_table(u16 move, const u16* table_ptr);
u8 get_bank_side(u8 bank);

void atk04_critcalc(void)
{
    u8 crit_chance = 0;
    crit_loc = 1;
    u8 def_ability = battle_participants[bank_target].ability_id;
    if (!(has_ability_effect(bank_target, 1) && (def_ability == ABILITY_SHELL_ARMOR || def_ability == ABILITY_BATTLE_ARMOR))
         && !status3[bank_attacker].atk_cant_crt && !battle_flags.wally && !(battle_flags.save_birch && get_bank_side(bank_attacker))
        && !new_battlestruct->side_affecting[get_bank_side(bank_target)].lucky_chant)
    {
        //check if must be crit
        if (find_move_in_table(current_move, always_crit_hits) ||
            (check_ability(bank_attacker, ABILITY_MERCILESS) && BANK_PSN(bank_target))
            || new_battlestruct->bank_affecting[bank_attacker].always_crit)
            crit_loc = 2;
        else
        {
            if (battle_participants[bank_attacker].status2.focus_energy)
                crit_chance += 2;
			if (current_move == MOVE_Z_ASH_PIKACHU)
				crit_chance += 2;
            if (move_table[current_move].move_flags.flags.raised_crit_ratio)
                crit_chance++;
            if (check_ability(bank_attacker, ABILITY_SUPER_LUCK))
                crit_chance++;
            switch (get_item_effect(bank_attacker, 1))
            {
            case ITEM_EFFECT_SCOPELENS:
                crit_chance++;
                break;
            case ITEM_EFFECT_STICK:
                if (battle_participants[bank_attacker].species == POKE_FARFETCHD)
                    crit_chance += 2;
                break;
            case ITEM_EFFECT_LUCKYPUNCH:
                if (battle_participants[bank_attacker].species == POKE_CHANSEY)
                    crit_chance += 2;
                break;
            }
            if (crit_chance >= 3)
                crit_loc = 2;
            else
            {
                static const u16 crit_table[] = {2730, 8192, 32768};
                if (rng() < crit_table[crit_chance])
                    crit_loc = 2;
            }
        }
    }
    battlescripts_curr_instruction++;
}
