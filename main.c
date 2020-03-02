#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Payment.h"

ST_transaction* transaction;
int main()
{

    printf("##This version is not working correctly##");
    fillCardData(&transaction);


    fillTerminalData(&transaction);

    saveTransactionIntoServer(&transaction);



    return 0;
}
