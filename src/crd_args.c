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

crd_args_t *
crd_args_new()
{
    crd_args_t *crd_args;
    
    crd_args = (crd_args_t *) malloc(sizeof(crd_args_t));
    if (crd_args == NULL) {
        fprintf(stderr, "crd_args_new: cannot allocate memory.");
        return NULL;
    }
    
    memset(crd_args, 0, sizeof(crd_args_t));
    
    return crd_args;
}

void
crd_args_free(crd_args_t **crd_args)
{
    if (*crd_args != NULL)
        free(*crd_args);
    *crd_args = NULL;       
}

void
crd_args_display(crd_args_t *crd_args)
{
    fprintf(stderr, "crd_args_t options = %p (\n", crd_args);
    fprintf(stderr, "\tdevice=%s, mac=%s\n", crd_args->device, crd_args->mac);
    fprintf(stderr, ");\n");
}

int
crd_args_is_valid(crd_args_t *crd_args)
{
    if (crd_args->device == NULL) {
        fprintf(stderr, "crd_args_is_valid: device (-d') is mandatory\n");
        return 1;
    }
    else if (crd_args->mac == NULL) {
        fprintf(stderr, "crd_args_is_valid: mac (-m) is mandatory\n");
        return 2;
    }
    else {
        return 0;
    }
}

int
crd_args_parse(crd_args_t *crd_args, int argc, char **argv)
{
    char c;
    
    while((c = getopt(argc, argv, "d:m:c:")) != -1)
    {
        switch(c)
        {
            case 'd':
                crd_args->device = optarg;
                break;
            case 'm':
                crd_args->mac = optarg;
                break;
            case 'c':
                crd_args->client_ip = optarg;
                break;
            case '?':
                    if (optopt == 'c')
                        fprintf(stderr, "Option -%c requires an argument.\n",
                                optopt);
                    else if (isprint (optopt))
                        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                    else
                        fprintf(stderr, "Unknown option character `\\x%x'.\n",
                                optopt);
                        return 1;
             default:
                return 2;
        }
    }
    
    if (crd_args_is_valid(crd_args) > 0) {
        return 3;
    }
    
    return 0;
}
