#ifndef FLAVOURS_H
#define FLAVOURS_H

enum poke_flavours
{
    SPICY_PREFERENCE, //0
    DRY_PREFERENCE, //1
    SWEET_PREFERENCE, //2
    BITTER_PREFERENCE, //3
    SOUR_PREFERENCE //4
};

enum poke_flavour_status
{
    FLAVOUR_NEUTRAL = 0,
    FLAVOUR_LIKED = 1,
    FLAVOUR_DISLIKED = -1
};
#endif /* FLAVOURS_H */
