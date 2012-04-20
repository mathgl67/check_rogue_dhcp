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

#include "dhcpc.h"

dhcp_message_t *
dhcp_message_new()
{
    dhcp_message_t *dhcp_message = (dhcp_message_t *) malloc(sizeof(dhcp_message_t));
    if (dhcp_message == NULL) {
        fprintf(stderr, "dhcp_message_new: no free memory?\n");
    } else {
        memset(dhcp_message, 0, sizeof(dhcp_message_t));
    }

    return dhcp_message;
}


void
dhcp_message_display(dhcp_message_t *m)
{
    struct in_addr ciaddr, yiaddr, siaddr, giaddr;

    ciaddr.s_addr = m->ciaddr;
    yiaddr.s_addr = m->yiaddr;
    siaddr.s_addr = m->siaddr;
    giaddr.s_addr = m->giaddr;

    fprintf(stderr, "dhcp_message_t message = %p (\n", m);
    fprintf(stderr, "\top=%d, htype=%d, hlen=%d, hops=%d, xid=%d, secs=%d, flags=%x,\n", m->op, m->htype, m->hlen, m->hops, m->xid, m->secs, m->flags);
    fprintf(stderr, "\tciaddr=%s, yiaddr=%s, siaddr=%s, giaddr=%s,\n", inet_ntoa(ciaddr), inet_ntoa(yiaddr), inet_ntoa(siaddr), inet_ntoa(giaddr));
    fprintf(stderr, "\tchaddr=%02x:%02x:%02x:%02x:%02x:%02x\n", m->chaddr[0], m->chaddr[1], m->chaddr[2], m->chaddr[3], m->chaddr[4], m->chaddr[5]);
    fprintf(stderr, ");\n");
}

void
dhcp_message_set_default(dhcp_message_t *dhcp_message)
{
    dhcp_message->op = 0x1;
    dhcp_message->htype = 0x1;
    dhcp_message->hlen = 0x6;
    dhcp_message->hops = 0x0;
    dhcp_message->xid = htonl(0xdeadbeaf);
    dhcp_message->secs = htons(0);
    dhcp_message->flags = htons(0x8000); /* BROADCAST */
    dhcp_message->magic_cookie = htonl(0x63825363);
    dhcp_message->code = 53;
    dhcp_message->len = 1;
    dhcp_message->type = 1;
    dhcp_message->end = 0xFF;
}

void
dhcp_message_set_random_xid(dhcp_message_t *dhcp_message)
{
    dhcp_message->xid = htonl(rand());
}

void
dhcp_message_set_hwaddr(dhcp_message_t *dhcp_message, const char *hwaddr)
{
    int ret;
    ret = sscanf(
         hwaddr,
         "%2hx:%2hx:%2hx:%2hx:%2hx:%2hx", 
         (short unsigned int *) &(dhcp_message->chaddr[0]),
         (short unsigned int *) &(dhcp_message->chaddr[1]),
         (short unsigned int *) &(dhcp_message->chaddr[2]),
         (short unsigned int *) &(dhcp_message->chaddr[3]),
         (short unsigned int *) &(dhcp_message->chaddr[4]),
         (short unsigned int *) &(dhcp_message->chaddr[5])
    );

    if (ret != 6) {
        fprintf(stderr, "dhcp_message_set_hwaddr: cannot parse hardware addr\n");
    }
}

uint32_t
dhcp_message_conv_ipv4(const char *ip)
{
    struct in_addr inp;

    if (inet_aton(ip, &inp) == 0) {
        fprintf(stderr, "dhcp_message_conv_ipv4: cannot convert ipv4\n");
        return 0;
    }
    
    return inp.s_addr;
}

void
dhcp_message_free(dhcp_message_t **dhcp_message)
{
    if (*dhcp_message != NULL)
        free(*dhcp_message);
    *dhcp_message = NULL;
}

