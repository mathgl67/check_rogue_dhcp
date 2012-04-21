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

crd_options_t *
crd_options_new()
{
    crd_options_t *crd_options;
    
    crd_options = (crd_options_t *) malloc(sizeof(crd_options_t));
    if (crd_options == NULL) {
        fprintf(stderr, "crd_options_new: cannot allocate memory.");
        return NULL;
    }
    
    memset(crd_options, 0, sizeof(crd_options_t));
    
    return crd_options;
}

void
crd_options_free(crd_options_t **crd_options)
{
    if (*crd_options != NULL)
        free(*crd_options);
    *crd_options = NULL;       
}

void
crd_options_display(crd_options_t *crd_options)
{
    fprintf(stderr, "crd_options_t options = %p (\n", crd_options);
    fprintf(stderr, "\tdevice=%s, mac=%s\n", crd_options->device, crd_options->mac);
    fprintf(stderr, ");\n");
}

int
crd_options_is_valid(crd_options_t *crd_options)
{
    if (crd_options->device == NULL) {
        fprintf(stderr, "crd_options_is_valid: device (-d') is mandatory\n");
        return 1;
    }
    else if (crd_options->mac == NULL) {
        fprintf(stderr, "crd_options_is_valid: mac (-m) is mandatory\n");
        return 2;
    }
    else {
        return 0;
    }
}

int
crd_options_parse(crd_options_t *crd_options, int argc, char **argv)
{
    char c;
    
    while((c = getopt(argc, argv, "d:m:")) != -1)
    {
        switch(c)
        {
            case 'd':
                crd_options->device = optarg;
                break;
            case 'm':
                crd_options->mac = optarg;
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
    
    if (crd_options_is_valid(crd_options) > 0) {
        return 3;
    }
    
    return 0;
}
