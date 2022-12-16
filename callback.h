#include "MQTTClient.h"

volatile MQTTClient_deliveryToken deliveredtoken;

void aiTurn()
{
    int temp;
    char *sInt;
    MQTTClient_deliveryToken token;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    srand(time(0));
    do
    {
        temp = rand() % 9;
        *sInt = temp+0;
        pubmsg.payload = sInt;
        pubmsg.payloadlen = strlen(sInt)+1;
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        if(gameBoard[temp] != 'X' && gameBoard[temp] != 'O')
        {
            MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
            gameBoard[temp] = 'O';
            count = 0;
        }
    } while (count == 1);
    

}
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = message->payload;
    curmsg = message->payload;
    printf("%s", curmsg);

    if(ai == false && player == false)
    {
        if(*curmsg == 'a')
        {
            printf("\nGame set to Player VS AI...\n");
            ai = true;
        }
        else if (*curmsg == 'p')
        {
            printf("\nGame set to Player VS Player");
            player = true;
        }
    }
    else if(count == 0)
    {
        if(*curmsg == '1')
        {
            if(gameBoard[0] == 'X' || gameBoard[0] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[0] = 'X';
                printf("%c", gameBoard[0]);
                count++;
            }
        }
        if(*curmsg == '2')
        {
            if(gameBoard[1] == 'X' || gameBoard[1] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[1] = 'X';
                printf("%c", gameBoard[1]);
                count++;
            }
        }
        if(*curmsg == '3')
        {
            if(gameBoard[2] == 'X' || gameBoard[2] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[2] = 'X';
                printf("%c", gameBoard[2]);
                count++;
            }
        }
        if(*curmsg == '4')
        {
            if(gameBoard[3] == 'X' || gameBoard[3] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[3] = 'X';
                printf("%c", gameBoard[3]);
                count++;
            }
        }
        if(*curmsg == '5')
        {
            if(gameBoard[4] == 'X' || gameBoard[4] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[4] = 'X';
                printf("%c", gameBoard[4]);
                count++;
            }
        }
        if(*curmsg == '6')
        {
            if(gameBoard[5] == 'X' || gameBoard[5] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[5] = 'X';
                printf("%c", gameBoard[5]);
                count++;
            }
        }
        if(*curmsg == '7')
        {
            if(gameBoard[6] == 'X' || gameBoard[6] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[6] = 'X';
                printf("%c", gameBoard[6]);
                count++;
            }
        }
        if(*curmsg == '8')
        {
            if(gameBoard[7] == 'X' || gameBoard[7] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[7] = 'X';
                printf("%c", gameBoard[7]);
                count++;
            }
        }
        if(*curmsg == '9')
        {
            if(gameBoard[8] == 'X' || gameBoard[8] == 'O')
            {
                printf("Space already taken...");
            }
            else
            {
                gameBoard[8] = 'X';
                printf("%c", gameBoard[8]);
                count++;
            }
        }
    }
    else if (count == 1 && player == true)
    {
        printf("\nIt is not your turn...\n");
    }
    putchar('\n');
    showGameboard();
    if(ai == true && count == 1)
    {
        aiTurn();
        showGameboard();
    }
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}