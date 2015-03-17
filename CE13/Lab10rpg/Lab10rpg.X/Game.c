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

void GameGetInfo(int roomNumber);

// The initial room that Game should initialize to.
//#define STARTING_ROOM 32

// These variable describe the maximum string length of the room title and description respectively.
// Note that they don't account for the trailing '\0' character implicit with C-style strings.
//#define GAME_MAX_ROOM_TITLE_LENGTH 22
//#define GAME_MAX_ROOM_DESC_LENGTH 255

/**
 * This enum defines flags for checking the return values of GetCurrentRoomExits(). Usage is as
 * follows:
 *
 * if (GetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
 *   // The current room has a west exit.
 * }
 *
 * @see GetCurrentRoomExits
 */
//typedef enum {
//    GAME_ROOM_EXIT_WEST_EXISTS  = 0b0001,
//    GAME_ROOM_EXIT_SOUTH_EXISTS = 0b0010,
//    GAME_ROOM_EXIT_EAST_EXISTS  = 0b0100,
//    GAME_ROOM_EXIT_NORTH_EXISTS = 0b1000
//} GameRoomExitFlags;

/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */
int GameGoNorth(void)
{
    //check for valid door
    if (!thisFile.nextRoomNorth) {
        return STANDARD_ERROR;
    }

    GameGetInfo(thisFile.nextRoomNorth);
//    //create text file name and open it
//    char fileName[10];
//    sprintf(fileName, ROOM_TEMPLATE, thisFile.nextRoomNorth);
//    FILE *fp;
//    fp = fopen(fileName, "r");
//    GameGetInfo(fp);
//    fclose(fp);
    return SUCCESS;
}

/**
 * @see GameGoNorth
 */
int GameGoEast(void)
{
    //check for valid door
    if (!thisFile.nextRoomEast) {
        return STANDARD_ERROR;
    }

    GameGetInfo(thisFile.nextRoomEast);
//    //create text file name and open it
//    char fileName[10];
//    sprintf(fileName, ROOM_TEMPLATE, thisFile.nextRoomEast);
//    FILE *fp;
//    fp = fopen(fileName, "r");
//    GameGetInfo(fp);
//    fclose(fp);
    return SUCCESS;
}

/**
 * @see GameGoNorth
 */
int GameGoSouth(void)
{
    //check for valid door
    if (!thisFile.nextRoomSouth) {
        return STANDARD_ERROR;
    }

    GameGetInfo(thisFile.nextRoomSouth);

//    //create text file name and open it
//    char fileName[11];
//    sprintf(fileName, ROOM_TEMPLATE, thisFile.nextRoomSouth);
//    FILE *fpS;
//    fpS = fopen(fileName, "r");
//    GameGetInfo(fpS);
//    fclose(fpS);


    return SUCCESS;
}

/**
 * @see GameGoNorth
 */
int GameGoWest(void)
{
    //check for valid door
    if (!thisFile.nextRoomWest) {
        return STANDARD_ERROR;
    }

    GameGetInfo(thisFile.nextRoomWest);
//    //create text file name and open it
//    char fileName[10];
//
//    sprintf(fileName, ROOM_TEMPLATE, thisFile.nextRoomWest);
//    FILE *fp;
//    fp = fopen(fileName, "r");
//    GameGetInfo(fp);
//    fclose(fp);
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

    GameGetInfo(STARTING_ROOM);
    
    
    return SUCCESS;

}

/**
 * Copies the appropriate room title as a NULL-terminated string into the provided character array.
 * The appropriate room means the first room description that the Player has the required items to
 * see. Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param desc A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title)
{
    int i = 0;
    while(thisFile.title[i] != NULL) {
        title[i] = thisFile.title[i];
        i++;
    }
    title[i] = NULL;
    return strlen(title);
}

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc)
{
    int i = 0;
    while(thisFile.desc[i] != NULL) {
        desc[i] = thisFile.desc[i];
        i++;
    }
    desc[i] = NULL;
    return strlen(desc);
}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
uint8_t GameGetCurrentRoomExits(void)
{
    uint8_t temp = 0;
    if(thisFile.nextRoomNorth) {
        temp |= GAME_ROOM_EXIT_NORTH_EXISTS;
    }

    if(thisFile.nextRoomEast) {
        temp |= GAME_ROOM_EXIT_EAST_EXISTS;
    }

    if(thisFile.nextRoomSouth) {
        temp |= GAME_ROOM_EXIT_SOUTH_EXISTS;
    }

    if(thisFile.nextRoomWest) {
        temp |= GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return temp;
}

void GameGetInfo(int roomNumber)
{
    char fileName[12];
    sprintf(fileName, ROOM_TEMPLATE, roomNumber);
    FILE *fp;
//    fp = fopen(fileName, "r");
//    while(fgetc(fp) != EOF){
//        continue;
//    }
//    fclose(fp);
    fp = fopen(fileName, "r");
    //fp->_cnt = 0;

//    char testString[300];
//    fread(testString, 299, 1, fp);


    uint8_t input;
    bool badInput = false;

    //get title
    input = fgetc(fp);
    //if(input == 0x45){input = 0x0c;}
    int i = 0;
    for (i = 0; i < input; i++) {
        thisFile.title[i] = fgetc(fp);
    }
    thisFile.title[i] = NULL;

    bool fail = false;
    while (1) {

        badInput = false;

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
        for(i = 0; i < input; i++) {
            uint8_t item = fgetc(fp);
            if(!FindInInventory(item)) {
                AddToInventory(item);
            }
        }

        //get Exits
        thisFile.nextRoomNorth = fgetc(fp);
        thisFile.nextRoomEast = fgetc(fp);
        thisFile.nextRoomSouth = fgetc(fp);
        thisFile.nextRoomWest = fgetc(fp);
    
        break;
    }
    
    if(fclose(fp) != 0){
        FATAL_ERROR();
    }
}