/*************************************************************************/
/*  core_utils.h                                                         */
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

#ifndef CORE_UTILS_H
#define CORE_UTILS_H

#include "core/os/memory.h"
#include "core/reference.h"
#include "scene/2d/path_2d.h"
#include "scene/main/node.h"
#include "scene/resources/animation.h"
#include <memory>

//TODO: I should make AnimationUtils a singleton
class AnimationUtils : public Reference {
	GDCLASS(AnimationUtils, Reference);
	int count;

protected:
	static void _bind_methods();

public:
	enum HZ_MODE { UP = 1,
		DOWN = 2 };
	void add(int p_value);
	void reset();
	int get_total() const;
	Ref<Animation> animation;
	//TODO:This function really should be static...
	Ref<Animation> get_animation(NodePath node_path, String text, String delimeter = " ");
	Vector2 h_line_pattern(Ref<Curve2D> path, Vector2 origin, int length);
	Vector2 v_line_pattern(Ref<Curve2D> path, Vector2 origin, int length);
	Vector2 hz_line_pattern(Ref<Curve2D> path, Vector2 origin, int length, HZ_MODE mode);
	Vector2 zig_zag_pattern(Ref<Curve2D> path, Vector2 origin, int width, int height);
	Vector2 rectangle_pattern(Ref<Curve2D> path, Vector2 origin, int width, int height);

	//	Vector2 hz_line_pattern(Curve2D path,Vector2 origin,  int length);
	AnimationUtils();
};
VARIANT_ENUM_CAST(AnimationUtils::HZ_MODE);
#endif // CORE_UTILS_H
