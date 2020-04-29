/****************************************************************************
 *  Copyright (C) 2020 Lu Meng and Chen Xueqing.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#ifdef KEYBOARD_H_GLOBAL
#define KEYBOARD_H_EXTERN
#else
#define KEYBOARD_H_EXTERN extern
#endif

#define ERR -1
#define ENTER 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void setBufferedInput(bool enable);
int getkey();

#endif // __KEYBOARD_H__
