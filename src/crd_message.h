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
#ifndef __CRD_MESSAGE_H__
#define __CRD_MESSAGE_H__

enum crd_message_op_e {
    CRD_MESSAGE_OP_REQUEST=0x1,
    CRD_MESSAGE_OP_REPLY=0x2
};

typedef struct crd_message_s {
    uint8_t  op;
    uint8_t  htype;
    uint8_t  hlen;
    uint8_t  hops;
    uint32_t xid;
    uint16_t secs;
    uint16_t flags;
    uint32_t ciaddr;
    uint32_t yiaddr;
    uint32_t siaddr;
    uint32_t giaddr;
    uint8_t  chaddr[16];
    /* others */
    unsigned char sname[64];
    unsigned char file[128];
    /* options */
    uint32_t magic_cookie;
    uint8_t code;
    uint8_t len;
    uint8_t type;
    uint8_t end;
} crd_message_t;

crd_message_t *crd_message_new();
void crd_message_reset(crd_message_t *crd_message);
void crd_message_free(crd_message_t **crd_message);
void crd_message_display(crd_message_t *crd_message);
void crd_message_set_default(crd_message_t *crd_message);
void crd_message_set_random_xid(crd_message_t *crd_message);
void crd_message_set_hwaddr(crd_message_t *crd_message, const char *hwaddr);
void crd_message_set_options(crd_message_t *crd_message, crd_options_t *crd_options);
const char* crd_message_get_op_string(crd_message_t *crd_message);
uint32_t crd_message_conv_ipv4(const char *ip);

#endif /* __CRD_MESSAGE_H__ */
