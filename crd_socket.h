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
#ifndef __CRD_SOCKET_H__
#define __CRD_SOCKET_H__

typedef struct crd_socket_s {
    uint32_t sd;
    struct addrinfo hints;
} crd_socket_t;

crd_socket_t *crd_socket_new();
void crd_socket_free(crd_socket_t **crd_socket);
void crd_socket_init(crd_socket_t *crd_socket);
void crd_socket_close(crd_socket_t *crd_socket);
int crd_socket_set_broadcast(crd_socket_t *crd_socket, int value);
int crd_socket_set_checksum(crd_socket_t *crd_socket, int value);
int crd_socket_set_timeout(crd_socket_t *crd_socket, time_t seconds);
int crd_socket_set_bind_to_device(crd_socket_t *crd_socket, const char *device);
void crd_socket_bind(crd_socket_t *crd_socket);
void crd_socket_send(crd_socket_t *crd_socket, crd_message_t *crd_message);
void crd_socket_recv(crd_socket_t *crd_socket, crd_message_t *crd_message);

#endif /* __CRD_SOCKET_H__ */
