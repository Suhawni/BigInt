#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define byte char
#include "BigInteger.h"
void display(struct BigInteger b) {
    int i;
    if (b.sign != 0) {
        printf("-");
    }
    for (i = b.len - 1; i >= 0; i--) {
        printf("%d", b.data[i]);
    }
}
struct BigInteger initialise(char *s) {
    struct BigInteger b;
    int i, k;

    // Checking if the number is positive or negative
    if (s[0] == '-') {
        b.sign = 1;
        i = 1;
    } else {
        b.sign = 0;
        i = 0;
    }

    // Skipping leading zeroes
    while (s[i] == '0') {
        i++;
    }

    b.len = strlen(s) - i;
    b.data = (int *)malloc(sizeof(int) * b.len);
    k = b.len - 1;

    while (s[i] != '\0') {
        b.data[k] = s[i] - '0';
        i++;
        k--;
    }

    if (b.len == 0) {
        b.len = 1;
        b.data[0] = 0;
    }

    return b;
}
int compare(struct BigInteger b1, struct BigInteger b2) {
    int i, retval;
    if (b1.len == b2.len) {
        i = b1.len - 1;
        while (i >= 0 && b1.data[i] == b2.data[i]) {
            i--;
        }
        if (i == -1) {
            retval = 0;
        } else {
            retval = b1.data[i] - b2.data[i];
        }
    } else {
        retval = b1.len - b2.len;
    }
    return retval;
}
struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct BigInteger ans;

    if (a.sign == b.sign) {
        ans = addition(a,b);
        ans.sign = a.sign;
    } else {
        if (compare(a,b) > 0) {
            ans = subtraction(a,b);
            ans.sign = a.sign;
        } else {
            ans = subtraction(b,a);
            ans.sign = b.sign;
        }
    }

    display(ans);
}
struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    if (b.sign == 0) {
        b.sign = 1;
    } else {
        b.sign = 0;
    }
    struct BigInteger result = add(a, b); // Call the add function
    if (b.sign == 0) {
        b.sign = 1;
    } else {
        b.sign = 0;
    }

    // return result;
}
struct BigInteger addition(struct BigInteger a, struct BigInteger b) {
    int carry, i, j, sum, k;
    struct BigInteger ans;

    if (a.len == b.len) {
        ans.len = a.len + 1;
    } else {
        ans.len = (a.len > b.len) ? (a.len + 1) : (b.len + 1);
    }

    ans.data = (int *)malloc(sizeof(int) * (ans.len));
    i = 0;
    j = 0;
    k = 0;
    carry = 0;

    while (i < a.len || j < b.len || carry != 0) {
        if (i < a.len && j < b.len) {
            sum = a.data[i] + b.data[j];
        } else if (i < a.len) {
            sum = a.data[i];
        } else if (j < b.len) {
            sum = b.data[j];
        } else {
            sum = 0;
        }

        sum += carry;
        carry = sum / 10;
        ans.data[k] = sum % 10;
        k++;
        i++;
        j++;
    }

    ans.len = k;
    return ans;
}
struct BigInteger subtraction(struct BigInteger a, struct BigInteger b) {
    int borrow, i, j, diff, k;
    struct BigInteger ans;

    if (a.len == b.len) {
        ans.len = a.len;
    } else {
        ans.len = (a.len > b.len) ? a.len : b.len;
    }

    ans.data = (int *)malloc(sizeof(int) * ans.len);
    i = 0;
    j = 0;
    k = 0;
    borrow = 0;

    while (i < a.len) {
        if (i < a.len && j < b.len) {
            diff = a.data[i] - b.data[j] - borrow;
        } else if (i < a.len) {
            diff = a.data[i] - borrow;
        }

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        ans.data[k] = diff;
        k++;
        i++;
        j++;
    }

    if (ans.data[k - 1] == 0) {
        ans.len = k - 1;
    } else {
        ans.len = k;
    }

    return ans;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b) {
    int i, j, carry, prod, sum, temp;
    struct BigInteger ans;
    ans.len = a.len + b.len;
    ans.data = (int *)malloc(sizeof(int) * ans.len);

    for (i = 0; i < ans.len; i++) {
        ans.data[i] = 0;
    }

    for (i = 0; i < a.len; i++) {
        carry = 0;
        for (j = 0; j < b.len; j++) {
            prod = a.data[i] * b.data[j];
            sum = prod + carry;
            ans.data[i + j] += sum;
            carry = ans.data[i + j] / 10;
            ans.data[i + j] = ans.data[i + j] % 10;
        }

        if (carry != 0) {
            ans.data[i + j] += carry;
            if (ans.data[i + j] > 9) {
                ans.data[i + j] = (ans.data[i + j]) % 10;
                ans.data[i + j + 1] += (ans.data[i + j]) / 10;
            }
        }
    }

    i = ans.len - 1;
    while (ans.data[i] == 0 && i >= 0) {
        i--;
    }

    ans.len = i + 1;

    if (ans.len == 0) {
        ans.len = 1;
        ans.data[0] = 0;
    }

    if (a.sign == b.sign) {
        ans.sign = 0;
    } else {
        ans.sign = 1;
    }

    display(ans);
}
struct BigInteger div1(struct BigInteger a, struct BigInteger b) {
    struct BigInteger ans, temp;
    ans.len = 0;
    ans.sign = 0;
    ans.data = (int *)malloc(sizeof(int));

    if (compare(a, b) < 0) {
        ans.len = 1;
        ans.data[0] = 0;
        return ans;
    }

    temp.len = 1;
    temp.sign = 0;
    temp.data = (int *)malloc(sizeof(int));
    temp.data[0] = 1;

    struct BigInteger one = initialise("1");

    while (compare(a, b) >= 0) {
        a = subtraction(a, b);
        ans = add(ans, temp);
    }

    free(temp.data);
    free(one.data);

    display(ans);
}
