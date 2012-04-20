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
#ifndef __DHCP_SOCKET_H__
#define __DHCP_SOCKET_H__

typedef struct dhcp_socket_s {
    uint32_t sd;
    struct addrinfo hints;
} dhcp_socket_t;

dhcp_socket_t *dhcp_socket_new();
void dhcp_socket_free(dhcp_socket_t **dhcp_socket);
void dhcp_socket_init(dhcp_socket_t *dhcp_socket);
void dhcp_socket_close(dhcp_socket_t *dhcp_socket);
void dhcp_socket_enable_broadcast(dhcp_socket_t *dhcp_socket);
void dhcp_socket_bind_to_device(dhcp_socket_t *dhcp_socket, const char *device);
void dhcp_socket_bind(dhcp_socket_t *dhcp_socket);
void dhcp_socket_send(dhcp_socket_t *dhcp_socket, dhcp_message_t *dhcp_message);
void dhcp_socket_recv(dhcp_socket_t *dhcp_socket, dhcp_message_t *dhcp_message);

#endif /* __DHCP_SOCKET_H__ */
