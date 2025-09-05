#include <stdio.h>   
#include <stdlib.h>  
#include <stdbool.h> 
#include <string.h> 
#include <ctype.h>

void init();
int load();
int execute();
int mos(int op_add);
int allocate();
int addressmap(int va);


struct PCB
{
    int job_id;
    int TTL;
    int TLL;
    int TTC;
    int LLC;
};
struct PCB P;


char IR[4];
char R[4];
int IC, SI;
bool toggle;
char M[300][4];
int ptr;
bool visited[30];
int PI;
int TI;
int EM;
FILE *input;   
FILE *output;  


int main()
{
    input = fopen("input2.txt", "r");   
    output = fopen("output2.txt", "w");
    load();                              
    return 0;
}


void init()
{
    int i, j;
    for (i = 0; i < 300; i++)
    {
        for (j = 0; j < 4; j++)
        {
            M[i][j] = ' ';
        }
    }
    for (i = 0; i < 4; i++)
    {
        IR[i] = ' ';
        R[i] = ' ';
    }
    IC = 0;
    toggle = false;
    ptr = 0;
}


int allocate()
{
    return (rand() % 30);
}


int addressmap(int va)
{
    int pte = ptr * 10 + va / 10;
    int add;
    add = (M[pte][2] - '0') * 10 + (M[pte][3] - '0');
    return add * 10;
}


int mos(int op_add)
{
    if (SI == 1)
    {
        char buffer[100];
        fgets(buffer, 100, input);
        if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            return 1;
        }
        int frameno = allocate();
        while (visited[frameno] != false)
        {
            frameno = allocate();
        }
        visited[frameno] = true;
        int add = ptr * 10 + op_add / 10;
        M[add][0] = ' ';
        M[add][1] = ' ';
        M[add][2] = (frameno / 10) + '0';
        M[add][3] = (frameno % 10) + '0';
        int j = frameno * 10;
        int k = 0;
        for (int i = 0; i < 40 && i < strlen(buffer); i++)
        {
            M[j][k++] = buffer[i];
            if (k == 4)
            {
                k = 0;
                j++;
            }
        }
    }
    else if (SI == 2)
    {
        char out[100];
        int pte = ptr * 10 + op_add / 10;
        if (M[pte][0] == '*')
        {
            PI = 3;
            return 6;
        }
        int frameno = (M[pte][2] - '0') * 10 + (M[pte][3] - '0');
        int add = frameno * 10;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                out[i * 4 + j] = M[add][j];
            }
            add++;
        }
        out[40] = '\0';
        fprintf(output, "%s\n", out);
        P.LLC++;
    }
    else if (SI == 3)
    {
       
        if (P.TTC > P.TTL)
        {
            TI = 2;
        }
        else
        {
            return 0;
        }
    }
    if (TI == 2)
    {
        return 3;
    }
}


int execute()
{
    int RA = addressmap(0);
    int count = 0;
    while (1)
    {
        if (P.LLC > P.TLL)
        {
            return 2;
        }
        if (P.TTC > P.TTL)
        {
            TI = 2;
            int flag = mos(0);
            return flag;
        }
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[RA][i];
        }
        RA++;
        count++;
        if (count == 11)
        {
            int pte = ptr * 10 + 1;
            int frameno = (M[pte][2] - '0') * 10 + (M[pte][3] - '0');
            RA = frameno * 10;
        }
        if (IR[0] != 'H')
        {
            if (!isdigit(IR[2]) || !isdigit(IR[3]))
            {
                PI = 2;
                return 5;
            }
        }
        if (IR[0] == 'L' && IR[1] == 'R')
        {
            int op_add, offset;
            op_add = (IR[2] - '0') * 10;
            offset = IR[3] - '0';
            int pte = ptr * 10 + op_add / 10;
            if (M[pte][0] == '*')
            {
                PI = 3;
                return 6;
            }
            int add = (M[pte][2] - '0') * 10 + (M[pte][3] - '0');
            for (int i = 0; i < 4; i++)
            {
                R[i] = M[add * 10 + offset][i];
            }
            P.TTC++;
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int op_add, offset;
            op_add = (IR[2] - '0') * 10;
            offset = IR[3] - '0';
            int pte = ptr * 10 + op_add / 10;
            int add = (M[pte][2] - '0') * 10 + (M[pte][3] - '0');
            for (int i = 0; i < 4; i++)
            {
                M[add * 10 + offset][i] = R[i];
            }
            P.TTC = P.TTC + 2;
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int op_add, offset;
            op_add = (IR[2] - '0') * 10;
            offset = IR[3] - '0';
            int pte = ptr * 10 + op_add / 10;
            if (M[pte][0] == '*')
            {
                PI = 3;
                return 6;
            }
            int add = (M[pte][2] - '0') * 10 + (M[pte][3] - '0');
            int flag = 0;
            for (int i = 0; i < 4; i++)
            {
                if (R[i] != M[add * 10 + offset][i])
                    flag = 1;
            }
            if (flag == 1)
            {
                toggle = false;
            }
            else
            {
                toggle = true;
            }
            P.TTC++;
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            int op_add, offset, inst_no;
            op_add = (IR[2] - '0') * 10;
            offset = IR[3] - '0';
            if (toggle == true)
            {
                int pte = ptr * 10 + 1;
                RA = (((M[pte][2] - '0') * 10 + (M[pte][3] - '0')) * 10) + offset;
                count = 0;
            }
            P.TTC++;
        }
        else if (IR[0] == 'G' && IR[1] == 'D')
        {
            int op_add = (IR[2] - '0') * 10 + (IR[3] - '0');
            SI = 1;
            int flag = mos(op_add);
            if (flag == 1)
            {
                return 1;
            }
            P.TTC = P.TTC + 2;
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            int op_add = (IR[2] - '0') * 10 + (IR[3] - '0');
            SI = 2;
            int flag = mos(op_add);
            if (flag == 6)
            {
                PI = 3;
                return 6;
            }
            P.TTC++;
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            P.TTC++;
            int flag = mos(0);
            if (flag != 0)
            {
                return flag;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            PI = 1;
            return 4;
        }
    }
}


int load()
{
    char buffer[100];
    char line[5];
    int flag;
    while (fgets(buffer, 100, input) != NULL)
    {
        strncpy(line, buffer, 4);
        line[4] = '\0';
        if (strcmp(line, "$AMJ") == 0)
        {
            init();
            ptr = allocate();
            for (int i = ptr * 10; i < ptr * 10 + 10; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    M[i][j] = '*';
                }
            }
            visited[ptr] = true;
            char jobid_str[5], TTL_str[5], TLL_str[5];
            strncpy(jobid_str, buffer + 4, 4);
            jobid_str[4] = '\0';
            strncpy(TTL_str, buffer + 8, 4);
            TTL_str[4] = '\0';
            strncpy(TLL_str, buffer + 12, 4);
            TLL_str[4] = '\0';
            P.job_id = atoi(jobid_str);
            P.TTL = atoi(TTL_str);
            P.TLL = atoi(TLL_str);
            P.LLC = 0;
            P.TTC = 0;
        }
        else if (strcmp(line, "$DTA") == 0)
        {
            flag = execute();
        }
        else if (strcmp(line, "$END") == 0)
        {
            if (flag == 0)
            {
                printf("Memory Print:\n");
                for (int i = 0; i < 150; i++)
                {
                    printf("M[%d]:%c%c%c%c\t\tM[%d]:%c%c%c%c\n", i,
                           M[i][0], M[i][1], M[i][2], M[i][3],
                           i + 150, M[i + 150][0], M[i + 150][1], M[i + 150][2], M[i + 150][3]);
                }
                printf("*HALT*\n");
            }
            else if (flag == 1)
            {
                printf("Error Code:1 Out of Data.\n");
                fprintf(output, "Program Terminated Abnormally.\n");
                fprintf(output, "Error Code:1 Out of Data.\n");
            }
            else if (flag == 2)
            {
                printf("Error Code:2 Line Limit Exceeded.\n");
                fprintf(output, "Program Terminated Abnormally.\n");
                fprintf(output, "Error Code:2 Line Limit Exceeded.\n");
            }
            else if (flag == 3)
            {
                printf("Error Code:3 Time Limit Exceeded.\n");
                fprintf(output, "Program Terminated Abnormally.\n");
                fprintf(output, "Error Code:3 Time Limit Exceeded.\n");
            }
            else if (flag == 4)
            {
                printf("Error code:4 Operation Code Error.\n");
                fprintf(output, "Program Terminated Abnormally.\n");
                fprintf(output, "Error Code:4 Operation Code Error.\n");
            }
            else if (flag == 5)
            {
                printf("Error Code:5 Operand Error.\n");
                fprintf(output, "Program Terminated Abnormally.\n");
                fprintf(output, "Error Code:5 Operand Error.\n");
            }
            else if (flag == 6)
            {
                printf("Error Code:6 Invalid Page Fault.\n");
                fprintf(output, "Program Terminated Abnormally.\n");
                fprintf(output, "Error Code:6 Invalid Page Fault.\n");
            }
            printf("Toggle:%d\tTTL:%d\tTTC:%d\tLLC:%d\tTLL:%d\n", toggle, P.TTL, P.TTC, P.LLC, P.TLL);
            fprintf(output, "Toggle:%d\tTTL:%d\tTTC:%d\tLLC:%d\tTLL:%d\n\n\n", toggle, P.TTL, P.TTC, P.LLC, P.TLL);
        }
        else
        {
            int frameno = allocate();
            while (visited[frameno] != false)
            {
                frameno = allocate();
            }
            visited[frameno] = true;
            int add = ptr * 10;
            while (M[add][0] != '*')
            {
                add++;
            }
            M[add][0] = ' ';
            M[add][1] = ' ';
            M[add][2] = (frameno / 10) + '0';
            M[add][3] = (frameno % 10) + '0';
            int k = 0;
            for (int i = frameno * 10; i < frameno * 10 + 10 && k < strlen(buffer); i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (buffer[k] == 'H')
                    {
                        M[i][j] = buffer[k++];
                        break;
                    }
                    else
                    {
                        M[i][j] = buffer[k++];
                    }
                }
            }
        }
    }
    fclose(input);  
    fclose(output); 
}
