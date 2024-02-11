#ifndef BIT_MATH_H_INCLUDED
#define BIT_MATH_H_INCLUDED

#define SET_BIT(reg,X)    (reg |=   (1<<X))
#define CLEAR_BIT(reg,X)  (reg &=  ~(1<<X))
#define TOGGLE_BIT(reg,X) (reg ^=   (1<<X))

#define GET_BIT(reg,X)    ((reg>>X) & 0x01)
#endif // BIT_MATH_H_INCLUDED
