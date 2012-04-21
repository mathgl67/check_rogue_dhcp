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

crd_message_t *
crd_message_new()
{
    crd_message_t *crd_message = (crd_message_t *) malloc(sizeof(crd_message_t));
    if (crd_message == NULL) {
        fprintf(stderr, "crd_message_new: no free memory?\n");
    } else {
        memset(crd_message, 0, sizeof(crd_message_t));
    }

    return crd_message;
}


void
crd_message_display(crd_message_t *m)
{
    struct in_addr ciaddr, yiaddr, siaddr, giaddr;

    ciaddr.s_addr = m->ciaddr;
    yiaddr.s_addr = m->yiaddr;
    siaddr.s_addr = m->siaddr;
    giaddr.s_addr = m->giaddr;

    fprintf(stderr, "crd_message_t message = %p (\n", m);
    fprintf(stderr, "\top=%d, htype=%d, hlen=%d, hops=%d, xid=%d, secs=%d, flags=%x,\n", m->op, m->htype, m->hlen, m->hops, m->xid, m->secs, m->flags);
    fprintf(stderr, "\tciaddr=%s, yiaddr=%s, siaddr=%s, giaddr=%s,\n", inet_ntoa(ciaddr), inet_ntoa(yiaddr), inet_ntoa(siaddr), inet_ntoa(giaddr));
    fprintf(stderr, "\tchaddr=%02x:%02x:%02x:%02x:%02x:%02x\n", m->chaddr[0], m->chaddr[1], m->chaddr[2], m->chaddr[3], m->chaddr[4], m->chaddr[5]);
    fprintf(stderr, ");\n");
}

void
crd_message_set_default(crd_message_t *crd_message)
{
    crd_message->op = 0x1;
    crd_message->htype = 0x1;
    crd_message->hlen = 0x6;
    crd_message->hops = 0x0;
    crd_message->xid = htonl(0xdeadbeaf);
    crd_message->secs = htons(0);
    crd_message->flags = htons(0x8000); /* BROADCAST */
    crd_message->magic_cookie = htonl(0x63825363);
    crd_message->code = 53;
    crd_message->len = 1;
    crd_message->type = 1;
    crd_message->end = 0xFF;
}

void
crd_message_set_random_xid(crd_message_t *crd_message)
{
    crd_message->xid = htonl(rand());
}

void
crd_message_set_hwaddr(crd_message_t *crd_message, const char *hwaddr)
{
    int ret;
    ret = sscanf(
         hwaddr,
         "%2hx:%2hx:%2hx:%2hx:%2hx:%2hx", 
         (short unsigned int *) &(crd_message->chaddr[0]),
         (short unsigned int *) &(crd_message->chaddr[1]),
         (short unsigned int *) &(crd_message->chaddr[2]),
         (short unsigned int *) &(crd_message->chaddr[3]),
         (short unsigned int *) &(crd_message->chaddr[4]),
         (short unsigned int *) &(crd_message->chaddr[5])
    );

    if (ret != 6) {
        fprintf(stderr, "crd_message_set_hwaddr: cannot parse hardware addr\n");
    }
}

void
crd_message_set_options(crd_message_t *crd_message, crd_options_t *crd_options)
{
    crd_message_set_hwaddr(crd_message, crd_options->mac);
    
    if (crd_options->client_ip != NULL) {
        crd_message->ciaddr = crd_message_conv_ipv4(crd_options->client_ip);
    }
}

uint32_t
crd_message_conv_ipv4(const char *ip)
{
    struct in_addr inp;

    if (inet_aton(ip, &inp) == 0) {
        fprintf(stderr, "crd_message_conv_ipv4: cannot convert ipv4\n");
        return 0;
    }
    
    return inp.s_addr;
}

void
crd_message_free(crd_message_t **crd_message)
{
    if (*crd_message != NULL)
        free(*crd_message);
    *crd_message = NULL;
}

