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

#include "check_rogue_dhcp.h"

dhcp_socket_t *
dhcp_socket_new()
{
    dhcp_socket_t *dhcp_socket = NULL;

    dhcp_socket = (dhcp_socket_t *) malloc(sizeof(dhcp_socket_t));
    
    if (dhcp_socket == NULL) {
        fprintf(stderr, "dhcp_socket_new: cannot allocate memory\n");
        return NULL;
    } 

    memset(dhcp_socket, 0, sizeof(dhcp_socket_t));

    /* set default */
    dhcp_socket->hints.ai_family = AF_UNSPEC;
    dhcp_socket->hints.ai_socktype = SOCK_DGRAM;
    dhcp_socket->hints.ai_flags = AI_PASSIVE;

    return dhcp_socket; 
}

void
dhcp_socket_free(dhcp_socket_t **dhcp_socket)
{
    if (*dhcp_socket != NULL)
        free(*dhcp_socket);

    *dhcp_socket = NULL;
}

void
dhcp_socket_init(dhcp_socket_t *dhcp_socket)
{
    dhcp_socket->sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); 
}

void
dhcp_socket_close(dhcp_socket_t *dhcp_socket)
{
    close(dhcp_socket->sd);
}

void
dhcp_socket_enable_broadcast(dhcp_socket_t *dhcp_socket)
{
    int ret, value=1;

    ret = setsockopt(dhcp_socket->sd, SOL_SOCKET, SO_BROADCAST, &value, sizeof(int));
    if (ret == -1) {
        fprintf(stderr, "dhcp_socket_enable_broadcast: %s\n", strerror(errno));
    }
}

void
dhcp_socket_bind(dhcp_socket_t *dhcp_socket)
{
    int ret;
    struct addrinfo *res;

    ret = getaddrinfo(INADDR_ANY, "68", &(dhcp_socket->hints), &res);
    if (ret != 0) {
        fprintf(stderr, "dhcp_socket_bind: %s\n", gai_strerror(ret));
        return;
    }

    ret = bind(dhcp_socket->sd, res->ai_addr, res->ai_addrlen);
    if (ret == -1) {
        fprintf(stderr, "dhcp_socket_bind: %s\n", strerror(errno));
        return;
    }
}

void
dhcp_socket_bind_to_device(dhcp_socket_t *dhcp_socket, const char *device)
{
#if HAVE_BIND_TO_DEVICE == 1
    int ret;
    ret = setsockopt(dhcp_socket->sd, SOL_SOCKET, SO_BINDTODEVICE, device, sizeof(device));
    if (ret == -1) {
        fprintf(stderr, "dhcp_socket_bind_to_device: %s\n", strerror(errno));
        return;
    }
#else
    fprintf(stderr, "dhcp_socket_bind_to_device: disabled in config.h.\n");
#endif
}

void
dhcp_socket_send(dhcp_socket_t *dhcp_socket, dhcp_message_t *dhcp_message)
{
    int ret;
    struct addrinfo *res;

    ret = getaddrinfo("255.255.255.255", "67", &(dhcp_socket->hints), &res);
    if (ret != 0) {
        fprintf(stderr, "dhcp_socket_send: %s\n", gai_strerror(ret));
        return;
    }
    
    ret = sendto(dhcp_socket->sd, dhcp_message, sizeof(dhcp_message_t), 0,
                 res->ai_addr, res->ai_addrlen);
    if (ret == -1) {
        fprintf(stderr, "dhcp_socket_send: error when sending data\n"); 
        return;
    }
}

void
dhcp_socket_recv(dhcp_socket_t *dhcp_socket, dhcp_message_t *dhcp_message)
{
    int ret;
    struct sockaddr from;
    unsigned int fromlen;
    
    fromlen = sizeof(struct sockaddr);
    ret = recvfrom(dhcp_socket->sd, dhcp_message, sizeof(dhcp_message_t), 0, &from, &fromlen);

    if (ret == -1) {
        fprintf(stderr, "dhcp_socket_receive: an error occured when trying to receive data\n");
    }
}

