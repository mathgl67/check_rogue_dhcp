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

int
main(int argc, char **argv)
{
    dhcp_socket_t *dhcp_socket;
    dhcp_message_t *dhcp_message;

    /* init */
    srand(time(NULL));

    /* prepare */
    dhcp_message = dhcp_message_new();
    dhcp_message_set_default(dhcp_message);
    dhcp_message_set_random_xid(dhcp_message);
    dhcp_message_set_hwaddr(dhcp_message, "00:26:18:80:b8:35");
    dhcp_message_display(dhcp_message);

    /* create socket */
    dhcp_socket = dhcp_socket_new();
    dhcp_socket_init(dhcp_socket);
    /* bind */
    dhcp_socket_enable_broadcast(dhcp_socket);
    dhcp_socket_bind_to_device(dhcp_socket, "eth0");
    dhcp_socket_bind(dhcp_socket);

    /* send a request */
    dhcp_socket_send(dhcp_socket, dhcp_message);

    /* read a response */
    dhcp_socket_recv(dhcp_socket, dhcp_message);
    dhcp_message_display(dhcp_message);

    /* free */
    dhcp_socket_close(dhcp_socket);
    dhcp_socket_free(&dhcp_socket);

    dhcp_message_free(&dhcp_message);

    return EXIT_SUCCESS;
}

