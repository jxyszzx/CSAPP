/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* 德摩根定律对取反同样适用
  故x&y = ~~(x&y) == ~((~x) | (~y))
  */
  return ~((~x) | (~y));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /* 小端 */
  int mask = 0xff;
  int len = n << 3;
  return (x >> len) & mask;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*1. 掩码可以通过取反得到
    2. 关于>>(n-1)，当n=0时，移位负数可能会出问题，所以可以将表达式拆开来
  */
  int mask = ~(((1 << 31) >> n) << 1);
  return mask & (x >> n);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /*1. 主要思路是二分计数
    2. 前两次计数是可能出现溢出的，如一位相加出现10，两位相加出现100
    3. 如果研究一下性质也许还能优化，这里只是大致的估算了上界
  */
  int tmp_mask1 = (0x55) | (0x55 << 8);
  int mask1 = (tmp_mask1) | (tmp_mask1 << 16);
  int tmp_mask2 = (0x33) | (0x33 << 8);
  int mask2 = (tmp_mask2) | (tmp_mask2 << 16);
  int tmp_mask3= (0x0f) | (0x0f << 8);
  int mask3 = (tmp_mask3) | (tmp_mask3 << 16);

  x = (x & mask1) + ((x >> 1) & mask1);
  // x = x - ((x >> 1) & mask1); //如果能用减号 
  x = (x & mask2) + ((x >> 2) & mask2);  
  x = (x + (x >> 4)) & mask3;  
  x = x + (x >> 8);  
  x = x + (x >> 16);
  return x & 0x3f;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /* 解法一：一直想着写mask的话指令不够用，但其实不需要。
  x = x | (x >> 16);
  x = x | (x >> 8);
  x = x | (x >> 4);
  x = x | (x >> 2);
  x = x | (x >> 1);
  return (x & 1) ^ 1;
  */
  
  /* 解法二（超级难想）
    只有0会变成1，试着对0取反，得到11111111，它加一后能变回0。
    那么对其他数取反加一，则不管什么情况，不可能变符号，即x|(~x + 1)的符号位恒为1。
    我们已经制造出了一个符号位的区别，接下来只要把符号位拉到最低位，就可以用类似异或的方法解决了。
    本应该是(x & 1) ^ 1来去除其他位的影响，或者直接(~x) & 1判断，但我们发现了一个特殊性质。
    移位后我们得到了11111111和00000000，分别是-1和0，我们可以很轻易地把它转换成0和1。
  */
  return ((x | (~x + 1)) >> 31) + 1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*刚开始当作ilog2来做，但其实没有这么强的条件。
    1. 能否对应的是大小关系，我们可以观察临界状态让等号成立从而找到等价关系。
    2. 从1最多到第几位，我们可以直接想办法把通用的形式表示出来。
    对于正数，可以用n位表示的话，第一位是0，表示为0...0 0xxx(n位)，
    对于负数，用n位表示的话，应为1...1 1xxx(n位)。

    那么，我们可以分别将其右移n-1[n+(~0)]位，得到0...0和1...1。
    要把它们表示为1，即!(~x) | !x
  */
  int tmp = x >> (n+(~0));
  return (!(~tmp)) | (!tmp);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  /* 课本2.3.7
  */
  int signx = x >> 31;
  int mask = (1 << n) + (~0);
  int bias = signx&mask;
  return (x + bias) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /* 德摩根定律提取!到括号外，简化
  */
  return !((x >> 31) | (!x));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* 分成符号是否相同来讨论。
     若异号，则只有x负y正为所求；
     若同号，则y-x >= 0为所求。【术语补码来源，对于非0x80000000，2^w - x = -x，可将减转换为加】
     由补码的加法性质，异号之间的加法是不会有正负溢出的。【p63】
     然后要注意的是，由于补码的不对称性，0x8000的补码为其本身，但由于补码编码本身的连续性，这并不会破坏之前的数学性质。
     【可以通过0x8001-0x8000 和 0x8002-0x8001的对比来发现，但是鬼知道为什么啊...( ＿ ＿)ノ｜】
  */
  int sub = y + (~x + 1);
  int signsub = (sub >> 31) & 1;
  int signx = (x >> 31) & 1;
  int signy = (y >> 31) & 1;
  int equal = (!(signx ^ signy) & !signsub);
  int notequal = signx & !signy;
  return equal | notequal;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  /*note：取一个Byte可以(x>>n)&0xff，无需减去前面的那些。
  */
  /* 这里使用二分而不是分块其实无意中反而利用了01的所有信息。
     前缀和编译不通过所以没有使用，抛弃可读性的话可以再优化。
     然后，其实对于最后四位我们给出另一种分块做法(4*2Byte)里的一个套路，不用二分也能用最朴素的方法做出来。
  */
  int bit_16 = !!(x >> 16);
  int bias_16 = bit_16 << 4;

  int bit_8 = !!(x >> (8 + bias_16));
  int bias_8 = bit_8 << 3;
  
  int bit_4 = !!(x >> (4 + bias_8 + bias_16));
  int bias_4 = bit_4 << 2;
  /*
  int bit_2 = !!(x >> (2 + bias_4 + bias_8 + bias_16));
  int bias_2 = bit_2 << 1;

  int bit_1 = !!(x >> (1 + bias_2 + bias_4 + bias_8 + bias_16));
  int bias_1 = bit_1;

  return bias_1 + bias_2 + bias_4 + bias_8 + bias_16;
  */
  int highbyte = x >> (bias_4 + bias_8 + bias_16);
  int b1 = (highbyte >> 3) & 1;
  int b2 = ((highbyte >> 2) & 1) | b1;
  int b3 = ((highbyte >> 1) & 1) | b2;
  int b4 = (highbyte & 1) | b3;

  return ~0 + b1 + b2 + b3 + b4 + bias_4 + bias_8 + bias_16;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 unsigned mask, check;
  check = (uf << 1) >> 24;
  if (check == 0xff && (uf << 9)) {
    return uf;
  }
  // unsigned 
  mask = (1 << 31);
  return mask ^ uf;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned sign, exponent, frac, left_shift, result, flag;
  unsigned maskF = 0x007fffff;
  left_shift = flag = sign = 0;
  // Special Case
  if (x == 0) {
    return 0;
  }
  if (x == 0x80000000) {
    return 0xcf000000;
  }
  // Negative
  if (x < 0) {
    x = -x;
    sign = 0x80000000;
  }
  // left shift until highest pos is 1
  while (!(x & 0x80000000)) {
    x <<= 1;
    left_shift++;
  }
  // round up only if lowest 8 bits of x is larger than a half, or equals a half but lowest of frac equals 1
  flag = ((x & 0xff) > 0x80) || ((x & 0x1ff) == 0x180);
  // 127 + 31 - left_shift
  exponent = (158 - left_shift) << 23;
  frac = (x >> 8) & maskF;
  result = (sign | exponent | frac) + flag;
  return result;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned maskS, maskE, maskF, S, E, F;
  maskS = 0x80000000;
  maskE = 0x7f800000;
  maskF = 0x007fffff;
  S = (maskS & uf) >> 31;
  E = (maskE & uf) >> 23;
  F = maskF & uf;
  // Nan
  if (!(~(E|0xffffff00))) {
    return uf;
  }
  if (E != 0) {
    E += 1;
  }
  else {
    F <<= 1;
  }
  uf = (S << 31) | F | (E << 23);
  return uf;
}
