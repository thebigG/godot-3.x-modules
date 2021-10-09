/*************************************************************************/
/*  core_utils.cpp                                                       */
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

#include "core_utils.h"
#include <iostream>
void Summator::add(int p_value) {
	count += p_value;
}

void Summator::reset() {
	count = 0;
}

int Summator::get_total() const {
	return count;
}

void Summator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add", "value"), &Summator::add);
	ClassDB::bind_method(D_METHOD("reset"), &Summator::reset);
	ClassDB::bind_method(D_METHOD("get_total"), &Summator::get_total);
    ClassDB::bind_method(D_METHOD("get_animation"), &Summator::get_animation);
    ClassDB::bind_method(D_METHOD("get_node"), &Summator::get_node);

}

Summator::Summator() {
	count = 0;
}

/**
 * @brief Summator::get_animation
 * @return
 */
Ref<Animation> Summator::get_animation()
{
    animation.instance();
    return animation;
}

/**
 * @brief Summator::get_node
 * @return
 */
Node* Summator::get_node()
{
    node = std::make_unique<Node>();
    return node.get();
}
