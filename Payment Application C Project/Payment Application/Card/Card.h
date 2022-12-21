/*
 * Card.h
 *
 *  Created on: Dec 4, 2022
 *      Author: asus
 */
#ifndef CARD_H_
#define CARD_H_

#include "stdio.h"
#include "string.h"
#include "stdint.h" // AutoSar Convention Typedefs
#include "BugFix.h" // Printf bugfix in Eclipse(Replacing with a DPRINTF MACRO)

// Card Data type
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];

}ST_cardData_t;

// Enumeration of the Card Status
typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

// Prototypes
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* CARD_H_ */
