#ifndef __Payment_H__
#define __Payment_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct ST_cardData
{
unsigned char cardHolderName[25];
unsigned char primaryAccountNumber[19];
unsigned char cardExpirationDate[6];
}ST_cardData;


typedef struct ST_terminalData
{
unsigned char transAmount[8];
unsigned char maxTransAmount[8];
unsigned char transactionDate[11];
}ST_terminalData;






typedef enum EN_transStat
{
DECLINED,
APPROVED
}EN_transStat;



typedef struct ST_serverData
{
EN_transStat transactionStatus;
unsigned int receiptReferenceNumber;
}ST_serverData;

typedef struct ST_accountBalance
{
unsigned char primaryAccountNumber[19];
unsigned char balance[8];
}ST_accountBalance;

typedef struct ST_transaction
{
ST_cardData cardHolderData;
ST_terminalData transData;
ST_serverData transResponse;
}ST_transaction;



void fillCardData(ST_transaction *transaction);
/*It fills the card data structure into the ST_transaction structure*/
void checkAmount(ST_transaction *transaction);
/*It reads the amount.
- It checks if the amount > maximum transaction Amount (5000.00)
- Then it saves the response as DECLINED and prints ”The transaction is
DECLINED”
- Else do nothing*/
void fillTerminalData(ST_transaction *transaction);
/*It fills transaction amount, maximum transaction amount and expiry date in
the ST_transaction structure.
*/
void checkExpiryDate(ST_transaction *transaction);
/*Reads the expiry and transaction dates from the transaction structure.
- It checks if the expiry date > than transaction date
- Then saves the response as DECLINED and prints ”The transaction is
DECLINED”
- Else do nothing*/
void saveTransactionIntoServer(ST_transaction *transaction);
/*- It checks for the expiry date.
- It checks for balance.
- Saves the transaction data into the server array.
*/
void checkBalance(ST_transaction *transaction);
/*It reads the primary account number from the transaction structure.
- It searches for the primary account number into the account/balance array.
- If it is not exist
Then saves the response as DECLINED and print ”The transaction is
DECLINED”
- Else it checks if the transaction amount > account balance
- Then saves the response as DECLINED and print ”The transaction is
DECLINED”
- Else saves the response as APPROVED and print ”The transaction is
APPROVED”
*/

EN_transStat Check_Expiry(ST_transaction *transaction);
EN_transStat Check_Amount(ST_transaction *transaction);
EN_transStat Check_Balance(ST_transaction *transaction);

#endif // __Payment_H__
