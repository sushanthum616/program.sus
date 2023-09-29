// question no 1//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charToInt(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 10; // For hexadecimal (A-F)
  } else if (c >= 'a' && c <= 'z') {
    return c - 'a' + 10; // For hexadecimal (a-f)
  }
  return -1; // Invalid character
}

bool isValidDigit(char c, int base) {
  int maxDigit = (base <= 10) ? base - 1 : 15;
  int digitValue = charToInt(c);
  return (digitValue >= 0 && digitValue <= maxDigit);
}

void baseConversion(char *num, int base, int new_base) {
  int len = strlen(num);
  long long int decimalValue = 0;
  int i;

  for (i = 0; i < len; i++) {
    if (!isValidDigit(num[i], base)) {
      printf("Error: Invalid digit '%c' in base-%d number.\n", num[i], base);
      return;
    }
    decimalValue = decimalValue * base + charToInt(num[i]);
  }

  // Perform the conversion to the new base
  char result[100];
  int index = 0;
  while (decimalValue > 0) {
    int remainder = decimalValue % new_base;
    char digit;
    if (remainder < 10) {
      digit = '0' + remainder;
    } else {
      digit = 'A' + (remainder - 10); // Convert to hexadecimal
    }
    result[index++] = digit;
    decimalValue /= new_base;
  }

  // Print the result in reverse order
  printf("Result in base-%d: ", new_base);
  for (i = index - 1; i >= 0; i--) {
    printf("%c", result[i]);
  }
  printf("\n");
}

int main() {
  char num[100];
  int base, new_base;

  printf("Enter the number: ");
  scanf("%s", num);

  printf("Enter the current base: ");
  scanf("%d", &base);

  printf("Enter the new base: ");
  scanf("%d", &new_base);

  baseConversion(num, base, new_base);

  return 0;
}

// question no 2//
#include <math.h>
#include <stdio.h>

void intToBinary5Bits(int num, char *binary) {
  for (int i = 4; i >= 0; i--) {
    binary[i] = '0' + (num & 1);
    num >>= 1;
  }
  binary[5] = '\0';
}

int main() {
  float num = -26.625;
  char binary[14];

  // Step 1: Determine the sign bit
  int sign = (num < 0) ? 1 : 0;
  num = fabs(num); // Make the number positive for further calculations

  // Step 2: Convert the number to binary
  int integerPart = (int)num;
  float fractionalPart = num - integerPart;

  // Initialize the significand
  char significand[9] = "00000000"; // 8 bits for significand

  // Step 3: Extract the fractional part and store it in the significand
  for (int i = 0; i < 8; i++) {
    fractionalPart *= 2;
    significand[i] = '0' + (int)fractionalPart;
    fractionalPart -= (int)fractionalPart;
  }

  // Step 4: Calculate the exponent
  int exponent = 0;
  while (integerPart >= 2) {
    integerPart /= 2;
    exponent++;
  }

  while (integerPart < 1) {
    integerPart *= 2;
    exponent--;
  }

  // Step 5: Add 16 to the exponent
  exponent += 16;

  // Step 6: Convert the exponent to 5 bits
  char exponentBinary[6]; // 5 bits + 1 for null terminator
  intToBinary5Bits(exponent, exponentBinary);

  // Step 7: Combine the sign bit, exponent, and significand
  sprintf(binary, "%d%s%s", sign, exponentBinary, significand);

  printf("%s\n", binary);

  return 0;
}
