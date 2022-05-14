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
	ClassDB::bind_method(D_METHOD("get_animation", "node_path", "text", "delimeter"), &AnimationUtils::get_animation);

	//TODO:The following is not compiling..
	ClassDB::bind_method(D_METHOD("h_line_pattern", "path", "origin", "length"), &AnimationUtils::h_line_pattern);
	ClassDB::bind_method(D_METHOD("v_line_pattern", "path", "origin", "length"), &AnimationUtils::v_line_pattern);
	ClassDB::bind_method(D_METHOD("hz_line_pattern", "path", "origin", "length", "mode"), &AnimationUtils::hz_line_pattern);
	ClassDB::bind_method(D_METHOD("rectangle_pattern", "path", "origin", "width", "height"), &AnimationUtils::rectangle_pattern);
	ClassDB::bind_method(D_METHOD("zig_zag_pattern", "path", "origin", "length", "zigs"), &AnimationUtils::zig_zag_pattern);
	BIND_ENUM_CONSTANT(UP);
	BIND_ENUM_CONSTANT(DOWN);
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
 * @brief AnimationUtils::h_line_pattern Draws a horizontal line on the path
 * that starts at origin that is length long.
 * @param path
 * @param origin
 * @param length
 * @return The last point that was added to curve.
 */
Vector2 AnimationUtils::h_line_pattern(Ref<Curve2D> path, Vector2 origin, int length) {
	Vector2 target = Vector2{ origin.x + length, origin.y };
	path->add_point(origin,
			Vector2(0, 0),
			Vector2(0, 0));
	path->add_point(target,
			Vector2(0, 0),
			Vector2(0, 0));
	return target;
}

Vector2 AnimationUtils::v_line_pattern(Ref<Curve2D> path, Vector2 origin, int length) {
	Vector2 target = Vector2{ origin.x, origin.y + length };
	path->add_point(origin,
			Vector2(0, 0),
			Vector2(0, 0));
	path->add_point(target,
			Vector2(0, 0),
			Vector2(0, 0));
	return target;
}

Vector2 AnimationUtils::hz_line_pattern(Ref<Curve2D> path, Vector2 origin, int length, HZ_MODE mode) {
	Vector2 target = Vector2(origin.x + length, origin.y + length);
	switch (mode) {
		case HZ_MODE::DOWN:
			target = Vector2(origin.x + length, origin.y + length);
			break;
		case HZ_MODE::UP:
			target = Vector2(origin.x + length, origin.y - length);
			break;
	}
	path->add_point(origin,
			Vector2(0, 0),
			Vector2(0, 0));
	path->add_point(target,
			Vector2(0, 0),
			Vector2(0, 0));

	return target;
}

Vector2 AnimationUtils::rectangle_pattern(Ref<Curve2D> path, Vector2 origin, int width, int height) {
	return v_line_pattern(
			path,
			h_line_pattern(
					path,
					v_line_pattern(
							path,
							h_line_pattern(
									path,
									origin,
									width),
							height),
					-width),
			-height);
}

Vector2 AnimationUtils::zig_zag_pattern(Ref<Curve2D> path, Vector2 origin, int length, int zigs) {
	Vector2 last_origin = origin;
	for (auto zig = 0; zig < zigs; zig++) {
		if (zig % 2 == 0) {
			last_origin = hz_line_pattern(path, last_origin, length, HZ_MODE::DOWN);
		} else {
			last_origin = hz_line_pattern(path, last_origin, length, HZ_MODE::UP);
		}
	}

	return last_origin;
}
