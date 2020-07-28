#ifndef TIME_H
#define TIME_H


#include <cstddef>
#include <cstddef>
typedef	unsigned short			u16_t;
typedef	unsigned long			u32_t;
typedef	signed short			s16_t;
typedef	signed long             s32_t;
#define BYTE unsigned char

    // DEF: standard signed format
    // UNDEF: non-standard unsigned format
    #define	_XT_SIGNED

#ifdef	_XT_SIGNED
    typedef	s32_t                           xtime_t;
#else
    typedef	u32_t                           xtime_t;
#endif

struct time
{       /* date and time components */
    BYTE	tm_sec;
    BYTE	tm_min;
    BYTE	tm_hour;
    BYTE	tm_mday;
    BYTE	tm_mon;
    u16_t	tm_year;
};

void xttotm(struct time *t, xtime_t secs);
xtime_t xtmtot(struct time *t);



#endif // TIME_H
