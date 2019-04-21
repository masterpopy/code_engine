#ifndef CONFIG_H
#define CONFIG_H

#define ALL_POKES       1200     //number of all pokemon
#define ALL_ITEMS       800     //number of all items
#define NUM_OF_EVOS     5       //number of evolutions per pokemon
#define KEYSTONE        0x78     //mega item that the player has to posses in order to mega evolve

#define BUILD_LEARNSETS true        //set to false if you modified the learnsets and dont want them to get changed
#define GEN4_LEARNSETS  true //set to true if you want to have learnsets for pokemon up to genIV
#define GEN5_LEARNSETS  true         //set to true if you want to have learnsets for pokemon up to genV
#define GEN6_LEARNSETS  true          //set to true if you want to have learnsets for pokemon up to genVI
#define GEN7_LEARNSETS true

#define EXP_CAPTURE         false    //set to false if you don't want to receive exp from catching pokes
#define STAT_RECALC         false   //set to true if you want all pokemon having their stats recalculated at the end of the battle
#define ITEM_STEAL          true   //if true player is able to steal other trainers' items, if false the stolen item will disappear at the end of the battle
#define ITEM_SWAP           false   //if true player's item will be that that was switched, if false the switched item that a pokemon originally had returns to it
#define MAX_LEVEL           100     //highest possible level
#define MAX_EVS             510     //maximum amount of EV points per pokemon
#define EXP_DIVIDE          true    //if true exp will be divided among pokemon(if two pokemon participate they'll get 50 % each), set to false if you want gen6-style exp
#define GENVI_EXPSHARE      true    //set to true if you want EXPSHARE to act like in gen6
#define EXPSHARE_FLAG       0x275   //flag that must be set for GENVI expshare to work
#define DISABLED_EXP_FLAG   0x276   //if that flag is set, receiving exp is disabled, if flag is 0 it has no effect
#define DISABLED_EVS_FLAG   0x277     //if that flag is set, receiving EVS points is disabled, if flag is 0 it has no effect; this and above flag can be the same
#define DOUBLE_WILD_BATTLES true    //set to false if you don't want have them in your hack at all
//#define DOUBLE_WILD_BATTLES_FLAG 0x27B //0x278是有问题的
#define DOUBLE_WILD_TILES   4      //amount of tiles double wild battles are possible on
#define EXPANDED_POKEBALLS  true  //set to true if your hack uses pokeball expansion
#define INVERSE_FLAG        0x271   //if that flag is set, the battle is inverse
#define FISHING_FLAG        0x270   //if that flag is set, it's a battle against a hooked up pokemon
#define CANT_CATCH_FLAG     0x272   //if that flag is set, you can't catch any pokemon, if flag is 0 you always can catch any pokemon
#define ALLOW_LOSE_FLAG     0x273   //if that flag is set, you can lose a battle and the script will continue
#define FORCE_SET_FLAG      0x274   //if that flag is set, the player cannot switch a pokemon when opponent faints
#define NO_OF_SLIDING_MSG_TRAINERS 5 //number of trainers that say things in the middle of a battle
#define SCHOOLING_LEVEL     20
#define BALL_DREAM_FLAG     0x279
//#define DISABLE_BALL_MASTER_FLAG     0x4091


//form indexes
/*#define POKE_ZEN_MODE               961
#define POKE_GRENJA                 0x2C7
#define POKE_ASH_GRENJA             0x3C3
#define POKE_WISHIWASHI             0x31F
#define POKE_WISHIWASHI_SCHOOL      0x3C2
#define POKE_ZYGARDE_10            	0x3C8
#define POKE_ZYGARDE_50             0x303
#define POKE_ZYGARDE_100            0x3C7
#define POKE_MINIOR_CORE            0x3CB
#define POKE_MINIOR_METEOR          0x33B
#define POKE_MIMIKKYU               0x33F
#define POKE_MIMIKKYU_BUSTED        0x3E5*/

//only change these if you want to adjust the position of mega icons or if you want to change the HP bars
#define SINGLES_HEALTHBOX_X 116
#define DBL_HB_0_X 118
#define DBL_HB_2_X 130
#define SINGLES_HEALTHBOX_Y 90
#define DBL_HB_0_Y 75
#define DBL_HB_2_Y 100

#define EM 0
#define UTRAL 1

#define EM_VERSION UTRAL

#endif /* CONFIG_H */
