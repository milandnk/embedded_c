// #include <stdio.h>
// #include <string.h>
// #include<stdlib.h>
// int main() {
//     char str[] = "milan pipaliya";
//     int n1 = strlen(str);
//     puts(str);

//     char str1[] = "rameshbhai ";
//     int n2 = strlen(str1);
//     puts(str1);
//     int num;
//      printf("Enter num and which place to add:");
//     scanf("%d", &num);
//     char rep[n1 - num + 1];
    
//     realloc(str,sizeof(char)*(n1+n2));

//     for (int i = 0; i < n1 - num; i++) {
//         rep[i] = str[num + i];
//     }
//     // rep[n1 - num] = '\0'; 

//     for (int i = 0; i < n2; i++) {
//         str[num + i] = str1[i];
//     }

//     for (int i = 0; i < n1 - num; i++) {
//         str[num + n2 + i] = rep[i];
//     }
//     str[n1 + n2] = '\0';

//     puts(str);

//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #include<stdlib.h>
// int main() {

//     char str[] = "milan pipaliya";
//     int n1 = strlen(str);
//     puts(str);

//     char str1[] = "rameshbhai ";
//     int n2 = strlen(str1);
//     puts(str1);
//     int num;
//     char lstr[n1+n2-1];
//     strcpy(lstr,str);
//     printf("Enter position to add string: ");
//     scanf("%d", &num);
    
    
//     if (num < 0 || num > n1) {
//         printf("Invalid position.\n");
//         return 1;
//     }

//     memcpy(lstr+n1+1,lstr+num,n1+num);
//     //realloc(str,sizeof(char)*(n1+n2));
//     for (int i = num ; i < n1-num; i++) {
//         lstr[num+n2+i]=lstr[i];
//     }

//     for (int i = 0; i < n2; i++) {
//         lstr[num + i-1] = str1[i];
//     }

   
//     puts(lstr);

//     return 0;
// }

#include<stdio.h>
#include <string.h>
int main(){
    char str1[50];
    char str2[50];
    char str3[50];
    int n;
    printf("enter str1:");
    gets(str1);
    printf("enter str2:");
    gets(str2);
    printf("enter position:");
    scanf("%d",&n);
    // for (int i = 0; i <= strlen(str1)-n; i++)
    // {
    //     str3[i]=str1[n+i];
    // }
    memmove(str3,str1+n-1,strlen(str1)-n);
    printf("%s\n",str3);
    // for (int i = 0; i <= strlen(str2); i++)
    // {
    //     str1[n+i-1]=str2[i];
    // }
    memmove(str1+n,str2,strlen(str2));
    printf("%s\n",str1);
    // for (int i = n-1+strlen(str2),j=0; i <= n-1+strlen(str2)+strlen(str3); i++,j++)
    // {
    //     str1[i]=str3[j];
    // }
    memmove(str1+strlen(str2)+n,str3,strlen(str3));
    printf("%s\n",str1);
return 0;
}