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

void
crd_options_init(crd_options_t *crd_options, void *data)
{
    crd_options->data = data;
    crd_options->pos = 0;
}

int
crd_options_append(crd_options_t *crd_options, void *data, size_t datalen)
{
    if (crd_options->pos + datalen > CRD_MESSAGE_MAX_OPTION_LEN) {
        fprintf(stderr, "crd_options_append: max option size reached\n");
        return 1;
    }
    
    memcpy((crd_options->data + crd_options->pos), data, datalen);
    crd_options->pos = crd_options->pos + datalen;
    
    return 0;
}

int
crd_options_append_uint8(crd_options_t *crd_options, uint8_t data)
{
    return crd_options_append(crd_options, &data, 1);
}

int
crd_options_append_uint16(crd_options_t *crd_options, uint16_t data)
{
    return crd_options_append(crd_options, &data, sizeof(uint16_t));
}

int
crd_options_append_uint32(crd_options_t *crd_options, uint32_t data)
{
    return crd_options_append(crd_options, &data, sizeof(uint32_t));
}

int
crd_options_append_head(crd_options_t *crd_options, uint8_t code, uint8_t len)
{
    int ret=0;
    
    ret = crd_options_append_uint8(crd_options, code);
    if (ret != 0) return ret;
    
    ret = crd_options_append_uint8(crd_options, len);
    
    return ret;
}

void crd_options_display(crd_options_t *crd_options)
{
    size_t save_pos;
    uint32_t magic;
    uint8_t code, len;
    
    /* position will be used to read information */
    save_pos = crd_options->pos;
    crd_options->pos = 0;
       
    memcpy(&magic, (crd_options->data + crd_options->pos), sizeof(magic));
    crd_options->pos = crd_options->pos + sizeof(magic);
    
    memcpy(&code, (crd_options->data + crd_options->pos), sizeof(code));
    crd_options->pos = crd_options->pos + sizeof(code);
    
    memcpy(&len, (crd_options->data + crd_options->pos), sizeof(len));
    crd_options->pos = crd_options->pos + sizeof(len);
    
    fprintf(stderr, "crd_options options = %p (\n", crd_options);
    fprintf(stderr, "\t magic=0x%x,\n", magic);
    fprintf(stderr, "\t code=%d, len=%d\n", code, len);
    fprintf(stderr, ");\n");

    /* restore position */
    crd_options->pos = save_pos;
}