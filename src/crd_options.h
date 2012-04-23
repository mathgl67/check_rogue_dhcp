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

#define CRD_OPTIONS_MAGIC htonl(0x63825363)
#define CRD_OPTIONS_END 255

enum crd_options_code_e {
    CRD_OPTIONS_CODE_MESSAGE_TYPE=53,
    CRD_OPTIONS_CODE_PARAMETER_REQUEST_LIST=55,
};

enum crd_options_message_type_e {
    CRD_OPTIONS_MESSAGE_TYPE_DISCOVER = 1,
    CRD_OPTIONS_MESSAGE_TYPE_OFFER = 2,
    CRD_OPTIONS_MESSAGE_TYPE_REQUEST = 3,
    CRD_OPTIONS_MESSAGE_TYPE_DECLINE = 4,
    CRD_OPTIONS_MESSAGE_TYPE_ACK = 5,
    CRD_OPTIONS_MESSAGE_TYPE_NAK = 6,
    CRD_OPTIONS_MESSAGE_TYPE_RELEASE = 7,
    CRD_OPTIONS_MESSAGE_TYPE_INFORM = 8,
};

typedef struct crd_options_s {
    void *data;
    size_t pos;
} crd_options_t;

void crd_options_init(crd_options_t *crd_options, void *data);
int crd_options_append(crd_options_t *crd_options, void *data, size_t datalen);
int crd_options_append_uint8(crd_options_t *crd_options, uint8_t data);
int crd_options_append_uint16(crd_options_t *crd_options, uint16_t data);
int crd_options_append_uint32(crd_options_t *crd_options, uint32_t data);
int crd_options_append_head(crd_options_t *crd_options, uint8_t code, uint8_t len);
void crd_options_display(crd_options_t *crd_options);

#endif /* __CRD_OPTIONS_H__ */