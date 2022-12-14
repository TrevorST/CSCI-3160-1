/* 
 * CS:APP Data Lab 
 * 
 * Calen Cummings, cummingscc (completed bitXor, tmin, isTmax, allOddBits, negate, and isAsciiDigit)
 * Cory Windham, windham (completed logicalNeg, isLessOrEqual, howManyBits, and conditional)
 * Trevor Taylor, taylorts (completed logicalNeg, lessThanOrEqual, tmin)
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* We can AND each parameter with the bit-flipped version of the other, and then AND their results. This works by revealing where the parameters have 1's in common and where they do not. */
  int xFlip = ~x;
  int yFlip = ~y;
  int xSet = x & yFlip;
  int ySet = y & xFlip;
  int xSetFlip = ~xSet;
  int ySetFlip = ~ySet;
  int ansFlip = xSetFlip & ySetFlip;
  return ~ansFlip;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* exploit bit shifting to generate large numbers by multiplying by 2; minimum 2's complement would be the most negative number, which is 1 followed by 31 zeros. */
  int a = 1 << 31;
  return a;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* if x is Tmax, then adding one to x and adding the sum back to x will create -1. Tmax and -1 are the only cases where this would be true, so !(x + 1) will return 1 if x is -1. Flipping x will return 0 if it is Tmax and so will !(x + 1), meaning Tmax will always result in 0 being returned and !0 always returning 1. */
  int tMax_check = ((x + 1) + x);
  int negative_one_check = !(x + 1);
  int x_test = ~tMax_check | negative_one_check;
  return !x_test;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* Generates a mask of the desired bits to be set to 1 to quickly check for compliance. ANDing with the mask makes sure that all the ones are actually set, and then XOR will return with 0 if our desired bits are set. */	
  int a = 170;
  int b = (a << 8) + 170;
  int mask = (b << 16) + b;
  int d = mask & x;
  a = d ^ mask;
  return !a;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* Utilizes the two's complement to find the negative of any value. */	
  int a = ~x + 1;
  return a;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* First need to check that the given value is not above 0x3whatever and return 1 if it complies. After making sure bits 5-8 give us a hex 3, the only case we care about in bits 1-4 is if bit 4 is a 1; if it is, we must make sure that bits 2-3 are both 0. Every other combination of the last 4 bits will pass. */
  int three_mask = !((x >> 4) ^ 3);
  int bit_four_check = !((x >> 3) & 1);
  int middle_bits = !(x & 6);
  int nine_or_less = (bit_four_check | middle_bits);
  return (three_mask & nine_or_less);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {

        //turns x into boolean 1 or 0 this will be used as the basis for everything moving forward
        int dub_not_x = !(!x);

        //takes x and makes it able to be used as a conditional operator with y and z
        //this is done because the truth of x determines y or z (either -1 or 0)
        int mask = ~(dub_not_x&1)+1;

        //conditional operator is added to y because if x is true the y is the result
         //if x is true the var is -1 meaning y is returned
        int res_y = mask & y;

        //in this case the ~of mask & with z will be what is used to determine if z is
        //the result if x is false or 0 then z is the result
        int res_z = (~mask)&z;

        //adding together gives the answer becuase it will either be 0 + z or y + 0
        int result = res_y + res_z;

        return result;

}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */

/*
 * first we need to narrow down to the sign bit by shifting x and y 31 to the right
 *then we take the xor of that and ! that which is 1 if the signs are different.
 then check if x is neg and signs are different by anding x with var above

 */
int isLessOrEqual(int x, int y) {

	int x_sign = x>>31;                             //set sign bit for x
        int y_sign = y>>31;                             //set sign bit for y

        int d_sign = x_sign & (!y_sign);

        int s_sign = ((x+(~y)) >>31) & (!(x_sign ^ y_sign));

        return d_sign|s_sign;

}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
         //if x!= 0 right shit the number to get its signed bit if positive 0 if negative -1
         //if x== 0 the all that but 0 would be the outcome
         int s_bit_normal = x >> 31;

         //if x!= 0 negate plus 1 to get the inverse right shift and plus 1 to get 0
         //if x == 0 then is 0
         int s_bit_neg = (~x + 1) >> 31;

         //or together and add 1 to give 0 if x != 0 gives 1 if x== 0
         int result = (s_bit_normal | s_bit_neg) + 1;
         return result;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
	
	//set result
        int result = 0;

        //find the sign bit
        int sbit = x >> 31;

        //flips bits if x is neg
        x = (sbit & ~x) | (~sbit & x);

        //checks the 16th if x has to the 16th place shifts right 16 and
        //resets x if needed
        int k = !!(x >> 16) << 4;
        x = x >> k;
        result += k;

        //checks the 8th if x has to the 8th place shifts right 16 and
        //resets x if needed
        k = !!(x >> 8) << 3;
        x = x >> k;
        result += k;

        //checks the 4th if x has to the 4th place shifts right 16 and
        //resets x if needed
        k = !!(x >> 4) << 2;
        x = x >> k;
        result += k;
	
	//checks the 2nd if x has to the 2nd place shifts right 16 and
        //resets x if needed
        k = !!(x >> 2) << 1;
        x = x >> k;
        result += k;

        //checks the 1st if x has to the 1st place shifts right 16 and
        //resets x if needed
        k = !!(x >> 1);
        x = x >> k;
        result += k;

        //0th bit
        int zeroBit = x;
        result += zeroBit;

        //adds one at the end for 0
        result += 1;

        return result;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
