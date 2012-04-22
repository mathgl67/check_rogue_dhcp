/**
 * Copyright (C) 2012
 * mathgl67_AT_gmail.com
 *
 * This file is part of check_rogue_dhcp
 *
 * Check_rogue_dhcp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Check_rogue_dhcp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Check_rogue_dhcp.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#define OS_LINUX
/* #define OS_MACOSX */

#ifdef OS_LINUX
#define HAVE_BIND_TO_DEVICE 1
#endif /* OS_LINUX */

#ifdef OS_MACOSX
#define HAVE_BIND_TO_DEVICE 0
#endif /* OS_MAXOSX */

#endif /* __CONFIG_H__ */
