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

int
main(int argc, char **argv)
{
    crd_socket_t *crd_socket;
    crd_message_t *crd_message;

    /* init */
    srand(time(NULL));

    /* prepare */
    crd_message = crd_message_new();
    crd_message_set_default(crd_message);
    crd_message_set_random_xid(crd_message);
    crd_message_set_hwaddr(crd_message, "00:26:18:80:b8:35");
    crd_message_display(crd_message);

    /* create socket */
    crd_socket = crd_socket_new();
    crd_socket_init(crd_socket);
    /* bind */
    crd_socket_enable_broadcast(crd_socket);
    crd_socket_bind_to_device(crd_socket, "eth0");
    crd_socket_bind(crd_socket);

    /* send a request */
    crd_socket_send(crd_socket, crd_message);

    /* read a response */
    crd_socket_recv(crd_socket, crd_message);
    crd_message_display(crd_message);

    /* free */
    crd_socket_close(crd_socket);
    crd_socket_free(&crd_socket);

    crd_message_free(&crd_message);

    return EXIT_SUCCESS;
}
