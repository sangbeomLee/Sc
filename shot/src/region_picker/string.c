#include "region_picker/errors.h"
#include "region.h"

static int int_from_string(const char **str)
{
    int ret = 0;
    while (**str >= '0' && **str <= '9')
    {
        ret *= 10;
        ret += **str - '0';
        (*str)++;
    }
    return ret;
}

int update_region_from_string(ShotRegion *r, const char *str)
{
    ShotRegion tmp;
    tmp.width = 100;
    tmp.height = 100;
    tmp.x = 0;
    tmp.y = 0;

    const char *ptr = str;
    tmp.width = int_from_string(&ptr);
    if (*ptr != 'x' && *ptr != 'X')
        return ERR_INVALID_ARGUMENT;
    ptr++;

    tmp.height = int_from_string(&ptr);
    if (*ptr != '\0')
    {
        if (*ptr != '+')
            return ERR_INVALID_ARGUMENT;
        ptr++;
        tmp.x = int_from_string(&ptr);
        if (*ptr != '+')
            return ERR_INVALID_ARGUMENT;
        ptr++;
        tmp.y = int_from_string(&ptr);
        if (*ptr != '\0')
            return ERR_INVALID_ARGUMENT;
    }

    r->x = tmp.x;
    r->y = tmp.y;
    r->width = tmp.width;
    r->height = tmp.height;

    return 0;
}
