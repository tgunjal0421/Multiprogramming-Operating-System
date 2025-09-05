#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void init_Memory();
void init_Buffer();
void Load_Instructions(int I,int n);
void read_Instructions_Input();
void read_Data_Input();
void ExecuteUserProgram();
void mos();
void LOAD();

char IR[4];
char R[4];
int  IC,SI;
bool Toggle;
char Memory[100][4];
char Buffer[40];
int count = 0; int total_p = 0; int curr_pid = 0;
int line_count = 0;

int main(){
    LOAD();
    return 0;
}

void LOAD(){
    int i = 0;
    FILE* input; 
    input = fopen("input.txt", "r");
    while (fgets(Buffer,18,input))
    {
        if (!strncmp(Buffer,"$AMJ",4))
        {
            total_p++;
            init_Buffer();
        }
    }
    while (curr_pid <= total_p)
    {
        line_count = 0;
        init_Buffer();
        init_Memory();
        read_Instructions_Input();
        ExecuteUserProgram();
        curr_pid++;
    }
    fclose(input);
}

void init_Buffer(){
    int i;
    for (i = 0; i < 40; i++)
    {
        Buffer[i] = ' ';
    }
}

void init_Memory(){
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Memory[i][j] = ' ';
        }
    }
}

void read_Instructions_Input(){
    FILE* input;
    input = fopen("input.txt", "r");
    char ch; int inst = 0; int i = 0; int j = 0;
    init_Buffer();
    if (curr_pid != 0)
    {
        int I;
        for ( I = 0; I < curr_pid; I++)
        {
            while (fgets(Buffer,9,input))
            { 
                if (!strncmp(Buffer,"$END",4))
                {
                    break;
                }
            }
            init_Buffer();
        }
        fgetc(input);
    }
    init_Buffer();
    fgets(Buffer, 18, input);
    if (!strncmp(Buffer, "$AMJ", 4))
    {
        inst = 10 * (Buffer[10] - 48) + (Buffer[11] - 48); 
        init_Buffer();
    }
    while (i < 40)
    {
        if (inst < 10)
        {
            for (j = 0; j < (inst - 1) * 4; j++)
            {
                Buffer[j] = fgetc(input);
                printf("%c",Buffer[j]);
                
            }
            printf("\n");
            ch = fgetc(input);
            if (ch == 'H')
            {
                Buffer[j] = ch;
                Buffer[j + 1] = ' ';
                Buffer[j + 2] = ' ';
                Buffer[j + 3] = ' ';
                printf("%c",Buffer[j]);
                break;
            }
            else
            {
                int k = 0;
                while (k < 4)
                {
                    if (ch != '\n')
                    {
                        Buffer[j] = ch;
                         
                        j++;   
                    }
                    ch = fgetc(input);
                    k++;
                }
                Load_Instructions(0, 10);
                break;
            } 
        }
        else if (inst >= 10)
        {
            Buffer[i] = fgetc(input);
            
            
            if (Buffer[i] == 'H')
            {
                Buffer[i + 1] = ' ';
                Buffer[i + 2] = ' ';
                Buffer[i + 3] = ' ';
                break;
            }
            
            i++;
        }
    } 
    Load_Instructions(0, 10);
    

    if (inst > 10)
    {
        init_Buffer();
        i = 0;
        while (i < 40)
        {
            Buffer[i] = fgetc(input);
            
            if (Buffer[i] == '\n')
            {
                Buffer[i] = ' ';
                i--;    
            }
            else if (Buffer[i] == 'H')
            {
                Buffer[i + 1] = ' ';
                Buffer[i + 2] = ' ';
                Buffer[i + 3] = ' ';
                i = i + 3;
            }
            else if (Buffer[i] == 'D' && Buffer[i - 1] == '$')
            {
                Buffer[i] = ' ';
                printf("%c",Buffer[i]);
                Buffer[i - 1] = ' ';
                printf("%c",Buffer[i]);
                
                break;
            }
            
            i++;
        }
       
        Load_Instructions(10,20);
        
    }
    fclose(input);
}

void Load_Instructions(int I, int n){
    int i = I;
    int k = 0;
    for (i = I; i < n; i++)
    {
        int j;
        for (j = 0; j < 4; j++)
        {
            Memory[i][j] = Buffer[k];
            k++;
        }
    }
}

void read_Data_Input(){
    char c; int i = 0; int inst = 0; count = 0;
    FILE* input;
    input = fopen("input.txt", "r");
    init_Buffer();
    if (curr_pid != 0)
    {
        for (int I = 0; I < curr_pid; I++)
        {
            while (fgets(Buffer,9,input))
            { 
                if (!strncmp(Buffer,"$END",4))
                {
                    break;
                }
            }
            init_Buffer();
        }
        fgetc(input);
    }
    init_Buffer();
    fgets(Buffer, 18, input);
    if (!strncmp(Buffer, "$AMJ", 4))
    {
        inst = 10 * (Buffer[10] - 48) + (Buffer[11] - 48);
    }
    init_Buffer();
    if (inst <= 10)
    {
        while (c != '\n')
        {
            c = fgetc(input);
            
        }
        c = fgetc(input);
        while (c != '\n')
        {
            c = fgetc(input);
            
        }
        c = fgetc(input);
        
    }
    else if (inst > 10)
    {
        while (c != '\n')
        {
            c = fgetc(input);
           
        }
        c = fgetc(input);
        
        while (c != '\n')
        {
            c = fgetc(input);
        }
        c = fgetc(input);
        
        while (c != '\n')
        {
            c = fgetc(input);
        }
        c = fgetc(input);
        
    }

    init_Buffer();
    int I;
    for (I = 0; I < line_count; I++)
        {   
            while (c != '\n')
            {   
                c = fgetc(input);   
            }
            c = fgetc(input);  
        }
       
    i = 0;
    
    while (i < 40){
        printf("%c",c);
        Buffer[i] = c;

        c = fgetc(input);
        count++;
        if (c == '\n')
        {
            break;
        }
        if (c == 'E' && Buffer[i] == '$')
        {
            Buffer[i] = ' ';
            break;
        }
        i++;
    }
    printf("\n");
    fclose(input);
}

void mos(){
    if (SI == 1)
    {
        int add;
        add = 10 * (IR[2] - 48) + (IR[3] - 48);
        read_Data_Input();
        line_count++;
        int k = 0;
        int i;
        for (i = add; i < add + (count/4) + 1; i++)
        {
            int j;
            for ( j = 0; j < 4; j++)
            {
                Memory[i][j] = Buffer[k];
                printf("%c",Memory[i][j]);
                k++;
            }
        }
        printf("\n");
    }
    else if (SI == 2)
    {
        int add;
        add = 10 * (IR[2] - 48) + (IR[3] - 48);   
        FILE* output;
        output = fopen("output.txt", "a");
        int i;
        for (i = add; i < add + (count/4) + 1; i++)
        {
            int j;
            for ( j = 0; j < 4; j++)
            {
                fputc(Memory[i][j], output);
            }
        }
        fputc('\n', output);
        fclose(output);
    }
    else if (SI == 3)
    {
        FILE* output;
        output = fopen("output.txt", "a");
        fputs("\n\n", output);
        fclose(output);
    }
}

void ExecuteUserProgram(){
    int I = 0;
    while (true)
    {
        //printf("%d\n",I);
        int j;
        for (j = 0; j < 4; j++)
        {
            IR[j] = Memory[I][j];
        }
        I++;
        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            mos();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            mos();
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            int add;
            add = 10 * (IR[2] - 48) + (IR[3] - 48);
            R[0] = Memory[add][0];
            R[1] = Memory[add][1];
            R[2] = Memory[add][2];
            R[3] = Memory[add][3];
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int add;
            add = 10 * (IR[2] - 48) + (IR[3] - 48);
            Memory[add][0] = R[0];
            Memory[add][1] = R[1];
            Memory[add][2] = R[2];
            Memory[add][3] = R[3];
            count = count + 4;
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int add; int flag = 0;
            add = 10 * (IR[2] - 48) + (IR[3] - 48);
            int i;
            for (i = 0; i < 4; i++)
            {
                if (R[i] != Memory[add][i])
                    flag = 1;
            }
            if (flag == 1)
                Toggle = false;
            else
                Toggle = true;
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            int add;
            add = 10 * (IR[2] - 48) + (IR[3] - 48);
            if (Toggle == true)
                I = add;
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            mos();
            break;
        }
    }
}