#include "Player.h"


static struct _INVENTORY {
    uint8_t index;
    uint8_t items[INVENTORY_SIZE - 1];
} myItems;


int AddToInventory(uint8_t item)
{
    if(myItems.index == INVENTORY_SIZE - 1) {
        return STANDARD_ERROR;
    } else {
        myItems.items[myItems.index] = item;
        myItems.index++;
    }
    return SUCCESS;
}


int FindInInventory(uint8_t item)
{
    int i = 0;
    for(i = 0; i < INVENTORY_SIZE; i++) {
        if(myItems.items[i] == item){
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}
