/*
 * Server.c
 *
 *  Created on: Dec 4, 2022
 *      Author: asus
 */
#include "Server.h"

uint32_t TransNum = 0, Account_Num = 0;

ST_accountsDB_t accountsDB[DBMAX] = {
		{2000, RUNNING, "89123456889978456487"},
		{1000.0, BLOCKED, "79123456889978456487"},
		{0.00,   RUNNING, "69123456889978456487"},
		{750.0,  BLOCKED, "59123456889978456487"},
		{2000.0, BLOCKED, "49123456889978456487"}
};

ST_transaction transactionDB[DBMAX] = {0}, OBJ, *ptr = &OBJ;
// EN_transStat_t Transaction_State;

//int main(){

// Valid Account Test Cases
//			if(getCardPAN(&ptr->cardHolderData) == CARD_OK)
//				isValidAccount(&ptr->cardHolderData, accountsDB);

// Blocked Account Test Cases
// isBlockedAccount(&accountsDB[0]);

// Transaction Amount Test Cases
//		if(getTransactionAmount(&ptr->terminalData) == TERMINAL_OK)
//			isAmountAvailable(&ptr->terminalData, accountsDB);

// Saving Accounts Test Cases
//		TransNum = 256;
//		saveTransaction(ptr);


// Receive Transactions Test Cases
//	getCardPAN(&ptr->cardHolderData);
//	getTransactionAmount(&ptr->terminalData);
//	TransNum = 256;
//	recieveTransactionData(ptr);

//	getCardHolderName(&ptr->cardHolderData);
//	getCardExpiryDate(&ptr->cardHolderData);
//	getCardPAN(&ptr->cardHolderData);
//	getTransactionDate(&ptr->terminalData);
//	getTransactionAmount(&ptr->terminalData);
//	setMaxAmount(&ptr->terminalData, 3000.0);
//	TransNum = 2;
//	recieveTransactionData(ptr);
//	listSavedTransactions();

//	return 0 ;
//}

EN_transStat_t recieveTransactionData(ST_transaction *transData){

	if(isValidAccount(&transData->cardHolderData, accountsDB) == ACCOUNT_NOT_FOUND){
		return FRAUD_CARD;
	}

	if(isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT){
		return DECLINED_STOLEN_CARD;
	}

	if(isAmountAvailable(&transData->terminalData, accountsDB) == LOW_BALANCE){
		return DECLINED_INSUFFECIENT_FUND;
	}

	if(saveTransaction(transData) == SAVING_FAILED){
		return INTERNAL_SERVER_ERROR;
	}

	strcpy((char *)transactionDB[transData->transactionSequenceNumber].transStateENUM, (const char*)"APPROVED");
	return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference){

	for(Account_Num = 0; Account_Num < DBMAX; Account_Num++){

		if(strcmp((char*)cardData->primaryAccountNumber,
				(const char*)accountReference[Account_Num].primaryAccountNumber) == 0){

			DPRINTF("Account Valid\n");
			return SERVER_OK;
		}
	}

	DPRINTF("Account Not Found\n");
	// Transaction_State = FRAUD_CARD;
	// strcpy((char *)TransData->transStateENUM, (const char*)"FRAUD_CARD");
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference){

	if(accountReference[Account_Num].state == BLOCKED){
		DPRINTF("Account is Blocked\n");
		// Transaction_State = DECLINED_STOLEN_CARD;
		return BLOCKED_ACCOUNT;
	}
	//DPRINTF("Account is Still Running\n");
	return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference){

	if(termData->transAmount <= accountReference[Account_Num].balance){
		//DPRINTF("Enough Balance\n");
		return SERVER_OK;
	}

	DPRINTF("No Enough Balance\n");
	// Transaction_State = DECLINED_INSUFFECIENT_FUND;
	return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction *transData){

	transData->transactionSequenceNumber = TransNum;

	if(transData->transactionSequenceNumber < DBMAX){

		transactionDB[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		transactionDB[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		transactionDB[transData->transactionSequenceNumber].transState = transData->transState;
		strcpy((char *)transactionDB[transData->transactionSequenceNumber].transStateENUM, (const char*)transData->transStateENUM);
		transactionDB[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber + 1;

		//DPRINTF("Done Saving\n");
		TransNum++;
		return SERVER_OK;
	}

	DPRINTF("Saving Failed\n");
	// Transaction_State = INTERNAL_SERVER_ERROR;
	return SAVING_FAILED;
}

void listSavedTransactions(void){

	// EN_transStat_t STATE;
	DPRINTF("\n#####################################\n");
	DPRINTF("Transaction Sequence Number : %d\n", transactionDB[TransNum-1].transactionSequenceNumber);
	DPRINTF("Transaction Date : %s\n", transactionDB[TransNum - 1].terminalData.transactionDate);
	DPRINTF("Transaction Amount : %.2f\n", transactionDB[TransNum-1].terminalData.transAmount);
	DPRINTF("Transaction State : %s\n",transactionDB[TransNum-1].transStateENUM);
	DPRINTF("Terminal Max Amount : %.2f\n", transactionDB[TransNum-1].terminalData.maxTransAmount);
	DPRINTF("Card holder Name: %s\n",transactionDB[TransNum - 1].cardHolderData.cardHolderName);
	DPRINTF("PAN: %s\n", transactionDB[TransNum-1].cardHolderData.primaryAccountNumber);
	DPRINTF("Card Expiration Date: %s\n", transactionDB[TransNum-1].cardHolderData.cardExpirationDate);
	DPRINTF("\n#####################################\n");
}

