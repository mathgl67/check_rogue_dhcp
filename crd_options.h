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
#ifndef __CRD_OPTIONS_H__
#define __CRD_OPTIONS_H__

typedef struct crd_options_s {
  char *device;
  char *mac;
  char *client_ip;
} crd_options_t;

crd_options_t *crd_options_new();
void crd_options_free(crd_options_t **crd_options);
void crd_options_display(crd_options_t *crd_options);
int crd_options_parse(crd_options_t *crd_options, int argc, char **argv);
int crd_options_is_valid(crd_options_t *crd_options);

#endif /* __CRD_OPTIONS_H__ */