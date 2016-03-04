// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 10:15:01 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/04 20:22:45 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <array>
#include <fstream>

#include "ft/utils.hpp"
#include "ftui/AView.hpp"

#include "Main.hpp"
#include "config_window.hpp"


#ifdef MAC_OS_MODE
# define INIT_GLEW			true
# define OPENGL_PROFILE		GLFW_OPENGL_CORE_PROFILE
#else
# define INIT_GLEW			(glewInit() == GLEW_OK)
# define OPENGL_PROFILE		GLFW_OPENGL_COMPAT_PROFILE
#endif
#ifdef GLFW_DOUBLEBUFFER
# define HINT_DOUBLE_BUFFER	true
#else
# define GLFW_DOUBLEBUFFER	0
# define HINT_DOUBLE_BUFFER	false
#endif

/*
** ************************************************************************** **
** CONSTRUCTION
*/

Main			*Main::instance(void)
{
	static Main		*m = nullptr;

	if (m == nullptr)
		m = new Main();
	return m;
}

Main::Main(void)
	: _window(nullptr)
	, _canvasHolder(WIN_WIDTHI, WIN_HEIGHTI)
	, _tiles()
	, _act(WIN_SIZEVI)
	, _boardWidth(4)
	, _board(_boardWidth * _boardWidth, -1)
	, _gameStatus("Initialization")
{
	auto			pushFun =
		[&, this](std::string const &fname, lua_CFunction f) {
		_act.registerLuaCFun_table("Main", fname, f);
	};
	std::ifstream	is("res/layout.xml");
	lua_State		*l;

	std::srand(time(NULL));

	_act.inflate(is);
	l = _act.getLuaState();
	luaL_dostring(l, "Main = {}");
	ftlua::set(l, ftlua::makeKeys("Main"), 0, (void*)this);
	pushFun("getBoardWidth", &Main::getBoardWidthLua);
	pushFun("getBoard", &Main::getBoardLua);
	pushFun("getGameStatus", &Main::getGameStatusLua);

	if (glfwInit() != GL_TRUE)
		throw std::runtime_error("Cannot load GLFW");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (HINT_DOUBLE_BUFFER)
		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);
	if ((_window = glfwCreateWindow(
			 WIN_WIDTHI, WIN_HEIGHTI, "npuzzle", NULL, NULL)) == NULL)
		throw std::runtime_error("Cannot create GLFW window");
	glfwMakeContextCurrent(_window);
	if (!INIT_GLEW)
		throw std::runtime_error("Cannot load GLEW");
	glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
	glfwSetWindowUserPointer(_window, this);
	glfwSetKeyCallback(_window, &Main::handleKeyEvents);
	glfwSetCursorPosCallback(_window, &Main::handleMousePosEvents);
	glfwSetMouseButtonCallback(_window, &Main::handleMouseButtonEvents);
	glfwSetScrollCallback(_window, &Main::handleMouseScrollEvents);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_tiles.init(WIN_SIZEVI
				, ft::Vec2<int>(95, 95), 30, 0.33f
				, ft::Vec3<int>(120, 181, 129)
				, ft::Vec3<int>(10, 150, 10)
				, ft::Vec3<int>(10, 45, 10)
		);
	_canvasHolder.init();

	_board[5] = 42; //TODO: debug
	return ;
}

Main::~Main(void)
{
	glfwDestroyWindow(_window);
	glfwTerminate();
	return ;
}

/*
** ************************************************************************** **
** LOOP
*/

void				Main::loop(void)
{
	ftui::ACanvas		&canvas(_canvasHolder.getCanvas());

	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		_tiles.render();
		_act.fireEvent("ON_BOARD_UPDATE");
		_act.render(canvas);
		_canvasHolder.render();
		glfwSwapBuffers(_window);
	}
	return ;
}

/*
** ************************************************************************** **
** GLFW INTERACTIONS
*/

void			Main::onKeyUp(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(_window, true);
	else
		_act.onKeyUp(key, mods);
	(void)scancode;
	return ;
}

void			Main::onKeyDown(int key, int scancode, int mods)
{
	lua_State		*l = _act.getLuaState();

	_act.onKeyDown(key, mods);
	(void)scancode;
	(void)l;
	return ;
}

void			Main::onMouseMove(int x, int y)
{
	_act.onMouseMove(x, y);
	return ;
}

void			Main::onMouseScroll(float delta)
{
	_act.onMouseScroll(delta);
	return ;
}

void			Main::onMouseUp(int x, int y, int button, int mods)
{
	_act.onMouseUp(x, y, button, mods);
	return ;
}

void			Main::onMouseDown(int x, int y, int button, int mods)
{
	_act.onMouseDown(x, y, button, mods);
	return ;
}

void			Main::handleKeyEvents(
	GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Main		*main;

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	FTASSERT(main != NULL);
	if (action == GLFW_RELEASE)
		main->onKeyUp(key, scancode, mods);
	else if (action == GLFW_PRESS)
		main->onKeyDown(key, scancode, mods);
	return ;
}

void			Main::handleMousePosEvents(GLFWwindow *window,
										   double x, double y)
{
	Main		*main;

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	FTASSERT(main != NULL);
	main->onMouseMove(x, y);
	return ;
}

void			Main::handleMouseScrollEvents(GLFWwindow *window,
											  double, double y)
{
	Main		*main;

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	FTASSERT(main != NULL);
	main->onMouseScroll(y);
	return ;
}

void			Main::handleMouseButtonEvents(
	GLFWwindow *window, int button, int action, int mods)
{
	Main		*main;
	double		pos[2];

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	FTASSERT(main != NULL);
	glfwGetCursorPos(window, pos + 0, pos + 1);
	if (action == GLFW_PRESS)
		main->onMouseDown(static_cast<int>(pos[0]), static_cast<int>(pos[1])
						  , button, mods);
	else
		main->onMouseUp(static_cast<int>(pos[0]), static_cast<int>(pos[1])
						, button, mods);
	return ;
}

/*
** ************************************************************************** **
** LIBFTUI INTERACTIONS
*/

Main			*Main::ftlua_pop(
	lua_State *l, int i, std::function<void(std::string)> panic)
{
	Main		*v;
	int			type;

	FTLUA_STACKASSERT_PANIC(
		l, lua_istable(l, i), panic
		, ft::f("Main::ftlua_pop(i = %)", i), ft::f("No table at i"));
	ftlua::push(l, 0);
	type = lua_gettable(l, i < 0 ? i - 1 : i);
	FTLUA_STACKASSERT_PANIC(
		l, type == LUA_TLIGHTUSERDATA, panic
		, ft::f("Main::ftlua_pop(i = %)", i), ft::f("No pointer at [0]"));
	v = reinterpret_cast<Main*>(lua_touserdata(l, -1));
	lua_pop(l, 1);
	lua_remove(l, i);
	return v;
}

void			Main::ftlua_push(
	lua_State *l, std::function<void(std::string)>)
{
	ftlua::pushLight(l, this);
	return ;
}

int				Main::getBoardWidth(void) const
{
	return this->_boardWidth;
}

int				Main::getBoardWidthLua(lua_State *l)
{
	return ftlua::handle<1, 1>(l, &Main::getBoardWidth);
}

std::vector<int> const	&Main::getBoard(void) const
{
	return this->_board;
}

int				Main::getBoardLua(lua_State *l)
{
	return ftlua::handle<1, 1>(l, &Main::getBoard);
}

std::string const	&Main::getGameStatus(void) const
{
	return this->_gameStatus;
}

int				Main::getGameStatusLua(lua_State *l)
{
	return ftlua::handle<1, 1>(l, &Main::getGameStatus);
}

/*
** ************************************************************************** **
** IPCs INTERACTIONS
*/

void			Main::fetchBoard(void)
{
	// Game can be fully reloaded between 2 fetchBoard()
	// There is no case for exit or raise in fetchBoard
	// have a fallback configuration for _board and _boardWidth
	// handle signals to clean properly
	// display game status on window

	// once:
	// 	generate keys						(May raise)

	// each fetch (refresh rate?):
	// 	retrieve sem_reslife				(No raise)
	// 	lock sem_reslife					(No raise, handle SIGINT)
	// 	retrieve shm_gameinfo				(No raise)
	// 	ON_BOARD_SIZE_UPDATE if necessary
	// 	retrieve shm_board					(No raise)
	// 	ON_BOARD_UPDATE if necessary

	// unmap / release all					(No raise)

	return ;
}


/*
** ========================================================================== **
** Main
*/

int				main(void)
{
	try
	{
		Main *const	main = Main::instance();

		main->loop();
		delete main;
	}
	catch (std::exception const &e)
	{
		std::cout << "Exception:\n" << e.what() << std::endl;
	}
	return (0);
}
