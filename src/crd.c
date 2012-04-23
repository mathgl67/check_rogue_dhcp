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
main_parse(crd_args_t **crd_args, int argc, char **argv)
{
    *crd_args = crd_args_new();
    if (*crd_args == NULL)
        return 1;
    
    if (crd_args_parse(*crd_args, argc, argv) != 0) {
        crd_args_free(crd_args);
        return 2;
    } 
    
    crd_args_display(*crd_args);
    
    return 0;
}

int
main_send(crd_args_t *crd_args)
{
    crd_socket_t crd_socket;
    crd_message_t crd_message;
    
    /* prepare message */ 
    crd_message_reset(&crd_message);
    crd_message_set_default(&crd_message);
    crd_message_set_random_xid(&crd_message);
    crd_message_set_args(&crd_message, crd_args); 
   
    crd_message_display(&crd_message);
 
    /* options */
    crd_options_t crd_options;
    
    crd_options_init(&crd_options, crd_message.options);
    crd_options_append_uint32(&crd_options, CRD_OPTIONS_MAGIC);
    
    crd_options_append_head(&crd_options, CRD_OPTIONS_CODE_MESSAGE_TYPE, 1);
    crd_options_append_uint8(&crd_options, CRD_OPTIONS_MESSAGE_TYPE_DISCOVER);
    
    crd_options_append_head(&crd_options, CRD_OPTIONS_CODE_PARAMETER_REQUEST_LIST, 2);
    crd_options_append_uint8(&crd_options, 6);
    crd_options_append_uint8(&crd_options, 3);
    
    crd_options_append_uint8(&crd_options, CRD_OPTIONS_END);
    
    crd_options_display(&crd_options);
    
    /* prepare socket */
    crd_socket_reset(&crd_socket);
    crd_socket_init(&crd_socket);
    
    if (crd_socket_set_broadcast(&crd_socket, 1) != 0) {
        crd_socket_close(&crd_socket);
        return 1;
    }
       
    /* send a request */
    if (crd_socket_send(&crd_socket, &crd_message) != 0) {
        crd_socket_close(&crd_socket);
        return 2;
    } 
    
    crd_socket_close(&crd_socket);
    return 0;
}

int
main_recv(crd_args_t *crd_args)
{
    crd_socket_t crd_socket;
    crd_message_t crd_message;
    
    /* prepare message */
    crd_message_reset(&crd_message);

    /* create socket */
    crd_socket_reset(&crd_socket);
    crd_socket_init(&crd_socket);
    
    /* bind */
    if (crd_socket_set_broadcast(&crd_socket, 1) != 0) {
        crd_socket_close(&crd_socket);
        return 1;
    }
    
    if (crd_socket_set_timeout(&crd_socket, 1) != 0) {
        crd_socket_close(&crd_socket);
        return 2;
    }
    
    if (crd_socket_set_bind_to_device(&crd_socket, crd_args->device) != 0) {
        crd_socket_close(&crd_socket);
        return 3;
    }
    
    if (crd_socket_bind(&crd_socket) != 0) {
        crd_socket_close(&crd_socket);
        return 4;
    }
    
    /* read a response */
    if (crd_socket_recv(&crd_socket, &crd_message) != 0) {
        crd_socket_close(&crd_socket);
        return 5;
    }
    
    crd_message_display(&crd_message);
    crd_socket_close(&crd_socket);   
    
    return 0;
}

int
main(int argc, char **argv)
{
    crd_args_t *crd_args;

    /* init */
    srand(time(NULL));
    
    /* parse options */
    if (main_parse(&crd_args, argc, argv) != 0) {
        return 3;
    }
    
    if (main_send(crd_args) != 0) {
        crd_args_free(&crd_args);
        return 3;
    }
    
    if (main_recv(crd_args) != 0) {
        crd_args_free(&crd_args);
        return 3;
    }
    
    crd_args_free(&crd_args);
    
    return 0;
}

