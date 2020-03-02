#include "Payment.h"
struct ST_accountBalance gST_accountBalance[] = {
{"123456789", "0100.00"},
{"234567891", "6000.00"},
{"567891234", "3250.25"},
{"456789123", "1500.12"},
{"258649173", "0500.00"},
{"654823719", "2100.00"},
{"971362485", "0000.00"},
{"793148625", "0001.00"},
{"123123456", "0010.12"},
{"456789321", "0000.55"}
};
static unsigned int seq =0;




void fillCardData(ST_transaction *transaction){
    printf("Please Enter Card Data:\n");
    printf("Please Enter the Card Holder Name:\n");
    gets(transaction->cardHolderData.cardHolderName);
    printf("Please Enter the Primary Account Number:\n");
    gets(transaction->cardHolderData.primaryAccountNumber);
    printf("Please card Expiry Date:\n");
    gets(transaction->cardHolderData.cardExpirationDate);
}

void fillTerminalData(ST_transaction *transaction){
    printf("Please Enter Terminal Data:\n");
    printf("Please Enter the transaction Amount:\n");
    gets(transaction->transData.transAmount);
    strcpy(transaction->transData.maxTransAmount,"5000.00");
    printf("Please Enter transaction Date:\n");
    gets(transaction->transData.transactionDate);
}

void checkAmount(ST_transaction *transaction){

    if(Check_Amount(&transaction)==DECLINED){
            transaction->transResponse.transactionStatus = DECLINED;
            /*printf("%d",transaction->transResponse.transactionStatus);*/
        printf("The transaction is DECLINED\n");
    }else{
        transaction->transResponse.transactionStatus = APPROVED;
        //printf("%d",transaction->transResponse.transactionStatus);
        printf("The transaction is APPROVED\n");
    }
}

void checkExpiryDate(ST_transaction *transaction){

if(!Check_Expiry(&transaction)){
            transaction->transResponse.transactionStatus = DECLINED;
        printf("The transaction is DECLINED\n");
    }else{
        transaction->transResponse.transactionStatus = APPROVED;
        //printf("The transaction is APPROVED\n");
    }
}

void checkBalance(ST_transaction *transaction){
    if(Check_Balance(&transaction)== DECLINED){
        transaction->transResponse.transactionStatus = DECLINED;
        /*printf("%d",transaction->transResponse.transactionStatus);*/
        printf("The transaction is DECLINED\n");
    }else{
        transaction->transResponse.transactionStatus = APPROVED;
        printf("The transaction is APPROVED\n");
    }
}

void saveTransactionIntoServer(ST_transaction *transaction){

    checkAmount(&transaction);
    if(transaction->transResponse.transactionStatus == DECLINED){
            //printf("%d",transaction->transResponse.transactionStatus);
        return;
    }
    checkExpiryDate(&transaction);
    if(transaction->transResponse.transactionStatus == DECLINED){
        return;
    }
    printf("Verifying Data from the server...\n");
    checkBalance(&transaction);
    if(transaction->transResponse.transactionStatus == DECLINED){
        return;
    }else{
        transaction->transResponse.receiptReferenceNumber = seq;
        seq++;
        return;
    }
}







EN_transStat Check_Expiry(ST_transaction *transaction){
if(transaction->transData.transactionDate[8]<transaction->cardHolderData.cardExpirationDate[3]){
    return APPROVED;
}else if (transaction->transData.transactionDate[8]==transaction->cardHolderData.cardExpirationDate[3]){
    if (transaction->transData.transactionDate[9]<transaction->cardHolderData.cardExpirationDate[4]){
     return APPROVED;
    }else if(transaction->transData.transactionDate[9]==transaction->cardHolderData.cardExpirationDate[4]){
        if(transaction->transData.transactionDate[3]<transaction->cardHolderData.cardExpirationDate[0]){
            return APPROVED;
        }else if(transaction->transData.transactionDate[3]==transaction->cardHolderData.cardExpirationDate[0]){
            if(transaction->transData.transactionDate[4]<transaction->cardHolderData.cardExpirationDate[1]){
                return APPROVED;
            }else if(transaction->transData.transactionDate[4]==transaction->cardHolderData.cardExpirationDate[1]){
                return APPROVED;
            }else {
            return APPROVED;
            }
        }else{
        return DECLINED;
        }
    }else{
    return DECLINED;
    }
}else{
    return DECLINED;
}
}
EN_transStat Check_Amount(ST_transaction *transaction){
    unsigned char i;
    //printf("%s %s",transaction->transData.maxTransAmount,transaction->transData.transAmount);
    for(i=0;i<8;i++){
        if(transaction->transData.maxTransAmount[i]< transaction->transData.transAmount[i]){
                //printf("de");
            return DECLINED;
        }else if(transaction->transData.maxTransAmount[i]> transaction->transData.transAmount[i]){
            return APPROVED;
        }
    }
    return APPROVED;
}
EN_transStat Check_Balance(ST_transaction *transaction){
    unsigned char i;
    for(i=0;i<10;i++){

        if(!strcmp(transaction->cardHolderData.primaryAccountNumber,gST_accountBalance[i].primaryAccountNumber)){
            if(strcmp(transaction->transData.transAmount,gST_accountBalance[i].balance)>0){
                /*declined*/
                return DECLINED;
                break;
            }else{
                return APPROVED;
            }
        }
    }
    if(i<10){
        /*found id*/
    }else{
        return DECLINED;
    }


}
