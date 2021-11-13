/*************************************************************************/
/*  base_enemy2d.h                                                       */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef BASEENEMY2D_H
#define BASEENEMY2D_H

#include "scene/2d/physics_body_2d.h"
#include <iostream>

#define MAX_HEALTH 1
#define ZERO_HEALTH 0
#define DEFAULT_DAMAGE_INTERVAL 1

class BaseEnemy2D : public KinematicBody2D {
	GDCLASS(BaseEnemy2D, KinematicBody2D);

public:
	enum State { ALIVE = 1,
		DEAD = 2 };
	virtual void damage();
	BaseEnemy2D();
	real_t health; // value between 0 and 1
	State state;
	real_t get_health() const;
	BaseEnemy2D::State get_state() const;

protected:
	static void _bind_methods();
	double damage_interval;
};

VARIANT_ENUM_CAST(BaseEnemy2D::State);

#endif // BASEENEMY2D_H
