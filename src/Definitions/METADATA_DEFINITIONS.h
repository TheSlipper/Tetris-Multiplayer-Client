////////////////////////////////////////////////////////////
/// Tetris Multiplayer Game - PvP Tetris Experience
/// Copyright (C) 2019 Kornel Domeradzki
///
/// This program is free software; you can redistribute it and/or
/// modify it under the terms of the GNU General Public License
/// as published by the Free Software Foundation; either version 2
/// of the License, or (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program; if not, write to the Free Software
/// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
////////////////////////////////////////////////////////////
#pragma once

/// Definition Flags
///#define __WIN_ 1
#define __OS_X 1
/// #define __LINUX_ 1

/// Game metadata
#define GAME_NAME "Tetris Multiplayer"
#ifdef __WIN_
	#define OS_NAME "Windows_10 "
#endif
#ifdef __OS_X
	#define OS_NAME "MacOS_Mojave "
#endif
#ifdef __LINUX_
#define OS_NAME "GNU_Linux "
#endif

#define BUILD_NAME "INDEV_0.0.1 "

//#define GAME_PORT 7000

/// Server metadata
#define SERVER_IP "192.168.1.112"

//#define SERVER_PORT 7001
