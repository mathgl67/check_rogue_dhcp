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

#include "crd.h"

crd_socket_t *
crd_socket_new()
{
    crd_socket_t *crd_socket = NULL;

    crd_socket = (crd_socket_t *) malloc(sizeof(crd_socket_t));
    
    if (crd_socket == NULL) {
        fprintf(stderr, "crd_socket_new: cannot allocate memory\n");
        return NULL;
    } 

    crd_socket_reset(crd_socket);
    
    return crd_socket; 
}

void
crd_socket_reset(crd_socket_t *crd_socket)
{
    memset(crd_socket, 0, sizeof(crd_socket_t));
}

void
crd_socket_free(crd_socket_t **crd_socket)
{
    if (*crd_socket != NULL)
        free(*crd_socket);

    *crd_socket = NULL;
}

void
crd_socket_init(crd_socket_t *crd_socket)
{
    /* set default */
    crd_socket->hints.ai_family = AF_UNSPEC;
    crd_socket->hints.ai_socktype = SOCK_DGRAM;
    crd_socket->hints.ai_flags = AI_PASSIVE;
    crd_socket->sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); 
}

void
crd_socket_close(crd_socket_t *crd_socket)
{
    close(crd_socket->sd);
}

int
crd_socket_set_broadcast(crd_socket_t *crd_socket, int value)
{
    int ret;

    ret = setsockopt(crd_socket->sd, SOL_SOCKET, SO_BROADCAST, &value, sizeof(value));
    if (ret == -1) {
        fprintf(stderr, "crd_socket_set_broadcast: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

int crd_socket_set_checksum_disable(crd_socket_t *crd_socket, int value)
{
    int ret;

    ret = setsockopt(crd_socket->sd, SOL_SOCKET, SO_NO_CHECK, &value, sizeof(value));
    if (ret == -1) {
        fprintf(stderr, "crd_socket_set_checksum_disable: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

int
crd_socket_set_timeout(crd_socket_t *crd_socket, time_t seconds)
{
    int ret;
    struct timeval tv;
    
    tv.tv_sec = seconds;
    tv.tv_usec = 0;
    
    ret = setsockopt(crd_socket->sd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    if (ret == -1) {
        fprintf(stderr, "crd_socket_set_timeout (rcv): %s\n", strerror(errno));
        return 1;
    }
    
    ret = setsockopt(crd_socket->sd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    if (ret == -1) {
        fprintf(stderr, "crd_socket_set_timeout (snd): %s\n", strerror(errno));
        return 2;
    }
    
    return 0;
}

int
crd_socket_set_bind_to_device(crd_socket_t *crd_socket, const char *device)
{
#if HAVE_BIND_TO_DEVICE == 1
    int ret;
    ret = setsockopt(crd_socket->sd, SOL_SOCKET, SO_BINDTODEVICE, device, sizeof(device));
    if (ret == -1) {
        fprintf(stderr, "crd_socket_bind_to_device: %s\n", strerror(errno));
        return 1;
    }
#else
    fprintf(stderr, "crd_socket_bind_to_device: disabled in config.h.\n");
#endif
    return 0;
}

int
crd_socket_bind(crd_socket_t *crd_socket)
{
    int ret;
    struct addrinfo *res;

    ret = getaddrinfo(INADDR_ANY, "68", &(crd_socket->hints), &res);
    if (ret != 0) {
        fprintf(stderr, "crd_socket_bind: %s\n", gai_strerror(ret));
        return 1;
    }

    ret = bind(crd_socket->sd, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    if (ret == -1) {
        fprintf(stderr, "crd_socket_bind: %s\n", strerror(errno));
        return 2;
    }    
    
    return 0;
}

int
crd_socket_send(crd_socket_t *crd_socket, crd_message_t *crd_message)
{
    int ret;
    struct addrinfo *res;

    ret = getaddrinfo("255.255.255.255", "67", &(crd_socket->hints), &res);
    if (ret != 0) {
        fprintf(stderr, "crd_socket_send: %s\n", gai_strerror(ret));
        return 1;
    }
    
    ret = sendto(crd_socket->sd, crd_message, sizeof(crd_message_t), 0,
                 res->ai_addr, res->ai_addrlen);
    
    freeaddrinfo(res);
    
    if (ret == -1) {
        fprintf(stderr, "crd_socket_send: error when sending data\n"); 
        return 2;
    }
    
    return 0;
}

int
crd_socket_recv(crd_socket_t *crd_socket, crd_message_t *crd_message)
{
    int ret;
    struct sockaddr_in from;
    unsigned int fromlen;
    
    fromlen = sizeof(struct sockaddr_in);
    ret = recvfrom(crd_socket->sd, crd_message, sizeof(crd_message_t), 0, (struct sockaddr *) &from, &fromlen);

    if (ret == -1) {
        fprintf(stderr, "crd_socket_receive: an error occured when trying to receive data\n");
        return 1;
    }
    
    fprintf(stderr, "from: [sin_family: %d, sin_port: %d, address: %s]\n", from.sin_family, from.sin_port, inet_ntoa(from.sin_addr));
    
    return 0;
}

