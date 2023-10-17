/*
 * IncFile1.h
 *
 * Created: 05.09.2023 11:14:42
 *  Author: andreurn
 */ 


#ifndef BIT_MACROS_H
#define BIT_MACROS_H

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))
#define loop_until_bit_is_set(reg, bit) while(!test_bit(reg, bit))
#define loop_until_bit_is_clear(reg, bit) while(test_bit(reg, bit))

#endif