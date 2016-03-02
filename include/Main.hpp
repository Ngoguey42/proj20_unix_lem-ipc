// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 12:58:38 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/02 19:49:22 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAIN_HPP
# define MAIN_HPP

extern "C"
{
# include "lemipc.h"
# ifdef T
#  undef T
# endif
}

# include "gl/gl.hpp"
# include "gl_canvas/GlCanvasHolder.hpp"
# include "tiles/Tiles.hpp"
# include "ftui/Activity.hpp"

class Main
{
	/* CONSTRUCTION ***************** */
public:
	static Main				*instance(void);

private:
	Main(void);
public:
	~Main(void);

	/* LOOP ************************* */
public:
	void					loop(void);

public:
	/* GLFW INTERACTIONS ************ */
	void					onMouseMove(int x, int y);
	void					onMouseScroll(float delta);
	void					onKeyUp(int key, int scancode, int mods);
	void					onKeyDown(int key, int scancode, int mods);
	void					onMouseUp(int x, int y, int button, int mods);
	void					onMouseDown(int x, int y, int button, int mods);

	static void				handleKeyEvents(
		GLFWwindow *window, int key, int scancode, int action, int mods);
	static void				handleMousePosEvents(
		GLFWwindow *window, double x, double y);
	static void				handleMouseButtonEvents(
		GLFWwindow *window, int button, int action, int mods);
	static void				handleMouseScrollEvents(GLFWwindow *window,
													double, double y);

	/* LIBFTUI INTERACTIONS ********* */
	typedef std::integral_constant<unsigned int, 1> ftlua_size;
	//TODO: Push application's classes too
	static Main				*ftlua_pop(lua_State *l, int i,
								std::function<void(std::string)> panic);

private:
	GLFWwindow									*_window;
	gl::GlCanvasHolder							_canvasHolder;
	Tiles										_tiles;
	ftui::Activity								_act;
};

#endif
