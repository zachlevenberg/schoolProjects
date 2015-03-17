#include "Game.h"
#include "Common.h"
#include "Player.h"
#include "HardwareDefs.h"
#include <stdio.h>
#include <string.h>

#define ROOM_TEMPLATE "/room%02d.txt"

static struct _FILEDATA {
    char title[GAME_MAX_ROOM_TITLE_LENGTH];
    char desc[GAME_MAX_ROOM_DESC_LENGTH];
    uint8_t nextRoomNorth;
    uint8_t nextRoomEast;
    uint8_t nextRoomSouth;
    uint8_t nextRoomWest;
} thisFile;

static int GameGetInfo(int roomNumber);



int GameGoNorth(void)
{
    //check for valid door
    if (!thisFile.nextRoomNorth) {
        return STANDARD_ERROR;
    }

    if(!GameGetInfo(thisFile.nextRoomNorth)){
        return STANDARD_ERROR;
    }
    return SUCCESS;
}

int GameGoEast(void)
{
    //check for valid door
    if (!thisFile.nextRoomEast) {
        return STANDARD_ERROR;
    }

    if(!GameGetInfo(thisFile.nextRoomEast)){
        return STANDARD_ERROR;
    }
    return SUCCESS;
}

int GameGoSouth(void)
{
    //check for valid door
    if (!thisFile.nextRoomSouth) {
        return STANDARD_ERROR;
    }

    if(!GameGetInfo(thisFile.nextRoomSouth)){
        return STANDARD_ERROR;
    }
    return SUCCESS;
}

int GameGoWest(void)
{
    //check for valid door
    if (!thisFile.nextRoomWest) {
        return STANDARD_ERROR;
    }

    if(!GameGetInfo(thisFile.nextRoomWest)){
        return STANDARD_ERROR;
    }
    return SUCCESS;
}

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void)
{
    //create text file name and open it

    if(!GameGetInfo(STARTING_ROOM)){
        return STANDARD_ERROR;
    }
    return SUCCESS;

}

int GameGetCurrentRoomTitle(char *title)
{
    int i = 0;
    while (thisFile.title[i] != NULL) {
        title[i] = thisFile.title[i];
        i++;
    }
    title[i] = NULL;
    int temp =strlen(title);
    if(i != temp){
        title[0] = NULL;
        return STANDARD_ERROR;
    }
    return strlen(title);
}

int GameGetCurrentRoomDescription(char *desc)
{
    int i = 0;
    while (thisFile.desc[i] != NULL) {
        desc[i] = thisFile.desc[i];
        i++;
    }
    desc[i] = NULL;
        int temp =strlen(desc);
    if(i != temp){
        desc[0] = NULL;
        return STANDARD_ERROR;
    }
    return strlen(desc);
}

uint8_t GameGetCurrentRoomExits(void)
{
    uint8_t temp = 0;
    if (thisFile.nextRoomNorth) {
        temp |= GAME_ROOM_EXIT_NORTH_EXISTS;
    }

    if (thisFile.nextRoomEast) {
        temp |= GAME_ROOM_EXIT_EAST_EXISTS;
    }

    if (thisFile.nextRoomSouth) {
        temp |= GAME_ROOM_EXIT_SOUTH_EXISTS;
    }

    if (thisFile.nextRoomWest) {
        temp |= GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return temp;
}

int GameGetInfo(int roomNumber)
{
    char fileName[12];
    sprintf(fileName, ROOM_TEMPLATE, roomNumber);

    FILE *fp;
    fp = fopen(fileName, "rb");
    if(fp == NULL) {
        FATAL_ERROR();
    }
    uint8_t input;

    //get title
    input = fgetc(fp);
    int i = 0;
    for (i = 0; i < input; i++) {
        thisFile.title[i] = fgetc(fp);
    }
    thisFile.title[i] = NULL;

    bool fail = false;
    while (1) {
        input = fgetc(fp);
        for (i = 0; i < input; i++) {
            uint8_t item = fgetc(fp);
            if (!FindInInventory(item)) {
                fail = true;
            }
        }
        //if we fail, seek and try again.
        if (fail) {
            input = fgetc(fp);
            fseek(fp, input, SEEK_CUR);
            input = fgetc(fp);
            fseek(fp, input + 4, SEEK_CUR);
            fail = false;
            continue;
        }

        //get description
        input = fgetc(fp);
        for (i = 0; i < input; i++) {
            thisFile.desc[i] = fgetc(fp);
        }
        thisFile.desc[i] = NULL;

        //get items contained
        input = fgetc(fp);
        for (i = 0; i < input; i++) {
            uint8_t item = fgetc(fp);
            if (!FindInInventory(item)) {
                AddToInventory(item);
            }
        }

        //get Exits
        thisFile.nextRoomNorth = fgetc(fp);
        thisFile.nextRoomEast = fgetc(fp);
        thisFile.nextRoomSouth = fgetc(fp);
        thisFile.nextRoomWest = fgetc(fp);

        if (fclose(fp) != 0) {
            return STANDARD_ERROR;
        }
        return SUCCESS;
        break;
    }
}