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
#ifndef __DHCP_MESSAGE_H__
#define __DHCP_MESSAGE_H__

typedef struct dhcp_message_s {
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
} dhcp_message_t;

dhcp_message_t *dhcp_message_new();
void dhcp_message_free(dhcp_message_t **dhcp_message);
void dhcp_message_display(dhcp_message_t *dhcp_message);
void dhcp_message_set_default(dhcp_message_t *dhcp_message);
void dhcp_message_set_random_xid(dhcp_message_t *dhcp_message);
void dhcp_message_set_hwaddr(dhcp_message_t *dhcp_message, const char *hwaddr); 
uint32_t dhcp_message_conv_ipv4(const char *ip);

#endif /* __DHCP_MESSAGE_H__ */
