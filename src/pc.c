

#include "pc.h"


u8* get_box_name(u8 boxid)
{
    if (boxid < 14)
        return sav3->name[boxid];
    else if (boxid < MAX_BOX_COUNT) {
        return new_sav3.name[boxid - 14];
    }
    else
        return sav3->name[0];
}

u8* get_box_pal_offset(u8 boxid)
{
    if (boxid < 14)
        return &sav3->bg[boxid];
    else if (boxid < MAX_BOX_COUNT)
        return &new_sav3.bg[boxid - 14];
    else
        return &sav3->bg[0];
}

void set_box_bg(u8 boxid, u8 bgid)
{
    *get_box_pal_offset(boxid) = bgid;
}

u8 get_box_bg(u8 boxid)
{
    return *get_box_pal_offset(boxid);
}

extern u32 sav_index;
extern u16 sav_counterplus1;
#define MAX_SAVE_BLOCK 0xFF4
#define NEW_SAV3 ((u8*)&new_sav3)
#define new_sav ((u8*) 0x0203CF64)
#define SAVE_BLOCK_SIZE 0XE

struct sav_buff_info
{
    u8 section_ID;
    u8 pad0;
    u16 checksum;
    u32 magic_number;
    u32 index;
};

struct sav_buff
{//0x1000
    u8 data[0xFF4];
    struct sav_buff_info savBuffInfo;
};

extern struct sav_buff* sav_buff_ptr;

struct sav_section
{
    void* ptr;
    u16 size;
    u16 pad;
};

extern struct sav_section sav_sections[15];

extern u16 __attribute__((long_call)) sav_get_checksum(struct sav_buff* ptr, u32 size);
extern u8 __attribute__((long_call)) sub_8152908(u32 size, void* ptr);
extern void __attribute__((long_call)) copy_flash_section(u32 sectionID, void* buffer);

void copy_sav_to_buffer(struct sav_buff* sav_buff_ptr, void* sav, u16 size)
{
    u32* added_bytes = (u32*) &active_bank;
    struct sav_buff_info* savBuffInfo = &sav_buff_ptr->savBuffInfo;
    if (savBuffInfo->section_ID == 0)
        *added_bytes = 0;
    memcpy(sav_buff_ptr, sav, size);
    memcpy(sav_buff_ptr->data + size, new_sav + *added_bytes, MAX_SAVE_BLOCK - size);
    *added_bytes += MAX_SAVE_BLOCK - size;
    savBuffInfo->checksum = sav_get_checksum(sav_buff_ptr, MAX_SAVE_BLOCK);
}

u8 sav_to_flash_section(u8 sectionID, struct sav_section* sav_sections)
{
    struct sav_buff_info* savBuffInfo = &sav_buff_ptr->savBuffInfo;
    savBuffInfo->magic_number = 0x8012025;
    u8 result = 0;
    if (sav_sections)
    {
        savBuffInfo->section_ID = sectionID;
        savBuffInfo->index = 1;
        copy_sav_to_buffer(sav_buff_ptr, sav_sections[sectionID].ptr, sav_sections[sectionID].size);
        result = sub_8152908(savBuffInfo->section_ID, sav_buff_ptr);//会先清除存档,复制缓冲数据到存档
    }
    memcpy(sav_buff_ptr, NEW_SAV3 + MAX_SAVE_BLOCK * sectionID, MAX_SAVE_BLOCK);
    savBuffInfo->section_ID = sectionID;
    savBuffInfo->index = 0;
    sub_8152908(sectionID + SAVE_BLOCK_SIZE, sav_buff_ptr);//这里必须是0xE,最多10个
    return result;
}

u8 flash_to_sav0(u8 savID){
    u32 added_bytes = 0;
    struct sav_buff_info* savBuffInfo = &sav_buff_ptr->savBuffInfo;
    for (; savID < 25; savID++)//0-14 15-24,不是连续二分，一共32个block 每个0x1000
    {
        copy_flash_section(savID, sav_buff_ptr);
        u16 sectionID = savBuffInfo->section_ID;
        if (savBuffInfo->magic_number != 0x8012025)
            continue;
        if (sectionID < SAVE_BLOCK_SIZE && savBuffInfo->index == 1)
        {
            u32 size = sav_sections[sectionID].size;
            memcpy(sav_sections[sectionID].ptr, sav_buff_ptr, size);
            memcpy(new_sav + added_bytes, sav_buff_ptr->data + size, MAX_SAVE_BLOCK - size);
            added_bytes += MAX_SAVE_BLOCK - size;
        }
        else if (sectionID < 8 && savBuffInfo->index == 0)
        {
            memcpy(NEW_SAV3 + MAX_SAVE_BLOCK * sectionID, sav_buff_ptr, MAX_SAVE_BLOCK);
        }
    }
    return 1;
}

u8 flash_to_sav()
{
    return flash_to_sav0(0);
}

void new3_to_flash()
{
    for (u8 sectionID = 0; sectionID < 8; sectionID++)
    {
        sav_to_flash_section(sectionID,0);
    }
}

bool flash_to_new3()
{
    return flash_to_sav0(0xE);
}

void wait_flash_to_new3()
{
    over_world_script.mode = 2;
    over_world_script.waiting_routine = flash_to_new3;
}
