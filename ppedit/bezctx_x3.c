/*
ppedit - A pattern plate editor for Spiro splines.
Copyright (C) 2007 Raph Levien

Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
<LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
option. This file may not be copied, modified, or distributed
except according to those terms.

*/
#include <x3.h>
#include "zmisc.h"
#include "bezctx.h"
#include "bezctx_x3.h"

typedef struct {
    bezctx base;
    x3dc *dc;
    int is_open;
} bezctx_x3;

static void
bezctx_x3_moveto(bezctx *z, double x, double y, int is_open) {
    bezctx_x3 *bc = (bezctx_x3 *)z;

    if (!bc->is_open) x3closepath(bc->dc);
    x3moveto(bc->dc, x, y);
    bc->is_open = is_open;
}

void
bezctx_x3_lineto(bezctx *z, double x, double y) {
    bezctx_x3 *bc = (bezctx_x3 *)z;

    x3lineto(bc->dc, x, y);
}

void
bezctx_x3_quadto(bezctx *z, double x1, double y1, double x2, double y2)
{
    bezctx_x3 *bc = (bezctx_x3 *)z;
    double x0, y0;

    x3getcurrentpoint(bc->dc, &x0, &y0);
    x3curveto(bc->dc,
                  x1 + (1./3) * (x0 - x1),
                  y1 + (1./3) * (y0 - y1),
                  x1 + (1./3) * (x2 - x1),
                  y1 + (1./3) * (y2 - y1),
                  x2,
                  y2);
}

void
bezctx_x3_curveto(bezctx *z, double x1, double y1, double x2, double y2,
                      double x3, double y3)
{
    bezctx_x3 *bc = (bezctx_x3 *)z;

    x3curveto(bc->dc, x1, y1, x2, y2, x3, y3);
}

void
bezctx_x3_finish(bezctx *z)
{
    bezctx_x3 *bc = (bezctx_x3 *)z;

    if (!bc->is_open)
        x3closepath(bc->dc);

    zfree(bc);
}

bezctx *
new_bezctx_x3(x3dc *dc) {
    bezctx_x3 *result = znew(bezctx_x3, 1);

    result->base.moveto = bezctx_x3_moveto;
    result->base.lineto = bezctx_x3_lineto;
    result->base.quadto = bezctx_x3_quadto;
    result->base.curveto = bezctx_x3_curveto;
    result->base.mark_knot = NULL;
    result->dc = dc;
    result->is_open = 1;
    return &result->base;
}
