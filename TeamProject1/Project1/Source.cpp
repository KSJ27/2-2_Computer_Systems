#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include <float.h>

//맨 아래 메인함수에서 원하는 기능의 주석를 해제하여 실행해주세요

typedef struct BigFloat
{
    char inputNum[10000];    //입력받은 숫자 문자열
    char* intNum = 0;       //입력받은 숫자의 정수부분
    char* floatNum = 0;     //입력받은 숫자의 소수부분
    int intSize = 0;        //정수부분의 길이
    int floatSize = 0;      //소수부분의 길이
    int number[10000];       //실제 값이 저장된 int형 array
    int signCheck = 0;      //부호를 저장하는 변수: 0이면 양수, 1이면 음수
}BigFloat;

BigFloat storeNumber(BigFloat bigNumber) {

    char* token = strtok(bigNumber.inputNum, ".");

    bigNumber.intNum = token;
    token = strtok(NULL, "");
    bigNumber.floatNum = token;

    if (bigNumber.intNum[0] == '-') {
        bigNumber.signCheck = 1;
        for (int i = 0; i < strlen(bigNumber.intNum); i++) {
            bigNumber.intNum[i] = bigNumber.intNum[i + 1];
        }
    }

    bigNumber.intSize = strlen(bigNumber.intNum);
    bigNumber.floatSize = strlen(bigNumber.floatNum);

    for (int i = 0; i < 10000; i++) {
        bigNumber.number[i] = 0;
    }

    for (int i = 0; i < bigNumber.intSize; i++) {
        bigNumber.number[i] = ((int)bigNumber.intNum[i]) - 48;
    }
    for (int i = 0; i < bigNumber.floatSize; i++) {
        bigNumber.number[i + 5000] = ((int)bigNumber.floatNum[i]) - 48;
    }

    int tempNum[5000];

    for (int i = 0; i < 5000; i++) {
        tempNum[i] = 0;
    }

    for (int i = 0; i < bigNumber.intSize; i++) {
        tempNum[i + 5000 - bigNumber.intSize] = bigNumber.number[i];
    }
    for (int i = 0; i < 5000; i++) {
        bigNumber.number[i] = tempNum[i];
    }

    return bigNumber;
}

int showNumber(BigFloat bigNumber) {
    int firstIntIndex = 0;
    int lastFloatIndex = 9999;

    for (int i = 0; i < 5000; i++) {
        if (bigNumber.number[i] == 0) firstIntIndex++;
        else break;
    }

    for (int i = 9999; i > 4999; i--) {
        if (bigNumber.number[i] == 0) lastFloatIndex--;
        else break;
    }

    if (firstIntIndex == 5000) firstIntIndex = 4999;
    if (lastFloatIndex == 4999) lastFloatIndex = 5000;

    if (bigNumber.signCheck == 1) {
        printf("-");
    }

    for (int i = firstIntIndex; i < 5000; i++) {
        printf("%d", bigNumber.number[i]);
    }
    printf(".");
    for (int i = 5000; i <= lastFloatIndex; i++) {
        printf("%d", bigNumber.number[i]);
    }
    printf("\n");
    return 0;
}

int addition(BigFloat bigNumber1, BigFloat bigNumber2) {

    int result[10000];       //결과를 저장할 array
    int resultSign = 0;
    int checkBigger = 0;

    for (int i = 0; i < 10000; i++) {
        result[i] = 0;
    }
    //result의 elements를 0으로 초기화

    if (bigNumber1.signCheck == 0 && bigNumber2.signCheck == 0) {
        for (int i = 9999; i >= 0; i--) {
            if (result[i] + bigNumber1.number[i] + bigNumber2.number[i] <= 9)
                result[i] += bigNumber1.number[i] + bigNumber2.number[i];
            else {
                result[i] = (result[i] + bigNumber1.number[i] + bigNumber2.number[i]) % 10;
                result[i - 1] += 1;
            }
        }
    }
    else if (bigNumber1.signCheck == 1 && bigNumber2.signCheck == 0) {
        for (int i = 0; i < 10000; i++) {
            if (bigNumber1.number[i] > bigNumber2.number[i]) {
                checkBigger = 1;
                break;
            }
            else if (bigNumber1.number[i] < bigNumber2.number[i]) {
                checkBigger = -1;
                break;
            }
        }
        if (checkBigger == 1) {
            for (int i = 9999; i >= 0; i--) {
                if (bigNumber1.number[i] >= bigNumber2.number[i]) {
                    result[i] = bigNumber1.number[i] - bigNumber2.number[i];
                }
                else {
                    result[i] = (10 + bigNumber1.number[i]) - bigNumber2.number[i];
                    bigNumber1.number[i - 1] -= 1;
                }
            }
            resultSign = 1;
        }
        else if (checkBigger == -1) {
            for (int i = 9999; i >= 0; i--) {
                if (bigNumber2.number[i] >= bigNumber1.number[i]) {
                    result[i] = bigNumber2.number[i] - bigNumber1.number[i];
                }
                else {
                    result[i] = (10 + bigNumber2.number[i]) - bigNumber1.number[i];
                    bigNumber2.number[i - 1] -= 1;
                }
            }
            resultSign = 0;

        }
        else if (checkBigger == 0) {
            printf("[Addition Output]\n");
            printf("%d", 0);
            return 0;
        }
    }
    else if ((bigNumber2.signCheck == 1 && bigNumber1.signCheck == 0)) {

        for (int i = 0; i < 10000; i++) {
            if (bigNumber1.number[i] > bigNumber2.number[i]) {
                checkBigger = 1;
                break;
            }
            else if (bigNumber1.number[i] < bigNumber2.number[i]) {
                checkBigger = -1;
                break;
            }
        }
        if (checkBigger == 1) {
            for (int i = 9999; i >= 0; i--) {
                if (bigNumber1.number[i] >= bigNumber2.number[i]) {
                    result[i] = bigNumber1.number[i] - bigNumber2.number[i];
                }
                else {
                    result[i] = (10 + bigNumber1.number[i]) - bigNumber2.number[i];
                    bigNumber1.number[i - 1] -= 1;
                }
            }
            resultSign = 0;
        }
        else if (checkBigger == -1) {
            for (int i = 9999; i >= 0; i--) {
                if (bigNumber2.number[i] >= bigNumber1.number[i]) {
                    result[i] = bigNumber2.number[i] - bigNumber1.number[i];
                }
                else {
                    result[i] = (10 + bigNumber2.number[i]) - bigNumber1.number[i];
                    bigNumber2.number[i - 1] -= 1;
                }
            }
            resultSign = 1;
        }
        else if (checkBigger == 0) {
            printf("[Addition Output]\n");
            printf("%d", 0);
            return 0;
        }
    }
    else {
        for (int i = 9999; i >= 0; i--) {
            if (result[i] + bigNumber1.number[i] + bigNumber2.number[i] <= 9)
                result[i] += bigNumber1.number[i] + bigNumber2.number[i];
            else {
                result[i] = (result[i] + bigNumber1.number[i] + bigNumber2.number[i]) % 10;
                result[i - 1] += 1;
            }
        }
        resultSign = 1;
    }

    int firstIntIndex = 0;
    int lastFloatIndex = 9999;

    for (int i = 0; i < 5000; i++) {
        if (result[i] == 0) firstIntIndex++;
        else break;
    }

    for (int i = 9999; i > 4999; i--) {
        if (result[i] == 0) lastFloatIndex--;
        else break;
    }

    if (firstIntIndex == 5000) firstIntIndex = 4999;
    if (lastFloatIndex == 4999) lastFloatIndex = 5000;

    printf("[Addition Output]\n");

    if (resultSign == 1) {
        printf("-");
    }

    for (int i = firstIntIndex; i < 5000; i++) {
        printf("%d", result[i]);
    }

    printf(".");

    for (int i = 5000; i <= lastFloatIndex; i++) {
        printf("%d", result[i]);
    }
    return 0;
}

int subtraction(BigFloat bigNumber1, BigFloat bigNumber2) {

    int result[10000];
    int checkBigger = 0;
    int resultSign = 0;

    for (int i = 0; i < 10000; i++) {
        result[i] = 0;
    }
    //result의 elements를 0으로 초기화

    if (bigNumber1.signCheck == 0 && bigNumber2.signCheck == 0) {
        for (int i = 0; i < 10000; i++) {
            if (bigNumber1.number[i] > bigNumber2.number[i]) {
                checkBigger = 1;
                break;
            }
            else if (bigNumber1.number[i] < bigNumber2.number[i]) {
                checkBigger = -1;
                break;
            }
        }
        if (checkBigger == 1) {
            for (int i = 9999; i >= 0; i--) {
                if (bigNumber1.number[i] >= bigNumber2.number[i]) {
                    result[i] = bigNumber1.number[i] - bigNumber2.number[i];
                }
                else {
                    result[i] = (10 + bigNumber1.number[i]) - bigNumber2.number[i];
                    bigNumber1.number[i - 1] -= 1;
                }
            }
            resultSign = 0;
        }
        else if (checkBigger == -1) {
            for (int i = 9999; i >= 0; i--) {
                if (bigNumber2.number[i] >= bigNumber1.number[i]) {
                    result[i] = bigNumber2.number[i] - bigNumber1.number[i];
                }
                else {
                    result[i] = (10 + bigNumber2.number[i]) - bigNumber1.number[i];
                    bigNumber2.number[i - 1] -= 1;
                }
            }
            resultSign = 1;
        }
        else if (checkBigger == 0) {
            printf("[Subtraction Output]\n");
            printf("%d", 0);
            return 0;
        }
    }
    else if (bigNumber1.signCheck == 1 && bigNumber2.signCheck == 0) {
        for (int i = 9999; i >= 0; i--) {
            if (result[i] + bigNumber1.number[i] + bigNumber2.number[i] <= 9)
                result[i] += bigNumber1.number[i] + bigNumber2.number[i];
            else {
                result[i] = (result[i] + bigNumber1.number[i] + bigNumber2.number[i]) % 10;
                result[i - 1] += 1;
            }
        }
        resultSign = 1;
    }
    else if ((bigNumber2.signCheck == 1 && bigNumber1.signCheck == 0)) {
        for (int i = 9999; i >= 0; i--) {
            if (result[i] + bigNumber1.number[i] + bigNumber2.number[i] <= 9)
                result[i] += bigNumber1.number[i] + bigNumber2.number[i];
            else {
                result[i] = (result[i] + bigNumber1.number[i] + bigNumber2.number[i]) % 10;
                result[i - 1] += 1;
            }
        }
        resultSign = 0;
    }
    else { //둘다 음수인 경우
        for (int i = 0; i < 10000; i++) {
            if (bigNumber1.number[i] > bigNumber2.number[i]) {
                checkBigger = 1;
                break;
            }
            else if (bigNumber1.number[i] < bigNumber2.number[i]) {
                checkBigger = -1;
                break;
            }
        }
        if (checkBigger == 1) {
            for (int i = 9999; i >= 0; i--) {
                if (bigNumber1.number[i] >= bigNumber2.number[i]) {
                    result[i] = bigNumber1.number[i] - bigNumber2.number[i];
                }
                else {
                    result[i] = (10 + bigNumber1.number[i]) - bigNumber2.number[i];
                    bigNumber1.number[i - 1] -= 1;
                }
            }
            resultSign = 1;
        }
        else if (checkBigger == -1) {
            for (int i = 9999; i >= 0; i--) {
                if (bigNumber2.number[i] >= bigNumber1.number[i]) {
                    result[i] = bigNumber2.number[i] - bigNumber1.number[i];
                }
                else {
                    result[i] = (10 + bigNumber2.number[i]) - bigNumber1.number[i];
                    bigNumber2.number[i - 1] -= 1;
                }
            }
            resultSign = 0;
        }
        else if (checkBigger == 0) {
            printf("[Subtraction Output]\n");
            printf("%d", 0);
            return 0;
        }
    }

    int firstIntIndex = 0;
    int lastFloatIndex = 9999;

    for (int i = 0; i < 5000; i++) {
        if (result[i] == 0) firstIntIndex++;
        else break;
    }

    for (int i = 9999; i > 4999; i--) {
        if (result[i] == 0) lastFloatIndex--;
        else break;
    }

    if (firstIntIndex == 5000) firstIntIndex = 4999;
    if (lastFloatIndex == 4999) lastFloatIndex = 5000;

    printf("[Subtraction Output]\n");

    if (resultSign == 1) {
        printf("-");
    }

    for (int i = firstIntIndex; i < 5000; i++) {
        printf("%d", result[i]);
    }

    printf(".");

    for (int i = 5000; i <= lastFloatIndex; i++) {
        printf("%d", result[i]);
    }

    return 0;
}

int multiplication(BigFloat bigNumber1, BigFloat bigNumber2) {
    int result[100000];
    int maxIntSize = 0;
    int maxFloatSize = 0;

    for (int i = 0; i < 100000; i++) {
        result[i] = 0;
    }

    if (bigNumber1.intSize > bigNumber2.intSize) {
        maxIntSize = bigNumber1.intSize;
    }
    else if (bigNumber1.intSize < bigNumber2.intSize) {
        maxIntSize = bigNumber2.intSize;
    }
    else {
        maxIntSize = bigNumber1.intSize;
    }

    if (bigNumber1.floatSize > bigNumber2.floatSize)
        maxFloatSize = bigNumber1.floatSize;
    else
        maxFloatSize = bigNumber2.floatSize;

    //result에 두 수의 각 자리수를 곱한 값을 넣는다
    for (int i = 4999 + maxFloatSize; i >= 5000 - maxIntSize; i--) {
        for (int j = 4999 + maxFloatSize; j >= 5000 - maxIntSize; j--) {
            result[49999 + j - 4999 + i - 4999] += bigNumber2.number[i] * bigNumber1.number[j];
        }
    }

    //result의 각 자리수가 일의 자리수가 되도록 정리한다
    int totalFloatsize = bigNumber1.floatSize + bigNumber2.floatSize;

    for (int i = 50000 + totalFloatsize; i > 0; i--) {
        result[i - 1] += result[i] / 10;
        result[i] = result[i] % 10;
    }

    //결과 출력을 위해 출력할 첫번째 인덱스를 설정한다
    int firstIntIndex = 0;
    int lastFloatIndex = 49999 + totalFloatsize;

    for (int i = 0; i < 50000; i++) {
        if (result[i] == 0) firstIntIndex++;
        else break;
    }

    for (int i = totalFloatsize; i > 0; i--) {
        if (result[49999 + i] == 0) lastFloatIndex--;
        else break;
    }

    if (firstIntIndex == 50000) firstIntIndex = 49999;
    if (lastFloatIndex == 49999) lastFloatIndex = 50000;

    //결과 출력
    printf("[Multiplication Output]\n");

    if ((bigNumber1.signCheck == 1 && bigNumber2.signCheck == 0) || (bigNumber2.signCheck == 1 && bigNumber1.signCheck == 0)) {

        printf("-");
    }
    for (int i = firstIntIndex; i < 50000; i++) {
        printf("%d", result[i]);
    }

    printf(".");

    for (int i = 50000; i <= lastFloatIndex; i++) {
        printf("%d", result[i]);
    }

    return 0;
}

int division(BigFloat bigNumber1, BigFloat bigNumber2) {
    int result[1000];
    int maxIntSize = 0;
    int maxFloatSize = 0;

    for (int i = 0; i < 1000; i++) {
        result[i] = 0;
    }
    //result의 elements를 0으로 초기화

    if (bigNumber1.floatSize >= bigNumber2.floatSize) {
        maxFloatSize = bigNumber1.floatSize;
    }
    else {
        maxFloatSize = bigNumber2.floatSize;
    }

    if (bigNumber1.intSize >= bigNumber2.intSize) {
        maxIntSize = bigNumber1.intSize;
    }
    else {
        maxIntSize = bigNumber2.intSize;
    }

    int checkBigger = 0;
    int subNum = 0;
    int resultIndex = 499;

    for (int i = 0; i < 499; i++) {
        for (int i = 0; i < 10000; i++) {
            if (bigNumber1.number[i] > bigNumber2.number[i]) {
                checkBigger = 1;
                break;
            }
            else if (bigNumber1.number[i] < bigNumber2.number[i]) {
                checkBigger = -1;
                break;
            }
            else checkBigger = 0;
        }

        while (checkBigger == 1) {
            for (int i = 0; i < 10000; i++) {
                if (bigNumber1.number[i] > bigNumber2.number[i]) {
                    checkBigger = 1;
                    break;
                }
                else if (bigNumber1.number[i] < bigNumber2.number[i]) {
                    checkBigger = -1;
                    break;
                }
                else checkBigger = 0;
            }

            if (checkBigger == 1) {
                for (int i = 4999 + maxFloatSize; i >= 5000 - maxIntSize; i--) {
                    if (bigNumber1.number[i] >= bigNumber2.number[i]) {
                        bigNumber1.number[i] = bigNumber1.number[i] - bigNumber2.number[i];
                    }
                    else {
                        bigNumber1.number[i] = (10 + bigNumber1.number[i]) - bigNumber2.number[i];
                        bigNumber1.number[i - 1] -= 1;
                    }
                }
                subNum++;
            }
        }

        if (checkBigger == 0) {
            subNum++;
            result[resultIndex] = subNum;
            break;
        }

        int tempNum2[10000];
        for (int i = 0; i < 1000; i++) {
            tempNum2[i] = 0;
        }
        for (int i = 0; i < 9999; i++) {
            tempNum2[i + 1] = bigNumber2.number[i];
            bigNumber2.number[i] = tempNum2[i];
        }
        maxFloatSize++;

        result[resultIndex] = subNum;

        resultIndex++;
        subNum = 0;
    }

    for (int i = 499; i > 0; i--) {
        result[i - 1] = result[i] / 10;
        result[i] = result[i] % 10;
    }

    int firstIntIndex = 0;
    int lastFloatIndex = resultIndex;

    for (int i = 0; i < 500; i++) {
        if (result[i] == 0) firstIntIndex++;
        else break;
    }

    for (int i = resultIndex; i > 0; i--) {
        if (result[499 + i] == 0) lastFloatIndex--;
        else break;
    }

    if (firstIntIndex == 500) firstIntIndex = 499;
    if (lastFloatIndex <= 500) lastFloatIndex = 500;

    printf("[Division Output]\n");

    if ((bigNumber1.signCheck == 1 && bigNumber2.signCheck == 0) || (bigNumber2.signCheck == 1 && bigNumber1.signCheck == 0)) {

        printf("-");
    }
    for (int i = firstIntIndex; i < 500; i++) {
        printf("%d", result[i]);
    }

    printf(".");

    for (int i = 500; i <= lastFloatIndex; i++) {
        printf("%d", result[i]);
    }

    return 0;
}

int main() {

    BigFloat num1, num2;
    //printf("[float max]\n %e\n\n", FLT_MAX); //가장 큰 floating number를 출력

    printf("Input two number: \n");
    scanf("%s", num1.inputNum);
    scanf("%s", num2.inputNum);

    num1 = storeNumber(num1);
    num2 = storeNumber(num2);


    showNumber(num1);  //num1을 출력
    showNumber(num2);  //num2를 출력

    //addition(num1, num2);   //덧셈
    //subtraction(num1, num2); //뺄셈 
    //multiplication(num1, num2); // 곱셈
    division(num1, num2); //나눗셈

    //테스트 숫자: 123412341234123412341234.12341234
    //테스트 숫자: 98989898989898989898989898.9898989898989898989898

    printf("\n");

    return 0;
}