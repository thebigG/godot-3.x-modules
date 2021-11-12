/*************************************************************************/
/*  base_enemy2d.cpp                                                     */
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

#include "base_enemy2d.h"

BaseEnemy2D::BaseEnemy2D():
    health{MAX_HEALTH}, damage_interval{MAX_HEALTH}
{}

real_t BaseEnemy2D::get_health() const
{
    return health;
}

void BaseEnemy2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("damage"), &BaseEnemy2D::damage);
    ClassDB::bind_method(D_METHOD("get_health"), &BaseEnemy2D::get_health);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "health", PROPERTY_HINT_NONE), "", "get_health");
}

void BaseEnemy2D::damage()
{
    if (health <= ZERO_HEALTH)
    {
        return;
    }

    health -= damage_interval;
}
