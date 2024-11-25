/*
 * hsv2rgb.h
 *
 *  Created on: Nov 25, 2024
 *      Author: blueb
 */

#ifndef INC_HSV2RGB_H_
#define INC_HSV2RGB_H_

/* hsv2rgb.h */

struct hsv_colour {
   float h;
   float s;
   float v;
}; /* end struct */

struct rgb_colour {
   float r;
   float g;
   float b;
}; /* end struct */

int hsv2rgb( struct hsv_colour *hsv, struct rgb_colour *rgb );

#endif /* INC_HSV2RGB_H_ */
