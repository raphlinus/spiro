/*
ppedit - A pattern plate editor for Spiro splines.
Copyright (C) 2007 Raph Levien

Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
<LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
option. This file may not be copied, modified, or distributed
except according to those terms.

*/
#include <Carbon/Carbon.h>

#include "zmisc.h"
#include "bezctx.h"
#include "bezctx_quartz.h"


typedef struct {
    bezctx base;
    CGMutablePathRef pathref;
    int is_open;
} bezctx_quartz;

static void
bezctx_quartz_moveto(bezctx *z, double x, double y, int is_open) {
    bezctx_quartz *bc = (bezctx_quartz *)z;
    if (!bc->is_open) CGPathCloseSubpath(bc->pathref);
    CGPathMoveToPoint(bc->pathref, NULL, x, y);
    bc->is_open = is_open;
}

static void
bezctx_quartz_lineto(bezctx *z, double x, double y) {
    bezctx_quartz *bc = (bezctx_quartz *)z;
    CGPathAddLineToPoint(bc->pathref, NULL, x, y);
}

static void
bezctx_quartz_quadto(bezctx *z, double x1, double y1, double x2, double y2)
{
    bezctx_quartz *bc = (bezctx_quartz *)z;
    CGPathAddQuadCurveToPoint(bc->pathref, NULL, x1, y1, x2, y2);
}

bezctx *
new_bezctx_quartz(void) {
    bezctx_quartz *result = znew(bezctx_quartz, 1);

    result->base.moveto = bezctx_quartz_moveto;
    result->base.lineto = bezctx_quartz_lineto;
    result->base.quadto = bezctx_quartz_quadto;
    result->base.mark_knot = NULL;
    result->pathref = CGPathCreateMutable();
    result->is_open = 1;
    return &result->base;
}


CGMutablePathRef
bezctx_to_quartz(bezctx *z)
{
    bezctx_quartz *bc = (bezctx_quartz *)z;
    CGMutablePathRef result = bc->pathref;

    if (!bc->is_open) CGPathCloseSubpath(result);
    zfree(bc);
    return result;
}
