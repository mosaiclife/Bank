//
//  main.c
//  Bank
//
//  Created by EunPyo Hong on 11. 12. 28..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_ACCOUNT 10

void startActivity();
int loginAccount();
int showMenu();
void putMoney();
void getMoney();
void sendMoney();
void checkMoney();
void createAccount();
int deleteAccount();
int checkCurrentAccount();
int findAccount(char ori_account[20]);
void readFile();
void saveFile();

char* inputAccount();
char* inputPw();

int current_account=0;  // 현재 사용하고 있는 계정

struct account
{
    char name[20];
    char phone[20];
    char pw[10];
    char account[20];
    int money;
};

struct account account[MAX_ACCOUNT];

int main (int argc, const char * argv[])
{
    
    //    int choice, n;
    int n, i;
    
    readFile();
    
    
    
START_POINT:
    
    startActivity();  // 로그인 or 계좌생성해서 작업할 계정 선택
    
    while (1) // 입금 출금 메뉴
    {
        //        choice = showMenu();  // 메뉴 출력
        
        switch (showMenu()) 
        {
            case 1:
                putMoney();
                checkMoney();
                break;
            case 2:
                getMoney();
                checkMoney();
                break;
            case 3:
                sendMoney();
                break;
            case 4:
                checkMoney();
                break;
            case 5:
                n = deleteAccount();
                if(n == 1)
                    goto START_POINT;
                break;
            case 6:
                goto START_POINT;
                break;
            case 7:
                printf("감사합니다");
                saveFile();
                exit(0);
                break;
            default:
                printf("적절한 메뉴를 선택하세요\n\n");
                break;
        }
    }
    
    return 0;
}

// 시작화면
void startActivity()
{
    
    int n, choice;
    n = 0;
    while (1) 
    {
        //        choice = 0;
        
        printf("1.로그인, 2.계좌생성, 3.종료\n");
        printf("선택 : ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
                n = loginAccount();
                if(n == 1)
                    return;
                break;
            case 2:
                createAccount();
                break;
            case 3:
                saveFile();
                printf("감사합니다");
                exit(0);
                break;
            default:
                printf("적절한 메뉴를 선택하세요\n\n");
                break;
        }
        
    }
    
    
}

// 로그인
int loginAccount()
{
    char input_account[20];
    char input_pw[10];
    char* temp;
    
    int i, choice, stat = 0;
    
    while(choice != 2){
        temp = inputAccount();
        strcpy(input_account, temp);
        
        temp = inputPw();
        strcpy(input_pw, temp);
        
        //printf("%d %d\n\n", strcmp(account[0].account, input_account), strcmp(account[0].pw, input_pw));
        
        for(i = 0; i < MAX_ACCOUNT; i++){
            if(!strcmp(account[i].account, input_account))
            {
                stat = 1;   //일치하는 계좌가 있다는 상태 표시
                
            INPUT_PASSWORD:
                if(!strcmp(account[i].pw, input_pw))
                {
                    printf("환영합니다! %s 고객님\n\n", account[i].name);
                    current_account = i;
                    return 1;
                }
                else
                {
                    printf("비밀 번호가 일치하지 않습니다.\n");
                    printf("1.비밀번호 재입력, 2.돌아가기\n선택 : ");
                    scanf("%d", &choice);
                    
                    
                    switch (choice) {
                        case 1:
                            goto INPUT_PASSWORD;
                            break;
                        case 2:
                            return 0;
                            break;
                        default:
                            printf("적절한 메뉴를 선택하세요\n");
                            break;
                    }
                    break;
                }
            }
            else if(i == MAX_ACCOUNT - 1){
                printf("일치하는 계좌가 없습니다.\n");
            }
        }
        if(stat == 0)
        {
            printf("1.계좌번호 재입력, 2. 돌아가기\n선택 : ");
            scanf("%d", &choice);
        }
    }
    
    return 0;
    
}

// 계좌 생성(이름, 전화번호, 계좌번호, 비밀번호)
void createAccount()
{
    char input_name[10];
    char input_phone[20];
    char input_pw[10];
    char input_account[20];
    int input_money;
    
    current_account = checkCurrentAccount();  // 사용할수 있는 빈 계정 찾기
    
    if(current_account == -1)
    {
        printf("빈공간이 없습니다.");
        return 0;
    }
    
    gets(input_name);
    
    printf("이름 : ");
    //    fflush(stdin);
    gets(input_name);
    strcpy(account[current_account].name, input_name);
    
    printf("전화번호 : ");
    //    fflush(stdin);
    gets(input_phone);
    strcpy(account[current_account].phone, input_phone);
    
    printf("계좌번호 : ");
    //    fflush(stdin);
    gets(input_account);
    strcpy(account[current_account].account, input_account);
    
    printf("비밀번호 : ");
    //    fflush(stdin);
    gets(input_pw);
    strcpy(account[current_account].pw, input_pw);
    
    account[current_account].money = 0;
    
    printf("\n계좌생성이 완료되었습니다.\n");
    
    return;
}

// 로그인 후 메뉴보기
int showMenu()
{
    int choice;
    printf("1.입금, 2.출금, 3.송금, 4.조회, 5.삭제, 6.로그아웃, 7.종료\n");
    printf("선택 : ");
    scanf("%d", &choice);
    
    return choice;
}

// 입금
void putMoney()
{
    int temp_money;
    
    printf("입금할 금액 입력");
    scanf("%d", &temp_money);
    
    account[current_account].money += temp_money;
}

// 출금
void getMoney()
{
    int temp_money;
    
    printf("출금할 금액 입력");
    scanf("%d", &temp_money);
    
    account[current_account].money -= temp_money;    
}

// 송금
void sendMoney()
{
    int input_send_money, target_account;   // 보낼 돈, 보낼 사람의 배열안의 순번
    char input_account[20];
    char check;
    
INPUT_TARGET_ACCOUNT:
    
    printf("받는 분의 계좌번호 입력 : ");
    gets(input_account);
    gets(input_account);
    
    target_account = findAccount(input_account);    //받을 사람의 계좌 배열 인덱스
    
    if(target_account == -1)
    {
        printf("존재하지 않는 계좌번호 입니다.\n");
        return;
    }
    
    printf("받는 분의 계좌 정보\n");
    printf("이름 : %s\n전화번호 : %s\n계좌번호 : %s\n", account[target_account].name, account[target_account].phone, account[target_account].account);
    
    
    
    while(1)
    {
        printf("받는 분의 정보가 맞습니까?(Y/N)");
        scanf("%c", &check);
        
        if(check == 'Y' || check == 'y')
            break;
        else if(check == 'N' || check == 'n'){
            goto INPUT_TARGET_ACCOUNT;
        }
        else
        {
            printf("적절한 메뉴를 선택해 주세요\n");
        }
    }
    
    printf("송금할 금액 입력 : ");
    scanf("%d", &input_send_money);
    
    
    account[current_account].money -= input_send_money;
    account[target_account].money += input_send_money;
    
    printf("송금이 성공적으로 완료되었습니다.\n");
    printf("이체 전 금액 : %d\n이체 금액 : %d\n이체 후 금액 : %d\n", account[current_account].money, input_send_money, account[target_account].money);
    
}

// 잔액조회
void checkMoney()
{
    printf("지금 남음 잔액은 : %d원 입니다.\n", account[current_account].money);
}

// 계좌 삭제
int deleteAccount()
{
    char input_pw[10];
    int i, j, k;
    
    printf("비밀번호 입력 : ");
    gets(input_pw);
    gets(input_pw);
    
    if(!strcmp(account[current_account].pw, input_pw)){
        
        for(i = current_account; i < MAX_ACCOUNT - 1; i ++)
        {
            j = i+1;
            strcpy(account[i].name, account[j].name);
            strcpy(account[i].phone, account[j].phone);
            strcpy(account[i].account, account[j].account);
            strcpy(account[i].pw, account[j].pw);
            account[i].money = account[j].money;
        }
        
        strcpy(account[MAX_ACCOUNT].name, "");
        strcpy(account[MAX_ACCOUNT].phone, "");
        strcpy(account[MAX_ACCOUNT].account, "");
        strcpy(account[MAX_ACCOUNT].pw, "");
        account[MAX_ACCOUNT].money = 0;
        
        
        return 1;
    }
    else
        printf("비밀번호가 일치하지 않습니다.\n");
    
    return 0;
}

// 계좌번호 입력받는 함수
char* inputAccount()
{
    static char input_account[20];
    
    printf("계좌번호 입력 : ");
    gets(input_account);
    gets(input_account);
    
    return input_account;
}

//비밀번호 입력받는 함수
char* inputPw()
{
    static char input_pw[10];
    
    printf("비밀번호 입력 : ");
    fflush(stdin);
    gets(input_pw);
    
    return input_pw;
}

// 현재 빈 계좌 조회
int checkCurrentAccount(){
    int i;
    
    
    for(i=0; i<MAX_ACCOUNT; i++){
        if(!strcmp(account[i].account, ""))
            return i;
    }
    
    return -1;
}

// 계좌번호 찾기
int findAccount(char ori_account[20])
{
    int i;
    
    for(i = 0; i < MAX_ACCOUNT; i++)
    {
        if(!strcmp(account[i].account, ori_account))
            return i;
    }
    return -1;
}

void readFile()
{
    FILE* file;
    int start, end, money;
    int i, j;
    char ch, temp[100];
    
    file = fopen("/Users/mosaiclife/Documents/XCode/C/bankdata.data", "rb");
    if(file == NULL)
    {
        printf("file open error!\n");
        return 1;
    }
    
    fseek(file, 0, SEEK_SET);
    start = 0, end = 0;
    
    j = 0, i = 0;
    
    while(1)
    {
        end++;
        ch = fgetc(file);
        if(feof(file) != 0)
        {
            fseek(file, (end - start - 1) * -1, SEEK_CUR);
            fgets(temp, end - start, file);
            break;
        }
        else if(ch == '|')
        {
            j++;
            fseek(file, (end - start) * -1, SEEK_CUR);
            fgets(temp, end - start, file);
            fseek(file, 1, SEEK_CUR);
            printf("%s\n", temp);
            
            switch (j) {
                case 2:
                    strcpy(account[i].name, temp);
                    break;
                case 3:
                    strcpy(account[i].phone, temp);
                    break;
                case 4:
                    strcpy(account[i].account, temp);
                    break;
                case 5:
                    strcpy(account[i].pw, temp);
                    break;
                case 6:
                    money = atoi(temp);
                    account[i].money = money;
                    break;
                default:
                    break;
            }
            
            start = end;
        }
        else if(ch == '\n')
        {
            j = 0;
            i++;
        }
    }
    
    if(fclose(file))
    {
        printf("file close error\n");
        return 1;
    }
    
}

void saveFile()
{
    FILE* file;
    int i, max;
    char temp[100];
    
    file = fopen("/Users/mosaiclife/Documents/XCode/C/bankdata.data", "wb");
    if(file == NULL)
    {
        printf("file open error!\n");
        return 1;
    }
    
    max = checkCurrentAccount();
    
    for(i=0; i<max; i++)
    {
        fputc('|', file);
        fputs(account[i].name, file);
        fputc('|', file);
        fputs(account[i].phone, file);
        fputc('|', file);
        fputs(account[i].account, file);
        fputc('|', file);
        fputs(account[i].pw, file);
        fputc('|', file);
        
        
        sprintf(temp, "%d", account[i].money);
        fputs(temp, file);
        fputc('|', file);
        fputc('\n', file);
    }
    
    
    if(fclose(file))
    {
        printf("file close error\n");
        return 1;
    }
}