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
void AnimationUtils::add(int p_value) {
	count += p_value;
}

void AnimationUtils::reset() {
	count = 0;
}

int AnimationUtils::get_total() const {
	return count;
}

void AnimationUtils::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add", "value"), &AnimationUtils::add);
	ClassDB::bind_method(D_METHOD("reset"), &AnimationUtils::reset);
	ClassDB::bind_method(D_METHOD("get_total"), &AnimationUtils::get_total);
	ClassDB::bind_method(D_METHOD("get_animation"), &AnimationUtils::get_animation);
	ClassDB::bind_method(D_METHOD("get_node"), &AnimationUtils::get_node);
}

AnimationUtils::AnimationUtils() {
	count = 0;
}

/**
 * @brief Summator::get_animation
 * @return
 */
Ref<Animation> AnimationUtils::get_animation(NodePath node_path, String text, String delimeter) {
	animation.instance();
	int track_index = animation->add_track(Animation::TrackType::TYPE_VALUE, -1);
	animation->track_set_path(track_index, node_path);
	float current_transition = 0.0;
	String current_text = "";
	//TODO:When doing this from GDScript, it returns a PoolStringArray.
	//PoolStringArray is supposed to be faster than Vector and I would like to use it, but don't know
	//how at the moment.
	Vector<String> tokens = text.split(delimeter);

	for (int i = 0; i < tokens.size(); i++) {
		current_text = current_text + tokens[i] + delimeter;

		//This is very inefficient at the moment, but still learning the API...
		Variant v{ current_text };

		animation->track_insert_key(track_index, current_transition, v);
		current_transition = current_transition + 0.5;
		animation->set_length(animation->get_length() + 0.5);
	}

	return animation;
}

/**
 * @brief Summator::get_node
 * @return
 */
Node *AnimationUtils::get_node() {
	node = std::make_unique<Node>();
	return node.get();
}
