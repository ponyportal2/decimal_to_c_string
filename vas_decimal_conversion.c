#include "vas_decimal_conversion.h"

#include <stdio.h>
#include <string.h>

#include "vas_powers_of_two.h"

void vas_clear(char* input, int size) {
  for (int i = 0; i < size; ++i) {
    input[i] = 0;
  }
}

void vas_add_zeroes(char left[VAS_SIZE_ONE], char right[VAS_SIZE_ONE]) {
  int len_l = strlen(left), len_r = strlen(right);
  char string_left[VAS_SIZE_ONE] = {0}, string_right[VAS_SIZE_ONE] = {0};
  vas_clear(string_left, VAS_SIZE_ONE);
  vas_clear(string_right, VAS_SIZE_ONE);
  for (int i = 0; i < VAS_SIZE_ONE - len_l - 1; i++) strcat(string_left, "0");
  for (int i = 0; i < VAS_SIZE_ONE - len_r - 1; i++) strcat(string_right, "0");
  strcat(string_left, left);
  strcat(string_right, right);
  strcpy(left, string_left);
  strcpy(right, string_right);
}

void vas_reverse_string(char* input) {
  int i = 0, last_char = strlen(input) - 1;
  while (i < last_char) {
    char temp = input[i];
    input[i] = input[last_char];
    input[last_char] = temp;
    i++;
    last_char--;
  }
}

void vas_decimal_mantis_to_binary(char binary_output[VAS_SIZE_BIN],
                                  vas_decimal value) {
  char binary_local[VAS_SIZE_BIN] = {0};
  vas_clear(binary_local, VAS_SIZE_BIN);
  for (int cur_bit = 0; cur_bit <= 2; cur_bit++) {
    char stack[VAS_SIZE_THRD] = {0};
    vas_clear(stack, VAS_SIZE_THRD);
    for (int i = 0; i < VAS_SIZE_THRD - 1; ++i) stack[i] = '0';
    int i = 0;
    while (value.bits[cur_bit]) {
      if (value.bits[cur_bit] % 2 == 1) {
        stack[i] = '1';
      } else {
        stack[i] = '0';
      }
      ++i;
      value.bits[cur_bit] /= 2;
    }
    strcat(binary_local, stack);
  }
  vas_reverse_string(binary_local);
  binary_local[VAS_SIZE_BIN - 1] = 0;
  strcpy(binary_output, binary_local);
}

int vas_get_sign(int value) {
  char int_to_chars[4] = {0};
  vas_clear(int_to_chars, 4);
  int sign = 0;
  memcpy(int_to_chars, &value, sizeof(char) * 4);
  int_to_chars[3] == 0 ? (sign = 0) : (sign = 1);
  return sign;
}

int vas_get_scale(int value) {
  char intToChars[4] = {0};
  vas_clear(intToChars, 4);
  int scale = 0;
  memcpy(intToChars, &value, sizeof(char) * 4);
  scale = intToChars[2];
  return scale;
}

void vas_base_ten_char_array_add(char left[VAS_SIZE_ONE],
                                 char right[VAS_SIZE_ONE],
                                 char result[VAS_SIZE_ONE]) {
  vas_add_zeroes(left, right);
  char result_local[VAS_SIZE_ONE] = {0};
  vas_clear(result_local, VAS_SIZE_ONE);
  for (int i = 0; i < VAS_SIZE_ONE - 1; i++) {
    result_local[i] = (left[i] - '0') + (right[i] - '0');
  }
  for (int i = VAS_SIZE_ONE - 1; i > 0; i--) {
    if (result_local[i] > 9) {
      result_local[i - 1] += 1;
      result_local[i] -= 10;
    }
  }
  int started = 0, j = 0;
  for (int i = 0; i < VAS_SIZE_ONE - 1; ++i) {
    if (result_local[i] != 0) started = 1;
    if (started) {
      result[j] = result_local[i] + '0';
      ++j;
    }
  }
}

void vas_binary_to_base_ten(char binary[VAS_SIZE_BIN],
                            char output[VAS_OVER_SIZE]) {
  vas_reverse_string(binary);
  char sum[VAS_OVER_SIZE] = {0};
  vas_clear(sum, VAS_OVER_SIZE);
  strcpy(sum, "0");
  for (int i = 0; i < VAS_SIZE_BIN; ++i) {
    if (binary[i] == '1') {
      char power_of_two_local[VAS_OVER_SIZE] = {0};
      vas_clear(power_of_two_local, VAS_OVER_SIZE);
      strcpy(power_of_two_local, powers_of_two[i]);
      char sum_temp[VAS_OVER_SIZE] = {0};
      vas_clear(sum_temp, VAS_OVER_SIZE);
      vas_base_ten_char_array_add(sum, power_of_two_local, sum_temp);
      strcpy(sum, sum_temp);
    }
  }
  strcpy(output, sum);
}

void vas_add_the_dot(int dot, char* the_string) {
  int len = strlen(the_string);
  char temp[31] = {0};
  vas_clear(temp, 31);
  for (int i = 0; i < 30 - len - 1; i++) strcat(temp, "0");
  strcat(temp, the_string);
  if (dot > 0) {
    char temp_2[31] = {0};
    vas_clear(temp_2, 31);
    strncat(temp_2, temp, 29 - dot);
    strcat(temp_2, ".");
    strcat(temp_2, temp + 29 - dot);
    strcpy(the_string, temp_2);
  } else {
    strcpy(the_string, temp);
  }
}

void vas_print_decimal(vas_decimal input) {
  char input_binary_string[VAS_SIZE_BIN];
  vas_clear(input_binary_string, VAS_SIZE_BIN);
  char input_base_ten_string[VAS_SIZE_ONE];
  vas_clear(input_base_ten_string, VAS_SIZE_ONE);
  vas_decimal_mantis_to_binary(input_binary_string, input);
  vas_binary_to_base_ten(input_binary_string, input_base_ten_string);
  printf("\nmantis:%s\n", input_base_ten_string);
  vas_add_the_dot(vas_get_scale(input.bits[3]), input_base_ten_string);
  printf("\nfinal :");
  if (vas_get_sign(input.bits[3])) printf("-");
  printf("%s\n", input_base_ten_string);
}

int main() {
  char decimal_in_binary_string[VAS_SIZE_BIN];
  vas_clear(decimal_in_binary_string, VAS_SIZE_BIN);
  vas_decimal decimal_inst;
  decimal_inst.bits[0] = 0b11111111111111111111111111111111;
  decimal_inst.bits[1] = 0b11111111111111111111111111111111;
  decimal_inst.bits[2] = 0b11111111111111111111111111111111;
  decimal_inst.bits[3] = 2148007936;
  vas_decimal decimal_inst2;
  decimal_inst2.bits[0] = 1600699885;  // -789.10111213
  decimal_inst2.bits[1] = 18;
  decimal_inst2.bits[2] = 0;
  decimal_inst2.bits[3] = 2148007936;
  vas_print_decimal(decimal_inst);
  vas_print_decimal(decimal_inst2);
  return 0;
}