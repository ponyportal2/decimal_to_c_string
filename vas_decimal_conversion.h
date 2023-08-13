#ifndef DEC_VAS_DECIMAL_CONVERSION_H_
#define DEC_VAS_DECIMAL_CONVERSION_H_

#include "decimal_struct.h"

#define VAS_SIZE_ONE 59
#define VAS_SIZE_BIN 97
#define VAS_SIZE_THRD 33
#define VAS_OVER_SIZE 256

void vas_clear(char* input, int size);

void vas_add_zeroes(char left[VAS_SIZE_ONE], char right[VAS_SIZE_ONE]);

void vas_reverse_string(char* input);

void vas_decimal_mantis_to_binary(char binary_output[VAS_SIZE_BIN],
                                  vas_decimal value);

int vas_get_sign(int value);

int vas_get_scale(int value);

void vas_base_ten_char_array_add(char left[VAS_SIZE_ONE],
                                 char right[VAS_SIZE_ONE],
                                 char result[VAS_SIZE_ONE]);

void vas_binary_to_base_ten(char binary[VAS_SIZE_BIN],
                            char output[VAS_OVER_SIZE]);

void vas_add_the_dot(int dot, char* the_string);

void vas_print_decimal(vas_decimal input);

#endif  // DEC_VAS_DECIMAL_CONVERSION_H_