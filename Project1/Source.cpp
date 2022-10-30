#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

typedef struct MyStruct
{
    char number[1000];
    char* intNum = 0;
    char* floatNum = 0;
    int intsize, floatsize = 0;
    int fullsingleNum[1000];
    int intsingleNum[1000];
    int floatsingleNum[1000];
    int signCheck = 0;

}MyStruct;

MyStruct stringtointArray(MyStruct mystruct) {

    char* token = strtok(mystruct.number, ".");

    mystruct.intNum = token;
    token = strtok(NULL, "");
    mystruct.floatNum = token;


    if (mystruct.intNum[0] == '-') {
        mystruct.signCheck = 1;
        for (int i = 0; i < strlen(mystruct.intNum); i++) {
            mystruct.intNum[i] = mystruct.intNum[i + 1];
        }
    }

    mystruct.intsize = strlen(mystruct.intNum);
    mystruct.floatsize = strlen(mystruct.floatNum);

    for (int i = 0; i < 1000; i++) {
        mystruct.fullsingleNum[i] = 0;
    }

    for (int i = 0; i < mystruct.intsize; i++) {
        mystruct.fullsingleNum[i] = ((int)mystruct.intNum[i]) - 48;
    }
    for (int i = 0; i < mystruct.floatsize; i++) {
        mystruct.fullsingleNum[i + 500] = ((int)mystruct.floatNum[i]) - 48;
    }

    int tempNum[500];

    for (int i = 0; i < 500; i++) {
        tempNum[i] = 0;
    }

    for (int i = 0; i < mystruct.intsize; i++) {
        tempNum[i + 500 - mystruct.intsize] = mystruct.fullsingleNum[i];
    }
    for (int i = 0; i < 500; i++) {
        mystruct.fullsingleNum[i] = tempNum[i];
    }

    return mystruct;

}


int addition(MyStruct mystruct1, MyStruct mystruct2) {

    int result[1000];
    int checkBigger = 0;
    int resultSign = 0;

    for (int i = 0; i < 1000; i++) {
        result[i] = 0;
    }
    //result의 elements를 0으로 초기화

    if (mystruct1.signCheck == 0 && mystruct2.signCheck == 0) {
        for (int i = 999; i >= 0; i--) {
            if (result[i] + mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i] <= 9)
                result[i] += mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i];
            else {
                result[i] = (result[i] + mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i]) % 10;
                result[i - 1] += 1;
            }
        }
    }
    else if (mystruct1.signCheck == 1 && mystruct2.signCheck == 0) {
        for (int i = 0; i < 1000; i++) {
            if (mystruct1.fullsingleNum[i] > mystruct2.fullsingleNum[i]) {
                checkBigger = 1;
                break;
            }
            else if (mystruct1.fullsingleNum[i] < mystruct2.fullsingleNum[i]) {
                checkBigger = -1;
                break;
            }
        }
        if (checkBigger == 1) {
            for (int i = 999; i >= 0; i--) {
                if (mystruct1.fullsingleNum[i] >= mystruct2.fullsingleNum[i]) {
                    result[i] = mystruct1.fullsingleNum[i] - mystruct2.fullsingleNum[i];
                }
                else {
                    result[i] = (10 + mystruct1.fullsingleNum[i]) - mystruct2.fullsingleNum[i];
                    mystruct1.fullsingleNum[i - 1] -= 1;
                }
            }
            resultSign = 1;
        }
        else if (checkBigger == -1) {
            for (int i = 999; i >= 0; i--) {
                if (mystruct2.fullsingleNum[i] >= mystruct1.fullsingleNum[i]) {
                    result[i] = mystruct2.fullsingleNum[i] - mystruct1.fullsingleNum[i];
                }
                else {
                    result[i] = (10 + mystruct2.fullsingleNum[i]) - mystruct1.fullsingleNum[i];
                    mystruct2.fullsingleNum[i - 1] -= 1;
                }
            }
            resultSign = 0;

        }
        else if (checkBigger == 0) {
            printf("Subtraction Output: ");
            printf("%d", 0);
            printf("\n");
            return 0;
        }
    }
    else if ((mystruct2.signCheck == 1 && mystruct1.signCheck == 0)) {

        for (int i = 0; i < 1000; i++) {
            if (mystruct1.fullsingleNum[i] > mystruct2.fullsingleNum[i]) {
                checkBigger = 1;
                break;
            }
            else if (mystruct1.fullsingleNum[i] < mystruct2.fullsingleNum[i]) {
                checkBigger = -1;
                break;
            }
        }
        if (checkBigger == 1) {
            for (int i = 999; i >= 0; i--) {
                if (mystruct1.fullsingleNum[i] >= mystruct2.fullsingleNum[i]) {
                    result[i] = mystruct1.fullsingleNum[i] - mystruct2.fullsingleNum[i];
                }
                else {
                    result[i] = (10 + mystruct1.fullsingleNum[i]) - mystruct2.fullsingleNum[i];
                    mystruct1.fullsingleNum[i - 1] -= 1;
                }
            }
            resultSign = 0;
        }
        else if (checkBigger == -1) {
            for (int i = 999; i >= 0; i--) {
                if (mystruct2.fullsingleNum[i] >= mystruct1.fullsingleNum[i]) {
                    result[i] = mystruct2.fullsingleNum[i] - mystruct1.fullsingleNum[i];
                }
                else {
                    result[i] = (10 + mystruct2.fullsingleNum[i]) - mystruct1.fullsingleNum[i];
                    mystruct2.fullsingleNum[i - 1] -= 1;
                }
            }
            resultSign = 1;
        }
        else if (checkBigger == 0) {
            printf("Addition Output: ");
            printf("%d", 0);
            printf("\n");
            return 0;
        }
    }
    else {
        for (int i = 999; i >= 0; i--) {
            if (result[i] + mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i] <= 9)
                result[i] += mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i];
            else {
                result[i] = (result[i] + mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i]) % 10;
                result[i - 1] += 1;
            }
        }
        resultSign = 1;
    }

    printf("Addition Output: ");

    int firstIntIndex = 0;
    int lastFloatIndex = 999;

    for (int i = 0; i < 500; i++) {
        if (result[i] == 0) firstIntIndex++;
        else break;
    }

    for (int i = 999; i > 499; i--) {
        if (result[i] == 0) lastFloatIndex--;
        else break;
    }

    if (firstIntIndex == 500) firstIntIndex = 499;
    if (lastFloatIndex == 499) lastFloatIndex = 500;

    if (resultSign == 1) {
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

int subtraction(MyStruct mystruct1, MyStruct mystruct2) {

    int result[1000];
    int checkBigger = 0;
    int resultSign = 0;

    for (int i = 0; i < 1000; i++) {
        result[i] = 0;
    }
    //result의 elements를 0으로 초기화

    if (mystruct1.signCheck == 0 && mystruct2.signCheck == 0) {
        for (int i = 0; i < 1000; i++) {
            if (mystruct1.fullsingleNum[i] > mystruct2.fullsingleNum[i]) {
                checkBigger = 1;
                break;
            }
            else if (mystruct1.fullsingleNum[i] < mystruct2.fullsingleNum[i]) {
                checkBigger = -1;
                break;
            }
        }
        if (checkBigger == 1) {
            for (int i = 999; i >= 0; i--) {
                if (mystruct1.fullsingleNum[i] >= mystruct2.fullsingleNum[i]) {
                    result[i] = mystruct1.fullsingleNum[i] - mystruct2.fullsingleNum[i];
                }
                else {
                    result[i] = (10 + mystruct1.fullsingleNum[i]) - mystruct2.fullsingleNum[i];
                    mystruct1.fullsingleNum[i - 1] -= 1;
                }
            }
            resultSign = 0;
        }
        else if (checkBigger == -1) {
            for (int i = 999; i >= 0; i--) {
                if (mystruct2.fullsingleNum[i] >= mystruct1.fullsingleNum[i]) {
                    result[i] = mystruct2.fullsingleNum[i] - mystruct1.fullsingleNum[i];
                }
                else {
                    result[i] = (10 + mystruct2.fullsingleNum[i]) - mystruct1.fullsingleNum[i];
                    mystruct2.fullsingleNum[i - 1] -= 1;
                }
            }
            resultSign = 1;
        }
        else if (checkBigger == 0) {
            printf("Subtraction Output: ");
            printf("%d", 0);
            printf("\n");
            return 0;
        }
    }
    else if (mystruct1.signCheck == 1 && mystruct2.signCheck == 0) {
        for (int i = 999; i >= 0; i--) {
            if (result[i] + mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i] <= 9)
                result[i] += mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i];
            else {
                result[i] = (result[i] + mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i]) % 10;
                result[i - 1] += 1;
            }
        }
        resultSign = 1;
    }
    else if ((mystruct2.signCheck == 1 && mystruct1.signCheck == 0)) {
        for (int i = 999; i >= 0; i--) {
            if (result[i] + mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i] <= 9)
                result[i] += mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i];
            else {
                result[i] = (result[i] + mystruct1.fullsingleNum[i] + mystruct2.fullsingleNum[i]) % 10;
                result[i - 1] += 1;
            }
        }
        resultSign = 0;
    }
    else { //둘다 음수인 경우
        for (int i = 0; i < 1000; i++) {
            if (mystruct1.fullsingleNum[i] > mystruct2.fullsingleNum[i]) {
                checkBigger = 1;
                break;
            }
            else if (mystruct1.fullsingleNum[i] < mystruct2.fullsingleNum[i]) {
                checkBigger = -1;
                break;
            }
        }
        if (checkBigger == 1) {
            for (int i = 999; i >= 0; i--) {
                if (mystruct1.fullsingleNum[i] >= mystruct2.fullsingleNum[i]) {
                    result[i] = mystruct1.fullsingleNum[i] - mystruct2.fullsingleNum[i];
                }
                else {
                    result[i] = (10 + mystruct1.fullsingleNum[i]) - mystruct2.fullsingleNum[i];
                    mystruct1.fullsingleNum[i - 1] -= 1;
                }
            }
            resultSign = 1;
        }
        else if (checkBigger == -1) {
            for (int i = 999; i >= 0; i--) {
                if (mystruct2.fullsingleNum[i] >= mystruct1.fullsingleNum[i]) {
                    result[i] = mystruct2.fullsingleNum[i] - mystruct1.fullsingleNum[i];
                }
                else {
                    result[i] = (10 + mystruct2.fullsingleNum[i]) - mystruct1.fullsingleNum[i];
                    mystruct2.fullsingleNum[i - 1] -= 1;
                }
            }
            resultSign = 0;
        }
        else if (checkBigger == 0) {
            printf("Subtraction Output: ");
            printf("%d", 0);
            printf("\n");
            return 0;
        }
    }

    printf("Subtraction Output: ");

    int firstIntIndex = 0;
    int lastFloatIndex = 999;

    for (int i = 0; i < 500; i++) {
        if (result[i] == 0) firstIntIndex++;
        else break;
    }

    for (int i = 999; i > 499; i--) {
        if (result[i] == 0) lastFloatIndex--;
        else break;
    }

    if (firstIntIndex == 500) firstIntIndex = 499;
    if (lastFloatIndex == 499) lastFloatIndex = 500;

    if (resultSign == 1) {
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

int multiplication(MyStruct mystruct1, MyStruct mystruct2) {
    int result[100000];
    int maxIntSize = 0;
    int maxFloatSize = 0;

    for (int i = 0; i < 100000; i++) {
        result[i] = 0;
    }

    if (mystruct1.intsize > mystruct2.intsize) {
        maxIntSize = mystruct1.intsize;
    }
    else if (mystruct1.intsize < mystruct2.intsize) {
        maxIntSize = mystruct2.intsize;
    }
    else {
        maxIntSize = mystruct1.intsize;
    }

    if (mystruct1.floatsize > mystruct2.floatsize)
        maxFloatSize = mystruct1.floatsize;
    else
        maxFloatSize = mystruct2.floatsize;

    //result에 두 수의 각 자리수를 곱한 값을 넣는다
    for (int i = 499 + maxFloatSize; i >= 500 - maxIntSize; i--) {
        for (int j = 499 + maxFloatSize; j >= 500 - maxIntSize; j--) {
            result[49999 + j - 499 + i - 499] += mystruct2.fullsingleNum[i] * mystruct1.fullsingleNum[j];
        }
    }

    //result의 각 자리수가 일의 자리수가 되도록 정리한다
    int totalFloatsize = mystruct1.floatsize + mystruct2.floatsize;

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
    if ((mystruct1.signCheck == 1 && mystruct2.signCheck == 0) || (mystruct2.signCheck == 1 && mystruct1.signCheck == 0)) {

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

int division(MyStruct mystruct1, MyStruct mystruct2) {
    int result[1000];
    int maxIntSize = 0;
    int maxFloatSize = 0;

    for (int i = 0; i < 1000; i++) {
        result[i] = 0;
    }
    //result의 elements를 0으로 초기화

    if (mystruct1.floatsize >= mystruct2.floatsize) {
        maxFloatSize = mystruct1.floatsize;
    }
    else {
        maxFloatSize = mystruct2.floatsize;
    }

    if (mystruct1.intsize >= mystruct2.intsize) {
        maxIntSize = mystruct1.intsize;
    }
    else {
        maxIntSize = mystruct2.intsize;
    }

    int checkBigger = 0;
    int subNum = 0;
    int resultIndex = 499;

    for (int i = 0; i < 498; i++) {
        for (int i = 0; i < 1000; i++) {
            if (mystruct1.fullsingleNum[i] > mystruct2.fullsingleNum[i]) {
                checkBigger = 1;
                break;
            }
            else if (mystruct1.fullsingleNum[i] < mystruct2.fullsingleNum[i]) {
                checkBigger = -1;
                break;
            }
            else checkBigger = 0;
        }

        while (checkBigger == 1) {
            for (int i = 0; i < 1000; i++) {
                if (mystruct1.fullsingleNum[i] > mystruct2.fullsingleNum[i]) {
                    checkBigger = 1;
                    break;
                }
                else if (mystruct1.fullsingleNum[i] < mystruct2.fullsingleNum[i]) {
                    checkBigger = -1;
                    break;
                }
                else checkBigger = 0;
            }

            if (checkBigger == 1) {
                for (int i = 499 + maxFloatSize; i >= 500 - maxIntSize; i--) {
                    if (mystruct1.fullsingleNum[i] >= mystruct2.fullsingleNum[i]) {
                        mystruct1.fullsingleNum[i] = mystruct1.fullsingleNum[i] - mystruct2.fullsingleNum[i];
                    }
                    else {
                        mystruct1.fullsingleNum[i] = (10 + mystruct1.fullsingleNum[i]) - mystruct2.fullsingleNum[i];
                        mystruct1.fullsingleNum[i - 1] -= 1;
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

        int tempNum2[1000];
        for (int i = 0; i < 1000; i++) {
            tempNum2[i] = 0;
        }
        for (int i = 0; i < 999; i++) {
            tempNum2[i + 1] = mystruct2.fullsingleNum[i];
            mystruct2.fullsingleNum[i] = tempNum2[i];
        }
        maxFloatSize++;

        result[resultIndex] = subNum;

        resultIndex++;
        subNum = 0;
        printf("%d\n", resultIndex);
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
    if (lastFloatIndex == 499) lastFloatIndex = 500;

    if ((mystruct1.signCheck == 1 && mystruct2.signCheck == 0) || (mystruct2.signCheck == 1 && mystruct1.signCheck == 0)) {

        printf("-");
    }
    for (int i = firstIntIndex; i < 500; i++) {
        printf("%d", result[i]);
    }

    printf(".");

    for (int i = 500; i <= resultIndex; i++) {
        printf("%d", result[i]);
    }

    return 0;
}

int main() {

    MyStruct num1, num2;

    printf("Input two number: \n");
    scanf("%s", num1.number);
    scanf("%s", num2.number);

    num1 = stringtointArray(num1);
    num2 = stringtointArray(num2);


    //addition(num1, num2);
    //subtraction(num1, num2);
    //multiplication(num1, num2);
    //division(num1, num2);

    return 0;
}