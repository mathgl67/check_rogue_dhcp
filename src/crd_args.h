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
#ifndef __CRD_ARGS_H__
#define __CRD_ARGS_H__

typedef struct crd_args_s {
  char *device;
  char *mac;
  char *client_ip;
} crd_args_t;

crd_args_t *crd_args_new();
void crd_args_free(crd_args_t **crd_args);
void crd_args_display(crd_args_t *crd_args);
int crd_args_parse(crd_args_t *crd_args, int argc, char **argv);
int crd_args_is_valid(crd_args_t *crd_args);

#endif /* __CRD_ARGS_H__ */