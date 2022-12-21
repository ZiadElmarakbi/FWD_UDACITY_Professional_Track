/*
 * Card.c
 *
 *  Created on: Dec 4, 2022
 *      Author: Ziad Mohamed
 */
#include "Card.h"

// ST_cardData_t y, *Y = &y; /* Creating a static memory space of 5 elements, each
//  contain a structure of the Card Data Type */

// Temporary Main Function in the existing file for testing
//int main(void){
//	//
//	//	// Passing by Reference
//	//	//  getCardHolderName(Y);
//	getCardExpiryDate(Y);
//	//	getCardPAN(Y);
//	//
//	return 0 ;
//}

// Defined Functions for the CARD Module
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){

	uint8_t Length;

	DPRINTF("Enter the CardHolder Name: ");
	gets((char*)cardData->cardHolderName);
	Length = strlen((const char*)cardData->cardHolderName);

	if(Length == 0 || Length < 20 || Length > 24){
		DPRINTF("Incorrect Name Format !\n");
		return WRONG_NAME ;
	}

	DPRINTF("\nHello, %s\n", cardData->cardHolderName);
	return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){

	uint8_t *p1, *p2, *p3, Length;

	p1 = &(cardData->cardExpirationDate[0]);
	p2 = &(cardData->cardExpirationDate[1]);
	p3 = &(cardData->cardExpirationDate[2]);

	DPRINTF("\nEnter the Card Expiry Date in the MM/YY Format:");
	gets((char*)cardData->cardExpirationDate);

	Length = strlen((const char*)cardData->cardExpirationDate);

	if(Length == 0 || Length > 5 || Length < 5){
		DPRINTF("Please enter the correct date\n");
		return WRONG_EXP_DATE;
	}

	if((*p1 > '1') || ((*p1 == '1') && (*p2 > '2'))){
		DPRINTF("Wrong date format\n");
		return WRONG_EXP_DATE;
	}

	if(*p3 != '/'){
		DPRINTF("Wrong Date Format\n");
		return WRONG_EXP_DATE;
	}

	// DPRINTF("CORRECT FORMAT !!\n");
	return CARD_OK ;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){

	uint8_t Length;

	DPRINTF("Enter the Card PAN: ");
	gets((char*)cardData->primaryAccountNumber);

	Length = strlen((const char*)cardData->primaryAccountNumber);

	if(Length == 0 || Length < 16 || Length > 20){
		DPRINTF("Wrong Pan Number !\n"); // Debugging Info
		return WRONG_PAN ;
	}

	// DPRINTF("Correct PAN Format\n"); // Debugging Info
	return CARD_OK;
}
